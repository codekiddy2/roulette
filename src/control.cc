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
//	control.cc
//
//	Definition of Control class
//
//	TODO: add description
//
///</summary>

#include "pch.hh"
#include "control.hh"

namespace roulette
{
	using std::string;

	Control::Control(const string&& name) :
		BaseControl(name.c_str())
	{
		// make me receive 'clicked' event
		set_events(Gdk::EventMask::BUTTON_PRESS_MASK);
	}

	// Draw on the supplied Cairo::Context.
	bool Control::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
	{
		Gtk::Allocation allocation = get_allocation();
		const int width = allocation.get_width();
		const int height = allocation.get_height();


		// paint the background
		Gdk::Cairo::set_source_rgba(cr, Color::get_background_color());
		cr->paint();

		// stroke lines around filed
		cr->set_source_rgb(1.0, 1.0, 1.0); // white
		cr->set_line_width(1.0);
		cr->move_to(0.0, 0.0);
		cr->line_to(0.0, height);
		cr->line_to(width, height);
		cr->line_to(width, 0.0);
		cr->stroke();

		// show text
		draw_text(cr, width, height);

		return true;
	}

} // namespace roulette
