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
//	racetrack.cc
//
//	Definition of Racetrack class
//
// TODO: add description
//
///</summary>

// roulette
#include "pch.hh"
#include "racetrack.hh"
#include "color.hh"

namespace
{

}

namespace roulette
{
	Racetrack::Racetrack() :
		IErrorHandler("Wheel")
	{
		set_size_request(500, 100);
	}

	bool Racetrack::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
	{
		Gtk::Allocation alloc = get_allocation();

		Gdk::Cairo::set_source_rgba(cr, Gdk::RGBA("Yellow"));// Color::get_background_color());

		cr->paint();

		return true;
	}
}