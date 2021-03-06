/*
MicroBuild
Copyright (C) 2016 TwinDrills

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "PCH.h"

#include "Actions/WriteHeaderMetadataToFile.h"

namespace MicroBuild {
	
WriteHeaderMetadataToFile::WriteHeaderMetadataToFile(MetadataFileInfo& info)
	: m_fileInfo(info)
{
	m_fileId = Strings::Uuid(16, { m_fileInfo.GeneratedHeaderPath.ToString() });
}

void WriteHeaderMetadataToFile::WriteHeader(TextStream& stream)
{
	stream.WriteLine("/*");
	stream.WriteLine("Ludo Game Engine");
	stream.WriteLine("Copyright (C) 2016 TwinDrills");
	stream.WriteLine("");
	stream.WriteLine("This program is free software: you can redistribute it and/or modify");
	stream.WriteLine("it under the terms of the GNU General Public License as published by");
	stream.WriteLine("the Free Software Foundation, either version 3 of the License, or");
	stream.WriteLine("(at your option) any later version.");
	stream.WriteLine("");
	stream.WriteLine("This program is distributed in the hope that it will be useful,");
	stream.WriteLine("but WITHOUT ANY WARRANTY; without even the implied warranty of");
	stream.WriteLine("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the");
	stream.WriteLine("GNU General Public License for more details.");
	stream.WriteLine("");
	stream.WriteLine("You should have received a copy of the GNU General Public License");
	stream.WriteLine("along with this program.  If not, see <http://www.gnu.org/licenses/>.");
	stream.WriteLine("*/");
	stream.WriteLine("#pragma once");
	stream.WriteLine("");
	stream.WriteLine("// Warning: This file is automatically generated by the MetaGeneration plugin.");
	stream.WriteLine("//          Do not modify manually, any change you make will not survive the next build.");
	stream.WriteLine("");
	stream.WriteLine("#include \"Core/Public/Reflection/ReflectionMacros.h\"");
	stream.WriteLine("");
	stream.WriteLine("#ifdef LD_REFLECTION_FILE_ID");
	stream.WriteLine("#undef LD_REFLECTION_FILE_ID");
	stream.WriteLine("#endif");
	stream.WriteLine("");
	stream.WriteLine("#define LD_REFLECTION_FILE_ID %s", m_fileId.c_str());
	stream.WriteLine("");
}

void WriteHeaderMetadataToFile::WriteClass(TextStream& stream, MetadataClass::Ptr classPtr)
{
	stream.WriteLine("// ----------------------------------------------------------------------------");
	stream.WriteLine("// Class - %s", classPtr->FullyQualifiedName.c_str());
	stream.WriteLine("// ----------------------------------------------------------------------------");	
	stream.WriteLine("#define LD_%s_%i_GENERATED_BODY \\", m_fileId.c_str(), classPtr->GeneratedBodyLine);
	stream.Indent();
	if (classPtr->BaseClasses.size() > 0)
	{
		MetadataClass::Ptr superClassPtr = classPtr->BaseClasses[0].Class;

		stream.WriteLine("LD_GENERATED_CLASS_BODY(%s, %s)",
			classPtr->FullyQualifiedName.c_str(),
			superClassPtr->FullyQualifiedName.c_str());
	}
	else
	{
		stream.WriteLine("LD_GENERATED_CLASS_BODY_NO_SUPER(%s)",
			classPtr->FullyQualifiedName.c_str());
	}
	stream.Undent();
	stream.WriteLine("");
}

void WriteHeaderMetadataToFile::WriteEnum(TextStream& stream, MetadataEnum::Ptr enumPtr)
{
	stream.WriteLine("// ----------------------------------------------------------------------------");
	stream.WriteLine("// Enum - %s", enumPtr->FullyQualifiedName.c_str());
	stream.WriteLine("// ----------------------------------------------------------------------------");
}

void WriteHeaderMetadataToFile::WriteType(TextStream& stream, MetadataType::Ptr typePtr)
{
	stream.WriteLine("// ----------------------------------------------------------------------------");
	stream.WriteLine("// Type -  %s", typePtr->ToString().c_str());
	stream.WriteLine("// ----------------------------------------------------------------------------");
}

bool WriteHeaderMetadataToFile::Execute()
{
	TextStream stream;
	WriteHeader(stream);

	for (auto& classPtr : m_fileInfo.Module.Classes)
	{
		if (classPtr->InMainFile && !classPtr->IsTemplateInstance)
		{
			WriteClass(stream, classPtr);
		}
	}

	for (auto& enumPtr : m_fileInfo.Module.Enums)
	{
		if (enumPtr->InMainFile)
		{
			WriteEnum(stream, enumPtr);
		}
	}

	/*
	for (auto& typePtr : m_fileInfo.Module.Types)
	{
		WriteType(stream, typePtr);
	}
	*/

	if (!stream.WriteToFile(m_fileInfo.GeneratedHeaderPath, true))
	{
		Log(LogSeverity::Fatal, "Failed to create generated file: %s\n", m_fileInfo.GeneratedHeaderPath.ToString().c_str());
		return false;
	}


	return true;
}

}; // namespace MicroBuild