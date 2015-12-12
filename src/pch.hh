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

/*
PCH includes
TODO: modify or add more includes here for faster compilation and intellisense
*/

#ifdef _MSC_VER
__pragma(warning(disable: 4309 4505 4250)) __pragma(warning(push, 0)) // disable warnings

#define _SCL_SECURE_NO_WARNINGS // boost
#endif // _MSC_VER

// std
#include <vector>
#include <string>
#include <algorithm>	// used in GetNeighbor function

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

#ifdef _MSC_VER
__pragma(warning(default: 4309 4505)) __pragma(warning(pop)) // enable warnings
#endif // _MSC_VER

#endif // ! PCH_HH