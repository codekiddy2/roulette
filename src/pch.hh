
#ifndef PCH_HH
#define PCH_HH 1

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
//	pch.hh
//
// precompiled header, used to speed up compilation and intelisense
// reference any headers which are not frequently modified here
//
///</summary>

#ifdef _MSC_VER
// disabled warnings for /W4
#pragma warning(disable: 4309) // lvl2 'conversion' : truncation of constant value
#pragma warning(disable: 4505) // lvl4 'function' : unreferenced local function has been removed
#pragma warning(disable: 4250) // lvl2 'class1' : inherits 'class2::member' via dominance
#pragma warning(disable: 4710) // lvl4 the compiler did not perform the inlining.
#pragma warning(disable: 4996) // lvl3 The compiler encountered a deprecated declaration.
#pragma warning(disable: 4242) // lvl4 The types are different. Type conversion may result in loss of data.
#pragma warning(push, 0)
#endif // _MSC_VER

// std
#include <vector> // wide usage for containers
#include <string> // wide usage to avoid const char*
#include <algorithm>	// get_neighbor() and std::for_each
#include <iostream> // for debugging (cout, cerr, endl)
#include <exception> // sed for error class
#include <cmath>	// SetPart2 in bet..
#include <utility> // for make_pair
#include <map> // used in Table and InfoBar
#include <unordered_map> // used in Table
#include <memory> // wide usage for shared_ptr
#include <tuple> // for chip tuple

// gtkmm
#include <gtkmm/gtkmm.h>

#if 0
#include <gtkmm/gdkmm.h> // included by gtkmm.h
#include <glibmm/giomm.h> // included by gtkmm.h
#include <glibmm/glibmm.h> // included by gtkmm.h and giomm.h
#endif

#include <atkmm/atkmm.h> // needed if GTKMM_ATKMM_ENABLED is defined
#include <sigc++/sigc++.h>
#include <cairomm/cairomm.h>
#include <pangomm/pangomm.h>

#if 0 // not used
#include <goocanvasmm\goocanvasmm.h>
#endif

// boost
#include <boost/random.hpp> // used by Engine class
#include <boost/filesystem.hpp> // used to check for existence of icons
#include <boost/random/random_device.hpp> // used by Engine class

#if 0 // not used
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#endif

#ifdef _MSC_VER
// reenable warnings for /W4
#pragma warning(default: 4309 4505 4250 4710 4996 4242)
#pragma warning(pop)
#endif // _MSC_VER

#endif // ! PCH_HH
