
#ifdef PCH_HH

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
//	pragmas.hh
//
// pragmas used to control warnings for msvc and g++
// one set of pragmas is used for precompiled header, and different
// set is used for translation units
//
///</summary>

#ifdef _MSC_VER
// disable warnings for /Wall
#pragma warning(disable: 4710) // lvl4 the compiler did not perform the inlining.
#pragma warning(disable: 4061) // lvl4 enumerator in a switch is not explicitly handled by a case label
#pragma warning(disable: 4062) // lvl4 enumerator in a switch is not handled
#pragma warning(disable: 4514) // lvl4 'function': unreferenced inline function has been removed
#pragma warning(disable: 4820) // lvl4 'bytes' bytes padding added after construct 'member_name'
#pragma warning(disable: 4242) // lvl4 'identifier': conversion from 'type1' to 'type2', possible loss of data
// disable warnings for /W4
#pragma warning(disable: 4250) // lvl2 'class1' : inherits 'class2::member' via dominance
#pragma warning(disable: 4996) // lvl3 The compiler encountered a deprecated declaration.
// save warnings for /W4
#pragma warning(push, 0)
#endif // _MSC_VER

#undef PCH_HH
#else // this is translation unit (not pch)
#define PCH_HH 1

#ifdef _MSC_VER
// restore warnings for /W4
#pragma warning(pop)
// re-enable warnings for /W4
#pragma warning(default: 4996) // lvl3 The compiler encountered a deprecated declaration.
// re-enable warnings for /Wall
#pragma warning(default: 4242) // lvl4 'identifier': conversion from 'type1' to 'type2', possible loss of data

#elif defined(__GNUC__)
#pragma GCC diagnostic warning "-Wall"
#pragma GCC diagnostic warning "-Wextra"
#pragma GCC diagnostic warning "-Wpedantic"
//#pragma GCC diagnostic warning "-Weffc++"

#pragma GCC diagnostic warning "-Wcast-align"
#pragma GCC diagnostic warning "-Wcast-qual"
#pragma GCC diagnostic warning "-Wconversion"
#pragma GCC diagnostic warning "-Wdisabled-optimization"
#pragma GCC diagnostic warning "-Wfloat-equal"

#pragma GCC diagnostic warning "-Wimport"
#pragma GCC diagnostic warning "-Winline"
#pragma GCC diagnostic warning "-Wunsafe-loop-optimizations"
#pragma GCC diagnostic warning "-Wlong-long"
#pragma GCC diagnostic warning "-Wmissing-include-dirs"
#pragma GCC diagnostic warning "-Wmissing-format-attribute"
#pragma GCC diagnostic warning "-Wpacked"
#pragma GCC diagnostic warning "-Winvalid-pch"
#pragma GCC diagnostic warning "-Wmissing-noreturn"
//#pragma GCC diagnostic warning "-Wpadded"
#pragma GCC diagnostic warning "-Wpointer-arith"
#pragma GCC diagnostic warning "-Wredundant-decls"
#pragma GCC diagnostic warning "-Wshadow"
#pragma GCC diagnostic warning "-Wstack-protector"
#pragma GCC diagnostic warning "-Wswitch-default"
//#pragma GCC diagnostic warning "-Wswitch-enum"
#pragma GCC diagnostic warning "-Wunreachable-code"
#pragma GCC diagnostic warning "-Wunused"
#pragma GCC diagnostic warning "-Wvariadic-macros"
#pragma GCC diagnostic warning "-Wwrite-strings"
#pragma GCC diagnostic warning "-Wctor-dtor-privacy"
#pragma GCC diagnostic warning "-Wlogical-op"
#pragma GCC diagnostic warning "-Wold-style-cast"
#pragma GCC diagnostic warning "-Woverloaded-virtual"
//#pragma GCC diagnostic warning "-Wsign-promo"
#pragma GCC diagnostic warning "-Wstrict-null-sentinel"
#pragma GCC diagnostic warning "-Wundef"
#pragma GCC diagnostic warning "-fdiagnostics-show-option"

#pragma GCC diagnostic warning "-Wformat"
#pragma GCC diagnostic warning "-Wformat-nonliteral"
#pragma GCC diagnostic warning "-Wformat-security"
#pragma GCC diagnostic warning "-Wformat-y2k"
#pragma GCC diagnostic warning "-Wformat-signedness"

#pragma GCC diagnostic ignored "-Wswitch"
#pragma GCC diagnostic ignored "-Waggregate-return"

#endif // _MSC_VER or defined(__GNUC__)
#endif // PCH_HH
