
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
//	Contains shared functions and data declarations
//
//	TODO: add description
//
///</summary>

#include "sets.hh"

#include <glibmm/refptr.h>
#include <gdkmm/pixbuf.h>

namespace roulette
{
	enum class ETable: unsigned;
	enum class EChip: unsigned;

	extern std::vector<Gtk::TargetEntry> dnd_targets;
	typedef Glib::RefPtr<Gdk::Pixbuf> type_chip_icon;

	type_chip_icon get_pixbuf(EChip ref);

	bool is_red(const unsigned number);
	bool is_black(const unsigned number);
	bool is_green(const unsigned number);

	unsigned which_column(EField field);
	unsigned which_column(const unsigned number);
	unsigned which_dozen(const unsigned number);
	unsigned get_neighbor(const ETable table, const unsigned refNum, const unsigned position);

	void set_chipsize(const int size);
	int get_chipsize();

} // namespace

#endif // ! MAIN_HH
