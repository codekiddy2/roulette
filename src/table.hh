
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

// std
#include <map>
#include <unordered_map>

// gtkmm
#include <gtkmm/grid.h>
#include <sigc++/signal.h>

namespace roulette
{

#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER

	// forward declarations
	class Field;
	enum class EMinimum : unsigned;

	class Table final :
		public Gtk::Grid,
		public IErrorHandler
	{
	public:
		// constructors
		Table(const ETable table_type);
		~Table();

		// check if table limits are reached and inform the player
		bool check_limits(type_chip_container& chips, type_chip& chip);

		// get maximum amount of chips which can be placed for given bet
		unsigned get_limit(const EBet& bet);

		// get table miniums
		unsigned get_minimum(const EMinimum& minimum);

		// set table maximum
		void set_table_max(const unsigned& limit = 0);

		// set maximum for bet
		void set_maximum(const EBet& name, const unsigned& limit);

		// set table minimum
		void set_minimum(const EMinimum& name, const unsigned& minimum);

		// return current table maximum
		inline unsigned get_table_limit() const noexcept;

		// return table type, european, american...
		inline ETable get_table_type() const noexcept;

		// call on_signal_spin for all fields
		void on_signal_spin(unsigned result);
		
		// clear all chips from the table
		sigc::signal0<void> signal_clear_all;

		// fields emit bet signals to engine and inforbar
		sigc::signal1<void, type_bet> signal_bet;

		// redraw last chips
		sigc::signal0<void> signal_rebet;

		// set debug mode for all table fields
		void set_debug(bool debug) noexcept override;

	private:
		// typedefs
		typedef std::vector<EBet> type_bet_list;
		typedef std::map<EBet, unsigned> type_max_container;
		typedef std::map<EMinimum, unsigned> type_min_container;
		typedef std::unordered_map<EField, Field*> type_fields;

		// members
		type_fields m_fields;
		unsigned m_tablelimit;  // limit of the above
		type_max_container m_maxbets; // count of bet types for given table, Maximum number of EBet that can be placed
		type_bet_list m_blacklist; // unsupported bet list
		type_min_container m_minimums;	// table minimums
		type_max_container m_maximums;	// table maximums
		type_max_container::iterator m_maxiter; // for constructor and get_limit 

		/// begin initializer list
		ETable m_tabletype;
		unsigned m_tablemax; // maximum amount of chips possible which can be put on the table
		unsigned m_totalbets; // SUM of of all the Bet types that can be placed on a ETable
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

	unsigned Table::get_table_limit() const noexcept
	{
		return m_tablelimit;
	}

#ifdef _MSC_VER
#pragma endregion inlines
#endif // _MSC_VER

} // namespace roulette

#endif // ! TABLE_HH
