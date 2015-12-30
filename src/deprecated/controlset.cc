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
//	controlset.cc
//
//	Definition of Controlset class
//
//	TODO: add description
//
///</summary>

#include "pch.hh"
#include "controlset.hh"

namespace roulette
{
	Controlset::Controlset() :
		IErrorHandler("Controlset"),
		m_BtnClose("Close"),
		m_BtnSpin("Spin"),
		m_BtnSpin50("Spin 50x"),
		m_BtnClear("Clear")
	{
		pack_end(m_BtnClear, Gtk::PACK_SHRINK);
		pack_end(m_BtnSpin, Gtk::PACK_SHRINK);
		pack_end(m_BtnSpin50, Gtk::PACK_SHRINK);
		pack_end(m_BtnClose, Gtk::PACK_SHRINK);

		//signal_draw().connect(sigc::mem_fun(this, &Controlset::on_controlset_draw));
	}

	bool Controlset::on_controlset_draw(const Cairo::RefPtr<Cairo::Context>& cr)
	{
		Gdk::Cairo::set_source_rgba(cr, Color::get_background_color());
		cr->paint();
		return false;
	}

} // namespace roulette
