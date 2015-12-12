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

#include "table.hh"
#include "history.hh"
#include "chipset.hh"
#include "controlset.hh"

#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/window.h>
#include <gdkmm/pixbuf.h>
#include <gdkmm/event.h>
#include <glibmm/refptr.h>


class Window final :
	public Gtk::Window
{
public:
	// constructors
	Window();
	Window(const Window&) = delete;
	Window(const Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(const Window&&) = delete;

private:
	// members
	Gtk::HBox mHBoxTop;
	Gtk::VBox mVBoxArea;
	Gtk::HBox mHBoxControls;
	Glib::RefPtr<Gdk::Pixbuf> refIcon;

	/// begin initializer list
	Gdk::RGBA mBackground;
	Table mTable;
	Chipset mChipset;
	Controlset mControlset;
	History mHistory;
	Gtk::Frame mFrameHistory;
	Gtk::Frame mFrameBets;
	/// end of initializer list

	// methods
	bool on_button_close(GdkEventButton* button_event);
	bool on_button_spin(GdkEventButton* button_event);
	bool on_button_spin50(GdkEventButton* button_event);
};

#endif // ! WINDOW_HH
