#ifndef COLOR_HH
#define COLOR_HH 1

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
//	color.hh
//
//	Declaration of Color class
//
//	All clases which inherit from this class will have common background
// and foreground color.
// so that colors do not have to be specified multiple times in on_draw handlers
//
///</summary>

#include <gdkmm/rgba.h>

namespace roulette
{
	class Color
	{
	protected:
		// constructors
		Color();
		virtual ~Color();

	public:
		// methods
		static const Gdk::RGBA& get_background_color();
		static const Gdk::RGBA& get_foreground_color();
		static void set_background_color(const Gdk::RGBA& color);
		static void set_foreground_color(const Gdk::RGBA& color);

	private:
		// members
		static Gdk::RGBA m_background;
		static Gdk::RGBA m_foreground;

		// deleted
		Color(const Color&) = delete;
		Color(const Color&&) = delete;
		Color& operator=(const Color&) = delete;
		Color& operator=(const Color&&) = delete;
	};

} // namespace

#endif // !COLOR_HH
