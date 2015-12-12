#ifndef CHIPSET_HH
#define CHIPSET_HH 1

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

#include "chip.hh"

#include <gdkmm/rgba.h>
#include <gtkmm/buttonbox.h>


class Chipset final
	: public Gtk::ButtonBox
{
public:
	// constructors
	Chipset(const Gdk::RGBA& color);
	Chipset(const Chipset&) = delete;
	Chipset(const Chipset&&) = delete;
	Chipset& operator=(const Chipset&) = delete;
	Chipset& operator=(const Chipset&&) = delete;

private:
	/// begin initializer list
	Chip mChip1;
	Chip mChip5;
	Chip mChip25;
	Chip mChip50;
	Chip mChip100;
	/// end initializer list
};

#endif // ! CHIPSET_HH