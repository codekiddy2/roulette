
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
//
// TODO: add description
//
///</summary>

#include "bet.hh"
#include "sets.hh"
#include "error.hh"

#include <map>
#include <string>

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

	class Engine;

	class InfoBar :
		public Gtk::DrawingArea,
		public IErrorHandler
	{
	public:
		// constructors
		InfoBar(Engine* p_engine);

		// signal handlers
		void on_signal_bet(std::shared_ptr<Bet> bet);

	protected:
		// methods
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

	private:
		// typedefs
		typedef Glib::RefPtr<Pango::Layout> type_layout;

		// members
		Engine* mp_engine;
		std::map<ELayout, type_layout> m_layouts;
		Pango::FontDescription font;
		Gdk::RGBA m_foreground = Gdk::RGBA("rgb(0, 190, 0)");
		Gdk::RGBA m_background = Gdk::RGBA("rgb(0, 0, 0)");
		Glib::RefPtr<Gdk::Window> refGdkWindow;
	};

#ifdef _MSC_VER
#pragma endregion begin

#pragma region
#endif // _MSC_VER

#ifdef _MSC_VER
#pragma endregion inlines
#endif // _MSC_VER

} // namespace

#endif // ! INFOBAR_HH
