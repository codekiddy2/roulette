
#ifndef TABLE_HH
#define TABLE_HH 1

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
//	table.hh
//
//	Declaration of Table class.
//	Table object is used to place Bet and Chip objects on it and sum the returns, wins and looses.
//	A roulette table has limits such as table maximum or minimum allowed for ie. red field.
//	Field class is a construction part of Table class.
//	Each field represent an field on roulette table like Red, black etc.
//	While table class is a complete roulette table constructed from other construction parts.
//
///</summary>

#include "sets.hh"
#include "error.hh"

#include <vector>
#include <gtkmm/grid.h>
#include <gdkmm/rgba.h>
#include <sigc++/signal.h>
#include <map>

namespace roulette
{
	// TODO: temporary
	using roulette::error;

	class Field;

	class Table final :
		public Gtk::Grid,
		public roulette::IErrorHandler
	{
	public:
		// constructors
		Table(const ETable table_type = ETable::European);
		virtual ~Table();

		// methods
		ETable get_table_type();
		void PrintProperties() const;
		int GetLimit(const EBet& bet);
		void error_handler(const error&& ref);
		void SetTableMax(const short& limit = 0);
		void SetMaximum(const EBet& name, const short& limit);
		void SetMinimum(const EMinimum& name, const short& minimum);


		// signals
		sigc::signal<void> signal_clear;

	private:
		// typedefs
		typedef std::vector<EBet> BetList;
		typedef std::map<EBet, int> MaxContainer;
		typedef std::map<EMinimum, short> MinContainer;

		// members
		std::vector<Field*> mFields;

		int mTableMax;
		float mResult;

		// SUM of maximum number of all the BetNames that can be placed on a ETable
		int mTotalBets;

		// Maximum number of n EBet that can be placed, separated into container.
		MaxContainer mMaxBets;

		BetList mBlacklist; // unsupported bet list
		MinContainer mMinimums;	// table minimums
		MaxContainer mMaximums;	// table maximums

		MaxContainer::iterator mMaxiter;	// due to constructor and GetLimit 

		/// begin initializer list
		ETable mTableType;
		/// end initializer list

		// deleted
		Table(const Table&) = delete;
		Table(const Table&&) = delete;
		Table& operator=(const Table&) = delete;
		Table& operator=(const Table&&) = delete;
	};

	inline int Table::GetLimit(const EBet& name)
	{
		if ((mMaxiter = mMaximums.find(name)) == mMaximums.end())
			error_handler(error("Table -> GetLimit -> iterator out of range"));

		return mMaxiter->second;
	}

	inline void Table::SetMinimum(const EMinimum& name, const short& minimum)
	{
		if (name == EMinimum::Table && (minimum < 0))
			error_handler(error("Table -> SetMinimum -> Table minimum less then 0"));

		minimum > 1 ? mMinimums.find(name)->second = minimum :
			error_handler(error("Table -> SetMinimum -> Bet minimum less then 1"));
	}

	inline void Table::SetMaximum(const EBet& name, const short& limit)
	{
		(mMaxiter = mMaximums.find(name)) != mMaximums.end() ? mMaxiter->second = limit :
			error_handler(error("Table -> SetMaximum -> Iterator out of range"));
	}

	inline void Table::error_handler(const error&& ref)
	{
		// TODO: implement functionality
		throw ref;
	}
} // namespace roulette

#endif // ! TABLE_HH
