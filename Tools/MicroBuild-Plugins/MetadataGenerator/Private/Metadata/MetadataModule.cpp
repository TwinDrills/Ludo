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

#include "Metadata/MetadataModule.h"

namespace MicroBuild {

MetadataClass::Ptr MetadataModule::FindClassByType(CXType type)
{
	for (auto& ptr : Classes)
	{
		if (clang_equalTypes(ptr->ClangType, type))
		{
			return ptr;
		}
	}
	return nullptr;
}

MetadataClass::Ptr MetadataModule::FindClassByCursor(CXCursor cursor)
{
	for (auto& ptr : Classes)
	{
		if (clang_equalCursors(ptr->ClangCursor, cursor))
		{
			return ptr;
		}
	}
	return nullptr;
}

MetadataClass::Ptr MetadataModule::FindUnspecializedTemplateClassByCursor(CXCursor cursor)
{
	for (auto& ptr : Classes)
	{
		if (ptr->IsTemplated && !ptr->IsTemplateInstance && clang_equalCursors(ptr->ClangCursor, cursor))
		{
			return ptr;
		}
	}
	return nullptr;
}

MetadataClass::Ptr MetadataModule::FindClassByName(const std::string& name)
{
	for (auto& ptr : Classes)
	{
		if (ptr->FullyQualifiedName == name)
		{
			return ptr;
		}
	}
	return nullptr;
}

MetadataType::Ptr MetadataModule::FindTypeByType(CXType type)
{
	for (auto& ptr : Types)
	{
		if (clang_equalTypes(ptr->ClangType, type))
		{
			return ptr;
		}
	}
	return nullptr;
}

MetadataEnum::Ptr MetadataModule::FindEnumByType(CXType type)
{
	for (auto& ptr : Enums)
	{
		if (clang_equalTypes(ptr->ClangType, type))
		{
			return ptr;
		}
	}
	return nullptr;
}

}; // namespace MicroBuild