
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

// disabled in property sheet for /WAll
//#pragma warning (disable: 4820) // '4' bytes padding added after data member

#endif // _MSC_VER

// std
#include <vector>
#include <string>
#include <algorithm>	// get_neighbor() and std::for_each
#include <iostream> // for debugging (cout, cerr, endl)
#include <exception>
#include <cmath>	// SetPart2 in bet..
#include <utility> // for make_pair
#include <map> // used in Table


// gtkmm
#ifdef GTKMM_ATKMM_ENABLED
#include <atkmm\atkmm.h>
#endif // GTKMM_ATKMM_ENABLED

#include <gtkmm/gtkmm.h>

#if 0
#include <gtkmm/gdkmm.h> // included by gtkmm.h
#include <glibmm/giomm.h> // included by gtkmm.h
#include <glibmm/glibmm.h> // included by gtkmm.h and giomm.h
#endif

#include <sigc++/sigc++.h>
#include <cairomm/cairomm.h>
#include <pangomm/pangomm.h>

#if 0
#include <goocanvasmm\goocanvasmm.h> // not used
#endif

// boost
#include <boost/random.hpp>
#include <boost/filesystem.hpp>
#include <boost/random/random_device.hpp>

#define DEBUG_FILE_LOG
#define DEBUG_DND_LOG

#ifdef _MSC_VER
// reenable warnings for /W4
#pragma warning(default: 4309 4505 4250 4710 4996 4242)
#pragma warning(pop)
#endif // _MSC_VER

#endif // ! PCH_HH
