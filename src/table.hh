
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

// roulette
#include "error.hh"
#include "main.hh"

// gtkmm
#include <gtkmm/grid.h>

namespace roulette
{

#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER

	class Table final :
		public Gtk::Grid,
		public IErrorHandler
	{
	public:
		// constructors
		Table(const ETable table_type);
		~Table();

		// clear all chips from the table
		type_signal signal_clear_all;

		// redraw last chips
		type_signal signal_rebet;

		// fields emit bet signals to engine and inforbar
		type_signal_bet signal_bet;

		// check if table limits are reached and inform the player
		bool check_limits(type_chip_container& chips, type_chip& chip);

		// get maximum amount of chips which can be placed for given bet
		uint16 get_limit(const EBet& bet);

		// get table miniums
		uint16 get_minimum(const EMinimum& minimum);

		// set table maximum
		void set_table_max(const uint32& limit = 0);

		// set maximum for bet
		void set_maximum(const EBet& name, const uint16& limit);

		// set table minimum
		void set_minimum(const EMinimum& name, const uint16& minimum);

		// return current table maximum
		inline uint32 get_table_limit() const noexcept;

		// return table type, european, american...
		inline ETable get_table_type() const noexcept;

		// call on_signal_spin for all fields
		void on_signal_spin(uint16 result);
		
		// set debug mode for all table fields
		void set_debug(bool debug) noexcept override;

	private:
		// members
		uint32 m_tablelimit;  // table limit
		type_fields m_fields; // table fields
		type_bet_list m_blacklist; // unsupported bet list
		type_max_container m_maxbets; // count of bet types for given table, Maximum number of EBet that can be placed
		type_min_container m_minimums;	// table minimums
		type_max_container m_maximums;	// table maximums
		type_max_container::iterator m_maxiter; // for constructor and get_limit 

		/// begin initializer list
		ETable m_tabletype;
		uint32 m_tablemax; // maximum amount of chips possible which can be put on the table
		uint16 m_totalbets; // SUM of of all the Bet types that can be placed on a ETable
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

	ETable Table::get_table_type() const noexcept
	{
		return m_tabletype;
	}

	uint32 Table::get_table_limit() const noexcept
	{
		return m_tablelimit;
	}

#ifdef _MSC_VER
#pragma endregion inlines
#endif // _MSC_VER

} // namespace roulette

#endif // ! TABLE_HH
