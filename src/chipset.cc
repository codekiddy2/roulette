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

#include "pch.hh"
#include "chipset.hh"

using std::string;
using std::cout;
using std::endl;
using std::cerr;

#ifdef DEBUG_DND_LOG
bool Chipset::constructed = false;
#endif // DEBUG_DND_LOG

int Chipset::chip_size = 48;

Chipset::Chipset() :
	mChip1(1),
	mChip5(5),
	mChip25(25),
	mChip50(50),
	mChip100(100)
{
	pack_end(mChip1, Gtk::PACK_SHRINK);
	pack_end(mChip5, Gtk::PACK_SHRINK);
	pack_end(mChip25, Gtk::PACK_SHRINK);
	pack_end(mChip50, Gtk::PACK_SHRINK);
	pack_end(mChip100, Gtk::PACK_SHRINK);

#ifdef DEBUG_DND_LOG
	Chipset::constructed = true;
#endif // DEBUG_DND_LOG
}

void Chipset::set_chipsize(int size)
{
	chip_size = size;
}

int Chipset::get_chipsize()
{
	return chip_size;
}

#ifdef DEBUG_DND_LOG

bool Chipset::is_constructed()
{
	return constructed;
}

#endif // DEBUG_DND_LOG
