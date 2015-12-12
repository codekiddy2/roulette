#ifndef HISTORY_HH
#define HISTORY_HH 1

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

//#include "engine.hh"

#include <glibmm/refptr.h>
#include <gtkmm/box.h>
#include <gtkmm/textview.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/scrolledwindow.h>

class Engine;

class History final
	: public Gtk::ScrolledWindow
{
public:
	// constructors
	History();
	History(const History&) = delete;
	History(const History&&) = delete;
	History& operator=(const History&) = delete;
	History& operator=(const History&&) = delete;

	// methods
	void apply_tags();

	/// begin initializer list
private:
	friend class Engine; // to set result
	Glib::RefPtr<Gtk::TextBuffer::TagTable> mTagTable;
	Glib::RefPtr<Gtk::TextBuffer> refRedBuffer, refBlackBuffer, refGreenBuffer;
	Gtk::TextView mViewRed, mViewBlack, mViewGreen;
	Glib::RefPtr<Gtk::TextBuffer::Tag> mTagRed, mTagBlack, mTagGreen;
	/// end initializer list
	
private:
	// members
	Gtk::HBox mHBox;
};

#endif // ! HISTORY_HH
