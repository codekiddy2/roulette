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

#include "pch.hh"
#include "sets.hh"


bool is_red(const int number)
{
	switch (number)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 9:
	case 12:
	case 14:
	case 16:
	case 18:
	case 19:
	case 21:
	case 23:
	case 25:
	case 27:
	case 30:
	case 32:
	case 34:
	case 36:
		return true;
	default:
		return false;
	}
}

short which_column(const short number)
{
	if (number % 3 == 0)
		return 3;
	return number % 3;
}


short which_dozen(const short number)
{
	if (number < 13)
		return 1;
	else if (number < 25)
		return 2;
	return 3;
}

const short basket[] = { 0,37,1,2,3 };
const short low[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 };
const short high[] = { 19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36 };
const short red[] = { 1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36 };
const short black[] = { 2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35 };
const short even[] = { 2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36 };
const short odd[] = { 1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35 };
const short column1[] = { 1,4,7,10,13,16,19,22,25,28,31,34 };
const short column2[] = { 2,5,8,11,14,17,20,23,26,29,32,35 };
const short column3[] = { 3,6,9,12,15,18,21,24,27,30,33,36 };
const short dozen1[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
const short dozen2[] = { 13,14,15,16,17,18,19,20,21,22,23,24 };
const short dozen3[] = { 25,26,27,28,29,30,31,32,33,34,35,36 };
const short snake[] = { 1,5,9,12,14,16,19,23,27,30,32,34 };
const short redSplits[] = { 9,12,16,19,18,21,27,30 };
const short blackSplits[] = { 8,11,10,11,10,13,17,20,26,29,28,29,28,31 };
const short orphelinsEnPlen[] = { 1,6,9,14,17,20,31,34 };
const short triesDuCylindre[] = { 5,8,10,11,13,16,23,24,27,30,33,36 };
const short voisinsDeZero[] = { 4,7,12,15,18,21,19,22,32,35,0,2,3,25,26,28,29 };
const short orphelinsACheval[] = { 1,6,9,14,17,17,20,31,34 };
const short jeu0[] = { 26,0,3,12,15,32,33 };
const short jeu79[] = { 19,27,7,8,8,9,17,18,28,29 };
const short euroWheel[] = { 0,32,15,19,4,21,2,25,17,34,6,27,13,36,11,30,8,23,10,5,24,16,33,1,20,14,31,9,22,18,29,7,28,12,35,3,26 };
const short amWheel[] = { 0,28,9,26,30,11,7,20,32,17,5,22,34,15,3,24,36,13,1,37,27,10,25,29,12,8,19,31,18,6,21,33,16,4,23,35,14,2 };
const short noZeroWheel[] = { 32,15,19,4,21,2,25,17,34,6,27,13,36,11,30,8,23,10,5,24,16,33,1,20,14,31,9,22,18,29,7,28,12,35,3,26 };

set_t Low(low, low + sizeof(low) / sizeof(short));
set_t Odd(odd, odd + sizeof(odd) / sizeof(short));
set_t Red(red, red + sizeof(red) / sizeof(short));
set_t Jeu0(jeu0, jeu0 + sizeof(jeu0) / sizeof(short));
set_t High(high, high + sizeof(high) / sizeof(short));
set_t Even(even, even + sizeof(even) / sizeof(short));
set_t Jeu79(jeu79, jeu79 + sizeof(jeu79) / sizeof(short));
set_t Black(black, black + sizeof(black) / sizeof(short));
set_t Snake(snake, snake + sizeof(snake) / sizeof(short));
set_t Dozen1(dozen1, dozen1 + sizeof(dozen1) / sizeof(short));
set_t Dozen2(dozen2, dozen2 + sizeof(dozen2) / sizeof(short));
set_t Dozen3(dozen3, dozen3 + sizeof(dozen3) / sizeof(short));
set_t Basket(basket, basket + sizeof(basket) / sizeof(short));
set_t Column1(column1, column1 + sizeof(column1) / sizeof(short));
set_t Column2(column2, column2 + sizeof(column2) / sizeof(short));
set_t Column3(column3, column3 + sizeof(column3) / sizeof(short));
set_t RedSplits(redSplits, redSplits + sizeof(redSplits) / sizeof(short));
set_t BlackSplits(blackSplits, blackSplits + sizeof(blackSplits) / sizeof(short));
set_t VoisinsDeZero(voisinsDeZero, voisinsDeZero + sizeof(voisinsDeZero) / sizeof(short));
set_t OrphelinsEnPlen(orphelinsEnPlen, orphelinsEnPlen + sizeof(orphelinsEnPlen) / sizeof(short));
set_t TriesDuCylindre(triesDuCylindre, triesDuCylindre + sizeof(triesDuCylindre) / sizeof(short));
set_t OrphelinsACheval(orphelinsACheval, orphelinsACheval + sizeof(orphelinsACheval) / sizeof(short));
set_t EuropeanWheel(euroWheel, euroWheel + sizeof(euroWheel) / sizeof(short));
set_t AmericanWheel(amWheel, amWheel + sizeof(amWheel) / sizeof(short));
set_t NoZeroWheel(noZeroWheel, noZeroWheel + sizeof(noZeroWheel) / sizeof(short));


short get_neighbor(const ETable table, const short refNum, const short position)
{
	short i = 0;
	using std::find;
	static set_t::const_iterator iter;

#ifdef _MSC_VER
#pragma warning (disable: 4061 4062) // TODO: case statement not handled
#endif

	switch (table)
	{
	case ETable::NoZero:
		iter = find(NoZeroWheel.begin(), NoZeroWheel.end(), refNum);
		while (i != position) // if i == position refNum is returned
		{ // if i != position then iterating.... position times
			if (position > 0) // positive position
			{
				++i;
				++iter;
				if (iter == NoZeroWheel.end())
					iter = NoZeroWheel.begin(); // return to begin and continue
			}
			else // negative position
			{
				if (iter == NoZeroWheel.begin() && i != position) //if begin is not what we want...
					iter = NoZeroWheel.end(); // then go to end
				--iter;
				--i;
			}
		}
		break;

	case ETable::American:
		iter = find(AmericanWheel.begin(), AmericanWheel.end(), refNum);
		while (i != position)
		{
			if (position > 0)
			{
				++i;
				++iter;
				if (iter == AmericanWheel.end())
					iter = AmericanWheel.begin();
			}
			else
			{
				if (iter == AmericanWheel.begin() && i != position)
					iter = AmericanWheel.end();
				--iter;
				--i;
			}
		}
		break;

	case ETable::French:
	case ETable::European:
		iter = find(EuropeanWheel.begin(), EuropeanWheel.end(), refNum);
		while (i != position)
		{
			if (position > 0)
			{
				++i;
				++iter;
				if (iter == EuropeanWheel.end())
					iter = EuropeanWheel.begin();
			}
			else
			{
				if (iter == EuropeanWheel.begin() && i != position)
					iter = EuropeanWheel.end();
				--iter;
				--i;
			}
		}
		break;
		// TODO: implement functionality

		//case ETable::SingleImprisonment:
		//case ETable::InfininiteImprisonment:
		//case ETable::DoubleImprisonment:
		//case ETable::TripleImprisonment:
		//	break;
	}

#ifdef _MSC_VER
#pragma warning (default: 4061 4062) // case statement not handled
#endif // _MSC_VER
	
	return *iter;
}
