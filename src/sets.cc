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
//	Defines number sets
//
//
///</summary>

// roulette
#include "pch.hh"
#define TU_SETS_CC // Explicit template instantiation from sets.hh
#include "sets.hh"

#define MAKE_SET(...) std::make_shared<type_raw_set>(type_raw_set{ __VA_ARGS__ });

namespace roulette
{
	type_set Corner0 = MAKE_SET({ 0, 1, 2, 3 });
	type_set Basket = MAKE_SET({ 0,37,1,2,3 });

	type_set Low = MAKE_SET({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18});
	type_set High = MAKE_SET({ 19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36});
	type_set Red = MAKE_SET({ 1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36 });
	type_set Black = MAKE_SET({ 2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35});
	type_set Even = MAKE_SET({ 2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36});
	type_set Odd = MAKE_SET({ 1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35});
	type_set Column1 = MAKE_SET({ 1,4,7,10,13,16,19,22,25,28,31,34});
	type_set Column2 = MAKE_SET({ 2,5,8,11,14,17,20,23,26,29,32,35});
	type_set Column3 = MAKE_SET({ 3,6,9,12,15,18,21,24,27,30,33,36});
	type_set Dozen1 = MAKE_SET({ 1,2,3,4,5,6,7,8,9,10,11,12});
	type_set Dozen2 = MAKE_SET({ 13,14,15,16,17,18,19,20,21,22,23,24});
	type_set Dozen3 = MAKE_SET({ 25,26,27,28,29,30,31,32,33,34,35,36});
	type_set Snake = MAKE_SET({ 1,5,9,12,14,16,19,23,27,30,32,34});
	type_set RedSplits = MAKE_SET({ 9,12,16,19,18,21,27,30});
	type_set BlackSplits = MAKE_SET({ 8,11,10,11,10,13,17,20,26,29,28,29,28,31});
	type_set OrphelinsEnPlen = MAKE_SET({ 1,6,9,14,17,20,31,34});
	type_set TriesDuCylindre = MAKE_SET({ 5,8,10,11,13,16,23,24,27,30,33,36});
	type_set VoisinsDeZero = MAKE_SET({ 4,7,12,15,18,21,19,22,32,35,0,2,3,25,26,28,29});
	type_set OrphelinsACheval = MAKE_SET({ 1,6,9,14,17,17,20,31,34});
	type_set Jeu0 = MAKE_SET({ 26,0,3,12,15,32,33});
	type_set Jeu79 = MAKE_SET({ 19,27,7,8,8,9,17,18,28,29});
	type_set EuropeanWheel = MAKE_SET({ 0,32,15,19,4,21,2,25,17,34,6,27,13,36,11,30,8,23,10,5,24,16,33,1,20,14,31,9,22,18,29,7,28,12,35,3,26});
	type_set AmericanWheel = MAKE_SET({ 0,28,9,26,30,11,7,20,32,17,5,22,34,15,3,24,36,13,1,37,27,10,25,29,12,8,19,31,18,6,21,33,16,4,23,35,14,2});
	type_set NoZeroWheel = MAKE_SET({ 32,15,19,4,21,2,25,17,34,6,27,13,36,11,30,8,23,10,5,24,16,33,1,20,14,31,9,22,18,29,7,28,12,35,3,26});

	type_set Street01 = MAKE_SET({ 0, 1, 2 });
	type_set Street02 = MAKE_SET({ 0, 2, 3 });

	type_set Street1 = MAKE_SET({ 1, 2, 3});
	type_set Street2 = MAKE_SET({ 4, 5, 6});
	type_set Street3 = MAKE_SET({ 7, 8, 9});
	type_set Street4 = MAKE_SET({ 10, 11, 12});
	type_set Street5 = MAKE_SET({ 13, 14, 15});
	type_set Street6 = MAKE_SET({ 16, 17, 18});
	type_set Street7 = MAKE_SET({ 19, 20, 21});
	type_set Street8 = MAKE_SET({ 22, 23, 24});
	type_set Street9 = MAKE_SET({ 25, 26, 27});
	type_set Street10 = MAKE_SET({ 28, 29, 30});
	type_set Street11 = MAKE_SET({ 31, 32, 33});
	type_set Street12 = MAKE_SET({ 34, 35, 36});

	type_set Line1 = MAKE_SET({ 1, 2, 3, 4, 5, 6 });
	type_set Line2 = MAKE_SET({ 4, 5, 6, 7, 8, 9 });
	type_set Line3 = MAKE_SET({ 7, 8, 9, 10, 11, 12 });
	type_set Line4 = MAKE_SET({ 10, 11, 12, 13, 14, 15 });
	type_set Line5 = MAKE_SET({ 13, 14, 15, 16, 17, 18 });
	type_set Line6 = MAKE_SET({ 16, 17, 18, 19, 20, 21 });
	type_set Line7 = MAKE_SET({ 19, 20, 21, 22, 23, 24 });
	type_set Line8 = MAKE_SET({ 22, 23, 24, 25, 26, 27 });
	type_set Line9 = MAKE_SET({ 25, 26, 27, 28, 29, 30 });
	type_set Line10 = MAKE_SET({ 28, 29, 30, 31, 32, 33 });
	type_set Line11 = MAKE_SET({ 31, 32, 33, 34, 35, 36 });

} // namespace roulette
