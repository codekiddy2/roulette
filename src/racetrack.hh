
#ifndef RACETRACK_HH
#define RACETRACK_HH 1

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
//	racetrack.hh
//
//	Declaration of Racetrack class
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
	class Racetrack :
		public Gtk::DrawingArea,
		public IErrorHandler
	{
	public:
		// constructors
		Racetrack();

	private:
		// methods
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

		//deleted
		Racetrack(Racetrack&&) = delete;
		Racetrack(const Racetrack&) = delete;
		Racetrack& operator= (Racetrack&&) = delete;
		Racetrack& operator= (const Racetrack&) = delete;
	};
}

#endif // !RACETRACK_HH
