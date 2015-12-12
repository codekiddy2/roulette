
#include "pch.hh"
#include "controlset.hh"

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


Controlset::Controlset(Gdk::RGBA& color) :
	mBtnClose(color, "Close"),
	mBtnSpin(color, "Spin"),
	mBtnSpin50(color, "Spin 50x")
{
	pack_end(mBtnClose, Gtk::PACK_SHRINK);
	pack_end(mBtnSpin, Gtk::PACK_SHRINK);
	pack_end(mBtnSpin50, Gtk::PACK_SHRINK);

	//override_background_color(color);
}
