
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
//	TODO: add description
//
///</summary>

#include <string>
#include <glibmm/refptr.h>
#include <gtkmm/box.h>
#include <gtkmm/textview.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/scrolledwindow.h>

namespace roulette
{
	class History final
		: public Gtk::ScrolledWindow
	{
	public:
		// constructors
		History();

		// methods
		void apply_tags();

		inline void set_red_buffer_text(std::string text);
		inline void set_black_buffer_text(std::string text);
		inline void set_green_buffer_text(std::string text);

		inline Glib::ustring get_red_buffer_text() const;
		inline Glib::ustring get_black_buffer_text() const;
		inline Glib::ustring get_green_buffer_text() const;

	private:
		// members
		Gtk::HBox mHBox;

		/// begin initializer list
		Glib::RefPtr<Gtk::TextBuffer::TagTable> mTagTable;
		Glib::RefPtr<Gtk::TextBuffer> refRedBuffer, refBlackBuffer, refGreenBuffer;
		Gtk::TextView mViewRed, mViewBlack, mViewGreen;
		Glib::RefPtr<Gtk::TextBuffer::Tag> mTagRed, mTagBlack, mTagGreen;
		/// end initializer list

		// deleted
		History(const History&) = delete;
		History(const History&&) = delete;
		History& operator=(const History&) = delete;
		History& operator=(const History&&) = delete;
	};

#ifdef _MSC_VER
	//#pragma warning (disable: 4514) // TODO: unreferenced inline function has been removed
#endif // _MSC_VER

	void History::set_red_buffer_text(std::string text)
	{
		refRedBuffer->set_text(text);
	}

	void History::set_black_buffer_text(std::string text)
	{
		refBlackBuffer->set_text(text);
	}

	void History::set_green_buffer_text(std::string text)
	{
		refGreenBuffer->set_text(text);
	}

	Glib::ustring History::get_red_buffer_text() const
	{
		return refRedBuffer->get_text();
	}

	Glib::ustring History::get_black_buffer_text() const
	{
		return refBlackBuffer->get_text();
	}

	Glib::ustring History::get_green_buffer_text() const
	{
		return refGreenBuffer->get_text();
	}

#ifdef _MSC_VER
	//#pragma warning (default: 4514) // unreferenced inline function has been removed
#endif // _MSC_VER
} // namespace roulette

#endif // ! HISTORY_HH
