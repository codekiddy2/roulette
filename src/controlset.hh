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

#include "control.hh"

#include <gtkmm/gdkmm/rgba.h>
#include <gtkmm/buttonbox.h>


class Controlset final
	: public Gtk::ButtonBox
{
public:
	// constructors
	Controlset(Gdk::RGBA& color);
	Controlset(const Controlset&) = delete;
	Controlset(const Controlset&&) = delete;
	Controlset& operator=(const Controlset&) = delete;
	Controlset& operator=(const Controlset&&) = delete;

//private:
/// begin initialization list
	Control mBtnClose;
	Control mBtnSpin;
	Control mBtnSpin50;
/// end initialization list
};

#endif // ! CONTROLSET_HH