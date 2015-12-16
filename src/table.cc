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

///<summary
//
//	table.cc
//
//	Definition of Table constructor and table methods
//
//	TODO: add description
//	TODO: (OLD) forward declare enum class ans use short enumeration (not default int)
// TODO: make print_properties print into a widget
//
///</summary>

#include "pch.hh"
#include "chipset.hh"
#include "field.hh"

#pragma warning(push, 4)

#include "table.hh"
#include "error.hh"

namespace roulette
{
	using std::cerr;
	using std::endl;
	using std::cout;
	using std::make_pair;
	using roulette::error;


	Table::Table(const ETable table_type) :
		mTableMax(0),
		mTableType(table_type),
		mTotalBets(0)
	{
		set_column_homogeneous(true);
		set_row_homogeneous(true);

#ifdef DEBUG_DND_LOG

		if (!Chipset::is_constructed())
		{
			cerr << "WARNING Chipset must be constructed before Table, DND will not work" << endl;
			cout << "-> Table::Table(const ETable table_type)" << endl;
		}
#endif // DEBUG_DND_LOG

		// create fields
		EField temp;
		for (size_t i = 0; i < static_cast<size_t>(EField::Dummy3); i++)
		{
			temp = static_cast<EField>(i);
			mFields.insert(make_pair(temp, new Field(temp, this)));
		}

		// zero
		attach(*mFields.find(EField::Number0)->second, 0, 0, 1, 3);

		// dummy1
		attach(*mFields.find(EField::Dummy1)->second, 0, 3, 1, 2);

		// numbers by column: 1, 2 and 3
		for (int col1 = 1, col2 = 2, col3 = 3, col = 1; col3 <= 36; col1 += 3, col2 += 3, col3 += 3, ++col)
		{
			attach(*mFields.find(static_cast<EField>(col3))->second, col, 0, 1, 1);
			attach(*mFields.find(static_cast<EField>(col2))->second, col, 1, 1, 1);
			attach(*mFields.find(static_cast<EField>(col1))->second, col, 2, 1, 1);
		}
		// columns
		attach(*mFields.find(EField::Column3)->second, 13, 0, 1, 1);
		attach(*mFields.find(EField::Column2)->second, 13, 1, 1, 1);
		attach(*mFields.find(EField::Column1)->second, 13, 2, 1, 1);

		// dozens
		attach(*mFields.find(EField::Dozen1)->second, 1, 3, 4, 1);
		attach(*mFields.find(EField::Dozen2)->second, 5, 3, 4, 1);
		attach(*mFields.find(EField::Dozen3)->second, 9, 3, 4, 1);

		// dummy2
		attach(*mFields.find(EField::Dummy2)->second, 13, 3, 1, 2);

		// low/high red/black high/low
		attach(*mFields.find(EField::Low)->second, 1, 4, 2, 1);
		attach(*mFields.find(EField::Even)->second, 3, 4, 2, 1);
		attach(*mFields.find(EField::Red)->second, 5, 4, 2, 1);
		attach(*mFields.find(EField::Black)->second, 7, 4, 2, 1);
		attach(*mFields.find(EField::Odd)->second, 9, 4, 2, 1);
		attach(*mFields.find(EField::High)->second, 11, 4, 2, 1);

		// set up table limits

		// single zero layout
		mMaxBets.insert(make_pair(EBet::StraightUp, 37));
		mMaxBets.insert(make_pair(EBet::Split, 60));
		mMaxBets.insert(make_pair(EBet::Street, 12));
		mMaxBets.insert(make_pair(EBet::Corner, 23));
		mMaxBets.insert(make_pair(EBet::Basket, 0));
		mMaxBets.insert(make_pair(EBet::Line, 11));
		mMaxBets.insert(make_pair(EBet::Column1, 1));
		mMaxBets.insert(make_pair(EBet::Column2, 1));
		mMaxBets.insert(make_pair(EBet::Column3, 1));
		mMaxBets.insert(make_pair(EBet::Dozen1, 1));
		mMaxBets.insert(make_pair(EBet::Dozen2, 1));
		mMaxBets.insert(make_pair(EBet::Dozen3, 1));
		mMaxBets.insert(make_pair(EBet::High, 1));
		mMaxBets.insert(make_pair(EBet::Low, 1));
		mMaxBets.insert(make_pair(EBet::Red, 1));
		mMaxBets.insert(make_pair(EBet::Black, 1));
		mMaxBets.insert(make_pair(EBet::Even, 1));
		mMaxBets.insert(make_pair(EBet::Odd, 1));

		mMaxiter = mMaxBets.begin();

		switch (mTableType)
		{
		case ETable::American:
			// modify maximum number of single EBet that can be placed on a ETable
			mMaxiter->second = 38;
			++mMaxiter;
			mMaxiter->second = 61;
			++mMaxiter;
			mMaxiter->second = 15;
			++mMaxiter;
			mMaxiter->second = 22;
			++mMaxiter;
			mMaxiter->second = 1;
			++mMaxiter;
			mMaxiter->second = 11;

			// blacklisted bets for this table
			mBlacklist.push_back(EBet::Jeu0);
			mBlacklist.push_back(EBet::OrphelinsEnPlen);
			mBlacklist.push_back(EBet::OrphelinsACheval);
			mBlacklist.push_back(EBet::TriesDuCylindre);
			mBlacklist.push_back(EBet::VoisinsDeZero);
			break;

		case ETable::NoZero:
			mMaxiter->second = 36;
			++mMaxiter;
			mMaxiter->second = 57;
			++mMaxiter;
			mMaxiter->second = 10;
			++mMaxiter;
			++mMaxiter;
			mMaxiter->second = 0;

			mBlacklist.push_back(EBet::Jeu0);
			mBlacklist.push_back(EBet::Basket);
			mBlacklist.push_back(EBet::Maximus0);
			mBlacklist.push_back(EBet::Maximus00);
			mBlacklist.push_back(EBet::VoisinsDeZero);
			mBlacklist.push_back(EBet::FinalesEnPlen0);
			mBlacklist.push_back(EBet::FinalesACheval01);
			break;
		case ETable::European:
		case ETable::French:
		case ETable::SingleImprisonment:
		case ETable::DoubleImprisonment:
		case ETable::TripleImprisonment:
		case ETable::InfininiteImprisonment:
		default: // single zero table
			mBlacklist.push_back(EBet::Basket);
			mBlacklist.push_back(EBet::Maximus00);
			break;
		}

		// calculate SUM of total bets
		for (mMaxiter = mMaxBets.begin(); mMaxiter != mMaxBets.end(); ++mMaxiter)
			mTotalBets += mMaxiter->second;

		// Insert initial miminums
		mMinimums.insert(make_pair(EMinimum::Inside, 1));
		mMinimums.insert(make_pair(EMinimum::Outside, 1));
		mMinimums.insert(make_pair(EMinimum::Table, 1));

		//Insert initial maximums
		mMaximums.insert(make_pair(EBet::StraightUp, 20));
		mMaximums.insert(make_pair(EBet::Split, 40));
		mMaximums.insert(make_pair(EBet::Street, 60));
		mMaximums.insert(make_pair(EBet::Corner, 80));
		mMaximums.insert(make_pair(EBet::Basket, 80));
		mMaximums.insert(make_pair(EBet::Line, 120));
		mMaximums.insert(make_pair(EBet::Column1, 200));
		mMaximums.insert(make_pair(EBet::Column2, 200));
		mMaximums.insert(make_pair(EBet::Column3, 200));
		mMaximums.insert(make_pair(EBet::Dozen1, 200));
		mMaximums.insert(make_pair(EBet::Dozen2, 200));
		mMaximums.insert(make_pair(EBet::Dozen3, 200));
		mMaximums.insert(make_pair(EBet::Red, 400));
		mMaximums.insert(make_pair(EBet::Black, 400));
		mMaximums.insert(make_pair(EBet::Even, 400));
		mMaximums.insert(make_pair(EBet::Odd, 400));
		mMaximums.insert(make_pair(EBet::High, 400));
		mMaximums.insert(make_pair(EBet::Low, 400));

		SetTableMax();
	}

