
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
#include "bet.hh"

#include <map>
#include <memory>
#include <vector>
#include <unordered_map>

#include <gtkmm/grid.h>
#include <sigc++/signal.h>

namespace roulette
{

#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER

	class Field;

	class Table final :
		public Gtk::Grid,
		public IErrorHandler
	{
	public:
		// constructors
		Table(const ETable table_type = ETable::European);
		~Table();

		// methods
		int get_limit(const EBet& bet);
		void print_properties() const;
		void set_table_max(const short& limit = 0);
		void set_maximum(const EBet& name, const short& limit);
		void set_minimum(const EMinimum& name, const short& minimum);

		inline ETable get_table_type() const;
		inline void error_handler(const error&& ref);
		
		// signals
		sigc::signal<void> signal_clear;
		sigc::signal<void, std::shared_ptr<Bet>> signal_bet; // fields emit bet signals

	private:
		// typedefs
		typedef std::vector<EBet> type_bet_list;
		typedef std::map<EBet, int> type_max_container;
		typedef std::map<EMinimum, short> type_min_container;
		typedef std::unordered_map<EField, Field*> type_fields;

		// members
		type_fields m_fields;
		int m_tablemax;
		float m_result;

		// SUM of maximum number of all the BetNames that can be placed on a ETable
		int m_totalbets;

		// Maximum number of n EBet that can be placed, separated into container.
		type_max_container m_maxbets;
		type_bet_list m_blacklist; // unsupported bet list
		type_min_container m_minimums;	// table minimums
		type_max_container m_maximums;	// table maximums

		type_max_container::iterator m_maxiter; // for constructor and get_limit 

		/// begin initializer list
		ETable m_tabletype;
		/// end initializer list

		// deleted
		Table(const Table&) = delete;
		Table(const Table&&) = delete;
		Table& operator=(const Table&) = delete;
		Table& operator=(const Table&&) = delete;
	};

#ifdef _MSC_VER
#pragma endregion begin

#pragma region
#endif // _MSC_VER

	ETable Table::get_table_type() const
	{
		return m_tabletype;
	}

	void Table::error_handler(const error&& ref)
	{
		// TODO: implement functionality
		throw ref;
	}

#ifdef _MSC_VER
#pragma endregion inlines
#endif // _MSC_VER

} // namespace roulette

#endif // ! TABLE_HH
