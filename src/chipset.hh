
#ifndef CHIPSET_HH
#define CHIPSET_HH 1

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
//	chipset.hh
//
//	Declaration of Chipset class
//
//	TODO: add description
//
///</summary>

#include "chip.hh"
#include "color.hh"

#include <gdkmm/rgba.h>
#include <gtkmm/buttonbox.h>

namespace roulette
{
	class Chipset final :
		public IErrorHandler,
		public Color
	{
	public:
		// constructors
		Chipset();

		// methods
		// TODO: if table resizes it should change chip sizes, this belongs to Table class.
		//static void set_chipsize(int size);
		//static int get_chipsize();

		static bool is_constructed();

	private:
		// methods
		bool on_chipset_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr);

		static bool constructed;
		Gtk::ButtonBox m_BtnBox;
		//static int chip_size;

		/// begin initializer list
		Chip m_Chip1;
		Chip m_Chip5;
		Chip m_Chip25;
		Chip m_Chip50;
		Chip m_Chip100;
		Chip m_Eraser;
		/// end initializer list

		// deleted
		Chipset(const Chipset&) = delete;
		Chipset(const Chipset&&) = delete;
		Chipset& operator=(const Chipset&) = delete;
		Chipset& operator=(const Chipset&&) = delete;
	};
} // namespace roulette

#endif // ! CHIPSET_HH
