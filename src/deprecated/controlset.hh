
#ifndef CONTROLSET_HH
#define CONTROLSET_HH 1

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
//	controlset.hh
//
//	Declaration of Controlset class
//
//	TODO: add description
//
///</summary>

#include "color.hh"
#include "control.hh"

#include <gdkmm/rgba.h>
#include <gtkmm/buttonbox.h>

namespace roulette
{
	class window;

	class Controlset final : 
		public Gtk::ButtonBox,
		public IErrorHandler,
		public Color
	{
	public:
		// constructors
		Controlset();
		~Controlset();

	private:
		// methods
		bool on_controlset_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr);

		friend class Window; // to set signals

		/// begin initialization list
		Control m_BtnClose;
		Control m_BtnSpin;
		Control m_BtnSpin50;
		Control m_BtnClear;
		/// end initialization list

		// deleted
		Controlset(const Controlset&) = delete;
		Controlset(const Controlset&&) = delete;
		Controlset& operator=(const Controlset&) = delete;
		Controlset& operator=(const Controlset&&) = delete;
	};

} // namespace roulette

#endif // ! CONTROLSET_HH
