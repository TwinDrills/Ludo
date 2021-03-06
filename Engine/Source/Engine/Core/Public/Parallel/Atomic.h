/*
Ludo Game Engine
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
#pragma once

namespace Ludo {
namespace Atomic {

/// \brief TODO
int Increment(int* Value);

/// \brief TODO
int Decrement(int* Value);

/// \brief TODO
int CompareExchange(int* Destination, int Exchange, int Comparand);

/// \brief TODO
void* CompareExchange(void** Destination, void* Exchange, void* Comparand);

/// \brief TODO
void RelaxCpu();
  
/// \brief TODO
template <typename ValueType>
struct AtomicValue
{
private:
    ValueType m_Value;
  
public:
    ValueType()
    {
    }

    ValueType(const ValueType& Other)
        : m_Value(Other)
    {      
        Store(m_Value, Other);
    }
  
    operator ValueType() const 
    {
        return Load(m_Value);
    }
  
    operator++()
    {
    }

    operator++(ValueType X)
    {
    }

    operator--()
    {
    }

    operator--(ValueType Y)
    {
    }

    operator=()
    {
    }

    operator+=()
    {
    }

    operator-=()
    {
    }

    operator&=()
    {
    }

    operator|=()
    {
    }

    operator^=()
    {
    }
  
    bool CompareExchange(ValueType& Orignal, ValueType& New)
    {
    }
  
    ValueType Exchange(ValueType& Orignal)
    {
    }
};

};
};
