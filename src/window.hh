
#ifndef WINDOW_HH
#define WINDOW_HH 1

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
//	window.hh
//
//	Declaration of Window class
//
//	Window class constructs other objects and packs them
// Connects objects with signals instead of passing poiners around
//
///</summary>

// roulette
#include "table.hh"
#include "history.hh"
#include "chip.hh"
#include "control.hh"
#include "engine.hh"
#include "infobar.hh"

// gtkmm
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <gdkmm/pixbuf.h>
#include <gdkmm/event.h>
#include <glibmm/refptr.h>

namespace roulette
{
	class Window final :
		public Gtk::Window,
		public IErrorHandler
	{
	public:
		// constructors
		Window(Glib::RefPtr<Gdk::Pixbuf> refIcon);
		virtual ~Window();

	private:
		// methods
		bool on_button_close(GdkEventButton* button_event);
		bool on_button_spin(GdkEventButton* button_event);
		bool on_button_spin50(GdkEventButton* button_event);
		bool on_button_clear(GdkEventButton* button_event);

		// members
		Gtk::HBox m_HBoxTop;
		Gtk::VBox m_VBoxArea;
		Gtk::HBox m_HBoxControls;
		Gtk::ButtonBox m_Chipset;
		Gtk::ButtonBox m_Controlset;

		/// begin initializer list
		Control m_BtnClose;
		Control m_BtnSpin;
		Control m_BtnSpin50;
		Control m_BtnClear;

		// engine must be constructed before infobar and chips
		Engine* mp_engine;
		InfoBar m_infobar;
		// Chips must be constructed before Table because
		// Chips initialize Gtk::TargetEntry used by Field objects for DND
		Chip m_Chip1;
		Chip m_Chip5;
		Chip m_Chip25;
		Chip m_Chip50;
		Chip m_Chip100;
		Chip m_Eraser;
		/// end of initializer list

		Table m_table;
		History m_history;

		// deleted
		Window(const Window&) = delete;
		Window(const Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(const Window&&) = delete;
	};

} // namespace roulette

#endif // ! WINDOW_HH
