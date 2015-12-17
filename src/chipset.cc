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
//	chipset.cc
//
//	Definition of Chipset class
//
//	TODO: add description
//
///</summary>

#include "pch.hh"
#include "chipset.hh"
#include "main.hh"

namespace roulette
{
	using std::string;
	using std::cout;
	using std::endl;
	using std::cerr;

#ifdef DEBUG_DND_LOG
	bool Chipset::constructed = false;
#endif // DEBUG_DND_LOG

	Chipset::Chipset() :
		mChip1(EChip::Chip1),
		mChip5(EChip::Chip5),
		mChip25(EChip::Chip25),
		mChip50(EChip::Chip50),
		mChip100(EChip::Chip100),
		mEraser(EChip::Eraser)
	{
		pack_end(mEraser, Gtk::PACK_SHRINK);
		pack_end(mChip1, Gtk::PACK_SHRINK);
		pack_end(mChip5, Gtk::PACK_SHRINK);
		pack_end(mChip25, Gtk::PACK_SHRINK);
		pack_end(mChip50, Gtk::PACK_SHRINK);
		pack_end(mChip100, Gtk::PACK_SHRINK);

#ifdef DEBUG_DND_LOG
		Chipset::constructed = true;
#endif // DEBUG_DND_LOG
	}

	//void Chipset::set_chipsize(int size)
	//{
	//	chip_size = size;
	//}

	//int Chipset::get_chipsize()
	//{
	//	return chip_size;
	//}

#ifdef DEBUG_DND_LOG

	bool Chipset::is_constructed()
	{
		return constructed;
	}
}

#endif // DEBUG_DND_LOG
