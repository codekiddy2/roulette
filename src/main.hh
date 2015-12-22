
#ifndef MAIN_HH
#define MAIN_HH 1

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
//	main.hh
//
//	Declares shared functions and data types
// Supposed to declare most common functions
// to be included in translation units
//
///</summary>

// roulette
#include "bet.hh"

// std
#include <vector>
#include <memory>

// gtkmm
#include <glibmm/refptr.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm/targetentry.h>

namespace roulette
{
	// TODO: use these types in declarations
	typedef unsigned long ulong;
	typedef unsigned short ushort;

	// forward declarations
	enum class ETable: unsigned;
	enum class EChip: unsigned;

	// drag and drop target entry shared by fields and chips
	extern std::vector<Gtk::TargetEntry> dnd_targets;

	// type declaring a bet
	typedef std::shared_ptr<Bet> type_bet;

	// container type to store bets
	typedef std::vector<type_bet> type_bet_container;

	// type declaring a pixbuf icon for a chip
	typedef Glib::RefPtr<Gdk::Pixbuf> type_chip_icon;

	// return chip pixbuf associated with the chip enum
	type_chip_icon get_pixbuf(EChip ref);

	// return true if number is red
	bool is_red(const unsigned number);

	// return true if number is black
	bool is_black(const unsigned number);

	// return true if number is green
	bool is_green(const unsigned number);

	// return to which columns a field enum index belongs
	unsigned which_column(EField field);

	// return to which column a number belongs
	unsigned which_column(const unsigned number);

	// return to which dozen a number belongs
	unsigned which_dozen(const unsigned number);

	// return neighboring number on roulette wheel, distance determined by position
	unsigned get_neighbor(const ETable table, const unsigned refNum, const unsigned position);

	// return current pixel size of chips
	int get_chipsize();

	// set pixel size of chips
	void set_chipsize(const int size);

} // namespace roulette

#endif // ! MAIN_HH
