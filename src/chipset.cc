
#include "pch.hh"
#include "chipset.hh"

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


Chipset::Chipset(Gdk::RGBA& color) :
	mChip1(color, "chip1.ico"),
	mChip5(color, "chip5.ico"),
	mChip25(color, "chip25.ico"),
	mChip50(color, "chip50.ico"),
	mChip100(color, "chip100.ico")
{
	pack_end(mChip1, Gtk::PACK_SHRINK);
	pack_end(mChip5, Gtk::PACK_SHRINK);
	pack_end(mChip25, Gtk::PACK_SHRINK);
	pack_end(mChip50, Gtk::PACK_SHRINK);
	pack_end(mChip100, Gtk::PACK_SHRINK);

	override_background_color(color);
}