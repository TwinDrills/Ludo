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

// These constants should be passed in by the compiler when built for release
// by a build server. Otherwise they will default to dummy values.

#if !defined(LD_BUILD_CHANGELIST)
#define LD_BUILD_CHANGELIST 0
#endif

#if !defined(LD_BUILD_BRANCH)
#define LD_BUILD_BRANCH "Local"
#endif

#if !defined(LD_BUILD_TIMESTAMP)
#define LD_BUILD_TIMESTAMP __DATE__ " at " __TIME__
#endif

// If false asserts are compiled out.
#if !defined(LD_SHIPPING_BUILD)
#define LD_ASSERTS_ENABLED 1
#endif