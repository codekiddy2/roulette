
#include "pch.hh"
#include "color.hh"

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
//	color.cc
//
//	Definition of Color class
//
//	TODO: add description
//
///</summary>

namespace roulette
{
	Gdk::RGBA Color::m_background("rgb(0, 102, 0)");
	Gdk::RGBA Color::m_foreground("rgb(255, 255, 255)");

	roulette::Color::Color()
	{
	}

	roulette::Color::~Color()
	{
	}

	const Gdk::RGBA & roulette::Color::get_background_color()
	{
		return m_background;
	}

	const Gdk::RGBA & roulette::Color::get_foreground_color()
	{
		return m_foreground;
	}

	void roulette::Color::set_background_color(const Gdk::RGBA & color)
	{
		m_background = color;
	}

	void roulette::Color::set_foreground_color(const Gdk::RGBA & color)
	{
		m_foreground = color;
	}

} // namespace