	Table::~Table()
	{
		for (size_t i = 0; i <= mFields.size(); i++)
		{
			delete mFields.at(static_cast<EField>(i));
		}
	}

	ETable Table::get_table_type()
	{
		return mTableType;
	}

	void Table::SetTableMax(const short& limit /*= 0*/)
	{
		if (limit > GetLimit(EBet::Red))
		{
			mTableMax = limit;
			return;
		}

		if (limit) // if limit is not 0
			limit > 0 ? throw error("CTable -> SetTableMax -> Table max smaler then even oney bet") : throw error("CTable -> SetMinimum -> Table limit too low");

		// if limit is zero it will be calculated according to maximum bets possible
		mTableMax = 0;
		mMaxiter = mMaxBets.begin();
		for (auto btMax = mMaximums.begin(); btMax != mMaximums.end(); ++mMaxiter, ++btMax)
			mTableMax += mMaxiter->second * btMax->second;
	}

	void Table::PrintProperties() const
	{
		using std::cout;
		using std::endl;

		cout << "Table properties" << endl;
		cout << "**************************" << endl << endl;
		cout << "Layout	";
		switch (mTableType)
		{
		case ETable::NoZero:
			cout << "	No zerro" << endl;
			break;
		case ETable::American:
			cout << "	American" << endl;
			break;
		case ETable::European:
			cout << "	European" << endl;
			break;
		case ETable::French:
			cout << "	French ";
			switch (mTableType)
			{
			case ETable::SingleImprisonment:
				cout << "single imprisonment" << endl;
				break;
			case ETable::DoubleImprisonment:
				cout << "double imprisonment" << endl;
				break;
			case ETable::TripleImprisonment:
				cout << "triple imprisonment" << endl;
				break;
			case ETable::InfininiteImprisonment:
				cout << "infinite imprisonment" << endl;
				break;
			default:
				cout << endl;
				break;
			} //single zero table
			cout << "Maximum bets    " << mTotalBets << endl;
			break;
		}
		cout << "Inside min.	" << mMinimums.at(EMinimum::Inside) << endl;
		cout << "Outside min.	" << mMinimums.at(EMinimum::Outside) << endl;
		cout << "Table min.	" << mMinimums.at(EMinimum::Table) << endl;
		cout << "Table max.	" << mTableMax << endl;
		cout << "StraightUp	" << mMaximums.at(EBet::StraightUp) << endl;
		cout << "Split		" << mMaximums.at(EBet::Split) << endl;
		cout << "Street		" << mMaximums.at(EBet::Street) << endl;
		cout << "Corner		" << mMaximums.at(EBet::Corner) << endl;
		cout << "Basket		" << mMaximums.at(EBet::Basket) << endl;
		cout << "Line		" << mMaximums.at(EBet::Line) << endl;
		cout << "Column/Dozen	" << mMaximums.at(EBet::Column1) << endl;
		cout << "EvenMoney	" << mMaximums.at(EBet::Red) << endl;
	}

#pragma warning(pop)

} // namespace roulette
