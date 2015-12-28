
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
#include "types.hh"

namespace roulette
{
	// drag and drop target entry shared by fields and chips
	extern type_dnd_targets dnd_targets;

	// number of bits in a byte, used by drag and drop
	extern const int format;

	// return chip pixbuf associated with the chip enum
	type_chip_icon get_pixbuf(EChip ref);

	// return true if number is red
	bool is_red(const uint16 number) noexcept;

	// return true if number is black
	bool is_black(const uint16 number) noexcept;

	// return true if number is green
	bool is_green(const uint16 number) noexcept;

	// return to which columns a field enum index belongs
	uint16 which_column(EField field) noexcept;

	// return to which column a number belongs
	uint16 which_column(const uint16 number) noexcept;

	// return to which dozen a number belongs
	uint16 which_dozen(const uint16 number) noexcept;

	// return neighboring number on roulette wheel, distance determined by position
	uint16 get_neighbor(const ETable table, const uint16 refNum, const uint16 position);

	// return current pixel size of chips
	int get_chipsize() noexcept;

	// set pixel size of chips
	void set_chipsize(const int size) noexcept;

} // namespace roulette

#endif // ! MAIN_HH
