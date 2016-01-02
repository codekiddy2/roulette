/*
roulette - roulette simulation program

Copyright (C) 2015 codekiddy

roulette is free software: you can redistribute it
and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see http://www.gnu.org/licenses.
*/

///<summary>
//
// pch.cc
//
//	compiles PCH file for faster compilation and intellisense
//	Reference additional includes in pch.hh and not here
//
///</summary>

#include "pch.hh"

#if \
!defined(ATKMM_DISABLE_DEPRECATED) || \
!defined(GDKMM_DISABLE_DEPRECATED) || \
!defined(GTKMM_DISABLE_DEPRECATED) || \
!defined(GIOMM_DISABLE_DEPRECATED) || \
!defined(GLIBMM_DISABLE_DEPRECATED) || \
!defined(SIGCXX_DISABLE_DEPRECATED) || \
!defined(CAIROMM_DISABLE_DEPRECATED) || \
!defined(PANGOMM_DISABLE_DEPRECATED)
#error "deprecated API not disabled"
#endif

#ifndef GTKMM_ATKMM_ENABLED
#error "GTKMM_ATKMM_ENABLED undefined"
#endif
