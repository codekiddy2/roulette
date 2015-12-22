
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

///<summary>
//
//	history.hh
//
//	Declaration of History class
//
//	History object shows history of number outcomes
// Engine class signals spin and sets the result
//
///</summary>

// roulette
#include "error.hh"

// gtkmm
#include <gtkmm/box.h>
#include <glibmm/refptr.h>
#include <gtkmm/textview.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/scrolledwindow.h>

namespace roulette
{
	class History final :
		public Gtk::ScrolledWindow,
		public IErrorHandler
	{
	public:
		// constructors
		History();

		// set spin result to history
		void set_result(unsigned result);

	private:
		// apply formating tags, background and foreground color
		void apply_tags();

		// members
		Gtk::HBox mHBox;

		/// begin initializer list
		Glib::RefPtr<Gtk::TextBuffer::TagTable> mTagTable;

		Glib::RefPtr<Gtk::TextBuffer> refRedBuffer;
		Glib::RefPtr<Gtk::TextBuffer> refBlackBuffer;
		Glib::RefPtr<Gtk::TextBuffer> refGreenBuffer;

		Gtk::TextView mViewRed;
		Gtk::TextView mViewBlack;
		Gtk::TextView mViewGreen;

		Glib::RefPtr<Gtk::TextBuffer::Tag> mTagRed;
		Glib::RefPtr<Gtk::TextBuffer::Tag> mTagBlack;
		Glib::RefPtr<Gtk::TextBuffer::Tag> mTagGreen;
		/// end initializer list

		// deleted
		History(const History&) = delete;
		History(const History&&) = delete;
		History& operator=(const History&) = delete;
		History& operator=(const History&&) = delete;
	};

} // namespace roulette

#endif // ! HISTORY_HH
