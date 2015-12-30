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

	bool Chipset::constructed = false;

	Chipset::Chipset() :
		IErrorHandler("Chipset"),
		m_Chip1(EChip::Chip1),
		m_Chip5(EChip::Chip5),
		m_Chip25(EChip::Chip25),
		m_Chip50(EChip::Chip50),
		m_Chip100(EChip::Chip100),
		m_Eraser(EChip::Eraser)
	{
		m_BtnBox.pack_end(m_Eraser, Gtk::PACK_SHRINK);
		m_BtnBox.pack_end(m_Chip1, Gtk::PACK_SHRINK);
		m_BtnBox.pack_end(m_Chip5, Gtk::PACK_SHRINK);
		m_BtnBox.pack_end(m_Chip25, Gtk::PACK_SHRINK);
		m_BtnBox.pack_end(m_Chip50, Gtk::PACK_SHRINK);
		m_BtnBox.pack_end(m_Chip100, Gtk::PACK_SHRINK);

		//signal_draw().connect(sigc::mem_fun(this, &Chipset::on_chipset_draw));
		Chipset::constructed = true;
	}

	//void Chipset::set_chipsize(int size)
	//{
	//	chip_size = size;
	//}

	//int Chipset::get_chipsize()
	//{
	//	return chip_size;
	//}

	bool Chipset::is_constructed()
	{
		return constructed;
	}

	bool Chipset::on_chipset_draw(const Cairo::RefPtr<Cairo::Context>& cr)
	{
		Gdk::Cairo::set_source_rgba(cr, Color::get_background_color());
		cr->paint();
		return true;
	}

} // namespace
