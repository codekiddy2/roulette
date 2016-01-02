
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

// options
#include "pragmas.hh"

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
#include <cstdint> // for integral typedefs

// gtkmm
#include <gtkmm.h>

#if 0
#include <gtkmm/gdkmm.h> // included by gtkmm.h
#include <glibmm/giomm.h> // included by gtkmm.h
#include <glibmm/glibmm.h> // included by gtkmm.h and giomm.h
#endif

#ifdef GTKMM_ATKMM_ENABLED
#include <atkmm.h> // needed if GTKMM_ATKMM_ENABLED is defined
#endif // GTKMM_ATKMM_ENABLED

#include <pangomm.h>
#include <sigc++/sigc++.h>
#include <cairomm/cairomm.h>

#if 0 // not used
#include <goocanvasmm.h>
#endif // 0

// boost
#include <boost/random.hpp> // used by Engine class
#include <boost/filesystem.hpp> // used to check for existence of icons
#include <boost/random/random_device.hpp> // used by Engine class

#if 0 // not used
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#endif // 0

#endif // ! PCH_HH
