
#ifndef INFOBAR_HH
#define INFOBAR_HH 1

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
// infobar.hh
//
// Infobar class shows current game status,
// calculations and table minimums/maximums
//
///</summary>

// roulette
#include "error.hh"
#include "main.hh"

// gtkmm
#include <glibmm/refptr.h>
#include <cairomm/context.h>
#include <gdkmm/rgba.h>
#include <pangomm/font.h>
#include <pangomm/layout.h>
#include <gtkmm/drawingarea.h>
#include <gdkmm/window.h>

namespace roulette
{

#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER

	class Table;
	class Engine;

	class InfoBar :
		public Gtk::DrawingArea,
		public IErrorHandler
	{
	public:
		// constructors
		InfoBar(Engine* p_engine, Table* p_table);

		// table will signal a bet and execute this handler
		// it will also execute this handler in case of clear_all_bets
		// argument is not used, it's just a placeholder for compatibility with
		// both signals, on_update uses mp_engine pointer to do updates
		void on_update(type_bet /*bet*/);

	protected:
		// methods
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

	private:
		// members
		Engine* mp_engine;
		Table* mp_table;
		Pango::FontDescription font;
		Gdk::RGBA m_foreground = Gdk::RGBA("rgb(0, 190, 0)");
		Gdk::RGBA m_background = Gdk::RGBA("rgb(0, 0, 0)");
		type_layout_container m_layouts;
		Glib::RefPtr<Gdk::Window> refGdkWindow;

		// deleted
		InfoBar(const InfoBar&) = delete;
		InfoBar(const InfoBar&&) = delete;
		InfoBar& operator=(const InfoBar&) = delete;
		InfoBar& operator=(const InfoBar&&) = delete;
	};

#ifdef _MSC_VER
#pragma endregion begin
#endif // _MSC_VER

} // namespace roulette

#endif // ! INFOBAR_HH
