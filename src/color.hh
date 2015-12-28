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

// gtkmm
#include <gdkmm/rgba.h>

namespace roulette
{
#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER

	class Color
	{
	protected:
		// constructors
		inline Color() noexcept;
		inline virtual ~Color() noexcept;

	public:
		// methods
		inline static const Gdk::RGBA& get_background_color() noexcept;
		inline static const Gdk::RGBA& get_foreground_color() noexcept;
		inline static void set_background_color(const Gdk::RGBA& color) noexcept;
		inline static void set_foreground_color(const Gdk::RGBA& color) noexcept;

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

#ifdef _MSC_VER
#pragma endregion begin

#pragma region
#endif // _MSC_VER

	roulette::Color::Color() noexcept
	{
	}

	roulette::Color::~Color() noexcept
	{
	}

	const Gdk::RGBA& roulette::Color::get_background_color() noexcept
	{
		return m_background;
	}

	const Gdk::RGBA& roulette::Color::get_foreground_color() noexcept
	{
		return m_foreground;
	}

	void roulette::Color::set_background_color(const Gdk::RGBA& color) noexcept
	{
		m_background = color;
	}

	void roulette::Color::set_foreground_color(const Gdk::RGBA& color) noexcept
	{
		m_foreground = color;
	}

#ifdef _MSC_VER
#pragma endregion inlines
#endif // _MSC_VER

} // namespace roulette

#endif // !COLOR_HH
