
#ifndef WHEEL_HH
#define WHEEL_HH 1

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
//	wheel.hh
//
//	Declaration of Wheel class
//
// TODO: add description
//
///</summary>

// roulette
#include "error.hh"

// gtkmm
#include <gtkmm/drawingarea.h>

namespace roulette
{
	class Wheel :
		public Gtk::DrawingArea,
		public IErrorHandler
	{
	public:
		// constructors
		Wheel();

	private:
		// methods
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

		//deleted
		Wheel(Wheel&&) = delete;
		Wheel(const Wheel&) = delete;
		Wheel& operator= (Wheel&&) = delete;
		Wheel& operator= (const Wheel&) = delete;
	};
}

#endif // WHEEL_HH
