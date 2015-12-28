
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
//	Definition of ETable, EBet.
//	ETable is enumeration of table layouts available to play.
//	EBet is enumeration of all the bet types available to put on the table (Table class).
//	TODO reserve 0th enum and set start at 1
//	c++11 TODO:
//	forward declare enum class ans use short enumeration (not default int)
//	initialize sets in Sets namespace with <set> class, ( some sets need to be ordered )
//
///</summary>

// std
#include <memory> // type_set
#include <vector> // type_raw_set

namespace roulette
{
	// Used by Field
	// Chip enumerations
	enum class EChip: unsigned
	{
		Eraser,
		Chip1 = 1,
		Chip5 = 5,
		Chip25 = 25,
		Chip50 = 50,
		Chip100 = 100
	};

	// used by Table
	// Table layout enumerations
	enum class ETable: unsigned
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

	// used by Bet
	// Bet type enumerations
	enum class EBet: unsigned
	{
		UNDEFINED = 0,
		///<needsSelection>
		StraightUp = 1,
		Split,
		Street,
		Corner,
		Corner0, // 0, 1, 2, 3
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
		Column1 = 38,  // WARNING: from here enum bet the same as enum field
		Column2,	// this matters in calculate point function
		Column3,
		Dozen1,
		Dozen2,
		Dozen3,
		Red,
		Black,
		Even,
		Odd,
		High,
		Low, // end of warning
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
		LIMIT_EXCEEDED,
		///</hasSelection>
	};

	// used by Table
	// Table minimums
	enum class EMinimum: unsigned
	{
		Inside = 1,
		Outside,
		Table
	};

	// used by Fields and Table
	// Table Field enumerations
	enum class EField: unsigned
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
		Number00,
		Column1, // = 38! WARNING: from here enum index the same as enum bet
		Column2, // this matters in calculate points function
		Column3,
		Dozen1,
		Dozen2,
		Dozen3,
		Red,
		Black,
		Even,
		Odd,
		High,
		Low, // end of warning
		Dummy1,
		Dummy2,
		Dummy3,
	};

	// used by InfoBar
	// Layout enumerations
	enum class ELayout : unsigned
	{
		Bankroll,
		TotalBet,
		LastBet,
		Numbers,
		Inside,
		Outside,
		Straight,
		Split,
		Street,
		Corner,
		Line,
		Dozen,
		High_Low,
		Red_Black,
		Even_Odd,
		Column,
		InsideMin, // inside bets minimum
		OutsideMin, // Outside bets minimum
		TableMin,
		TableMax,
	};

#ifdef TU_SETS_CC
	// Explicit instantiation definition
	// typedef-name cannot be used in explicit instantiation.
	template std::vector<unsigned>; // type_raw_set
	template std::shared_ptr<std::vector<unsigned>>; // type_set
#else
	// Explicit instantiation declaration
	// typedef-name cannot be used in explicit instantiation.
	extern template std::vector<unsigned>; // type_raw_set
	extern template std::shared_ptr<std::vector<unsigned>>; // type_set
#endif // !TU_SETS_CC

	// single type declaring a set of numbers in roulette
	// must be vector to preserve numbers order and avoid sorting
	typedef const std::vector<unsigned> type_raw_set;

	// shared pointer to the const set is shared between objects
	typedef std::shared_ptr<type_raw_set> type_set;

	// wheel number sets
	extern type_set NoZeroWheel;
	extern type_set AmericanWheel;
	extern type_set EuropeanWheel;

	// popular bet sets
	extern type_set Low;
	extern type_set Odd;
	extern type_set Red;
	extern type_set Jeu0;
	extern type_set High;
	extern type_set Even;
	extern type_set Jeu79;
	extern type_set Black;
	extern type_set Snake;
	extern type_set Dozen1;
	extern type_set Dozen2;
	extern type_set Dozen3;
	extern type_set Basket;
	extern type_set Column1;
	extern type_set Column2;
	extern type_set Column3;
	extern type_set RedSplits;
	extern type_set BlackSplits;
	extern type_set VoisinsDeZero;
	extern type_set OrphelinsEnPlen;
	extern type_set TriesDuCylindre;
	extern type_set OrphelinsACheval;

	// streets including zero
	extern type_set Street01;
	extern type_set Street02;

	// exceptional corner for zero
	extern type_set Corner0;

	// street sets
	extern type_set Street1;
	extern type_set Street2;
	extern type_set Street3;
	extern type_set Street4;
	extern type_set Street5;
	extern type_set Street6;
	extern type_set Street7;
	extern type_set Street8;
	extern type_set Street9;
	extern type_set Street10;
	extern type_set Street11;
	extern type_set Street12;

	// line sets
	extern type_set Line1;
	extern type_set Line2;
	extern type_set Line3;
	extern type_set Line4;
	extern type_set Line5;
	extern type_set Line6;
	extern type_set Line7;
	extern type_set Line8;
	extern type_set Line9;
	extern type_set Line10;
	extern type_set Line11;

} // namespace roulette

#endif // ! SETS_HH
