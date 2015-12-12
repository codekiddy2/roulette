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

#include "field.hh"

#include <vector>
#include <gtkmm/box.h>
#include <gtkmm/grid.h>
#include <gdkmm/rgba.h>


class Table final :
	public Gtk::Box
{
public:
	// constructors
	Table(Gdk::RGBA& color);
	~Table();
	Table(const Table&) = delete;
	Table(const Table&&) = delete;
	Table& operator=(const Table&) = delete;
	Table& operator=(const Table&&) = delete;

private:
	// members
	Gtk::Grid mGrid;
	std::vector<Field*> mFields;
};

#endif // ! TABLE_HH
