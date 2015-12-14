
#ifndef SETS_HH
#define SETS_HH 1

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
//	sets.hh
//
//	Sets header contains number sets of roulette wheel and enumerations.
//	Definition of ETable, EBet and CErrorCode class.
//	ETable is enumeration of table layouts available to play.
//	EBet is enumeration of all the bet types available to put on the table (Table class).
//	TODO reserve 0th enum and set start at 1
//	c++11 TODO:
//	forward declare enum class ans use short enumeration (not default int)
//	mark classes final
//	initialize sets in Sets namespace with <set> class
//
///</summary>

#include <vector>	// set_t

namespace roulette
{
	enum class ETable
	{
		NoZero = 36,
		European,
		American,
		French,
		SingleImprisonment,
		DoubleImprisonment,
		TripleImprisonment,
		InfininiteImprisonment,
	};

	bool is_red(const int number);
	short which_column(const short number);
	short which_dozen(const short number);
	short get_neighbor(const ETable table, const short refNum, const short position);

	// TODO: consider using unordered set to avoid vector messing with numbers
	typedef const std::vector<unsigned> set_t;

	extern set_t NoZeroWheel;
	extern set_t AmericanWheel;
	extern set_t EuropeanWheel;

	extern set_t Low;
	extern set_t Odd;
	extern set_t Red;
	extern set_t Jeu0;
	extern set_t High;
	extern set_t Even;
	extern set_t Jeu79;
	extern set_t Black;
	extern set_t Snake;
	extern set_t Dozen1;
	extern set_t Dozen2;
	extern set_t Dozen3;
	extern set_t Basket;
	extern set_t Column1;
	extern set_t Column2;
	extern set_t Column3;
	extern set_t RedSplits;
	extern set_t BlackSplits;
	extern set_t VoisinsDeZero;
	extern set_t OrphelinsEnPlen;
	extern set_t TriesDuCylindre;
	extern set_t OrphelinsACheval;

	extern const short basket[];
	extern const short low[];
	extern const short high[];
	extern const short red[];
	extern const short black[];
	extern const short even[];
	extern const short odd[];
	extern const short column1[];
	extern const short column2[];
	extern const short column3[];
	extern const short dozen1[];
	extern const short dozen2[];
	extern const short dozen3[];
	extern const short snake[];
	extern const short redSplits[];
	extern const short blackSplits[];
	extern const short orphelinsEnPlen[];
	extern const short triesDuCylindre[];
	extern const short voisinsDeZero[];
	extern const short orphelinsACheval[];
	extern const short jeu0[];
	extern const short jeu79[];
	extern const short euroWheel[];
	extern const short amWheel[];
	extern const short noZeroWheel[];

	enum class EBet/* : short*/
	{
		///<needsSelection>
		StraightUp,
		Split,
		Street,
		Corner,
		Line,
		Neighbor1,
		Neighbor2,
		Neighbor3,
		Neighbor4,
		Neighbor5,
		Maximus13,
		Maximus3436,
		MaximusColumn2,
		MaximusColumn13,
		///</needsSelection>

		///<hasSelection>
		///<fieldNameContinues>
		Column1 = 38,
		Column2,
		Column3,
		Dozen1,
		Dozen2,
		Dozen3,
		Red,
		Black,
		Even,
		Odd,
		High,
		Low,
		///</fieldNameContinues>

		Basket,
		Maximus00,
		Maximus0,
		Maximus2,
		Maximus35,
		VoisinsDeZero,
		TriesDuCylindre,
		OrphelinsEnPlen,
		OrphelinsACheval,
		Jeu0,
		Jeu79,
		RedSplits,
		BlackSplits,
		Snake,
		FinalesEnPlen0,
		FinalesEnPlen1,
		FinalesEnPlen2,
		FinalesEnPlen3,
		FinalesEnPlen4,
		FinalesEnPlen5,
		FinalesEnPlen6,
		FinalesEnPlen7,
		FinalesEnPlen8,
		FinalesEnPlen9,
		FinalesACheval01,
		FinalesACheval12,
		FinalesACheval23,
		FinalesACheval34,
		FinalesACheval45,
		FinalesACheval56,
		FinalesACheval67,
		FinalesACheval78,
		FinalesACheval89,
		FinalesACheval910,
		FinalesACheval03,
		FinalesACheval14,
		FinalesACheval25,
		FinalesACheval36,
		FinalesACheval47,
		FinalesACheval58,
		FinalesACheval69,
		FinalesACheval710,
		FinalesACheval811,
		FinalesACheval912,
		///</hasSelection>
	};

	enum class EMinimum
	{
		Inside = 1,
		Outside,
		Table
	};

	enum class EField
	{
		Number0,
		Number1,
		Number2,
		Number3,
		Number4,
		Number5,
		Number6,
		Number7,
		Number8,
		Number9,
		Number10,
		Number11,
		Number12,
		Number13,
		Number14,
		Number15,
		Number16,
		Number17,
		Number18,
		Number19,
		Number20,
		Number21,
		Number22,
		Number23,
		Number24,
		Number25,
		Number26,
		Number27,
		Number28,
		Number29,
		Number30,
		Number31,
		Number32,
		Number33,
		Number34,
		Number35,
		Number36,
		Number37,
		Column1,
		Column2,
		Column3,
		Dozen1,
		Dozen2,
		Dozen3,
		Red,
		Black,
		Even,
		Odd,
		High,
		Low,
	};
} // namespace roulette
#endif // ! SETS_HH
