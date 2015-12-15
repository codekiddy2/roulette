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
//	sets.cc
//
//	Defines common functions and number sets
//
//	TODO: add description
//
///</summary>

#include "pch.hh"
#include "sets.hh"

namespace roulette
{

#ifdef _MSC_VER
//symbol will be dynamically initialized (implementation limitation)
// false positive: http://stackoverflow.com/questions/34013930/error-c4592-symbol-will-be-dynamically-initialized-vs2015-1-static-const-std
#pragma warning (disable: 4592)
#endif // _MSC_VER

	set_t Basket{ 0,37,1,2,3 };
	set_t Low{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 };
	set_t High{ 19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36 };
	set_t Red{ 1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36 };
	set_t Black{ 2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35 };
	set_t Even{ 2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36 };
	set_t Odd{ 1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35 };
	set_t Column1{ 1,4,7,10,13,16,19,22,25,28,31,34 };
	set_t Column2{ 2,5,8,11,14,17,20,23,26,29,32,35 };
	set_t Column3{ 3,6,9,12,15,18,21,24,27,30,33,36 };
	set_t Dozen1{ 1,2,3,4,5,6,7,8,9,10,11,12 };
	set_t Dozen2{ 13,14,15,16,17,18,19,20,21,22,23,24 };
	set_t Dozen3{ 25,26,27,28,29,30,31,32,33,34,35,36 };
	set_t Snake{ 1,5,9,12,14,16,19,23,27,30,32,34 };
	set_t RedSplits{ 9,12,16,19,18,21,27,30 };
	set_t BlackSplits{ 8,11,10,11,10,13,17,20,26,29,28,29,28,31 };
	set_t OrphelinsEnPlen{ 1,6,9,14,17,20,31,34 };
	set_t TriesDuCylindre{ 5,8,10,11,13,16,23,24,27,30,33,36 };
	set_t VoisinsDeZero{ 4,7,12,15,18,21,19,22,32,35,0,2,3,25,26,28,29 };
	set_t OrphelinsACheval{ 1,6,9,14,17,17,20,31,34 };
	set_t Jeu0{ 26,0,3,12,15,32,33 };
	set_t Jeu79{ 19,27,7,8,8,9,17,18,28,29 };
	set_t EuropeanWheel{ 0,32,15,19,4,21,2,25,17,34,6,27,13,36,11,30,8,23,10,5,24,16,33,1,20,14,31,9,22,18,29,7,28,12,35,3,26 };
	set_t AmericanWheel{ 0,28,9,26,30,11,7,20,32,17,5,22,34,15,3,24,36,13,1,37,27,10,25,29,12,8,19,31,18,6,21,33,16,4,23,35,14,2 };
	set_t NoZeroWheel{ 32,15,19,4,21,2,25,17,34,6,27,13,36,11,30,8,23,10,5,24,16,33,1,20,14,31,9,22,18,29,7,28,12,35,3,26 };

#ifdef _MSC_VER
//symbol will be dynamically initialized (implementation limitation)
#pragma warning (default: 4592)
#endif // _MSC_VER

} // namespace roulette
