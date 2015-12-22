
#ifndef BASE_CONTROL_HH
#define BASE_CONTROL_HH 1

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
//	base_control.hh
//
//	Declaration of BaseControl class
//
// Base class for derived Control classes.
// Controls are a customized buttons to be shown
// on main window
// derived by Control, Chip and Dummy in Window class
//
///</summary>

// roulette
#include "error.hh"
#include "color.hh"

// std
#include <string>

// gtkmm
#include <gtkmm/widget.h>
#include <glibmm/refptr.h>
#include <pangomm/layout.h>
#include <pangomm/fontdescription.h>
#include <gdkmm/window.h>
#include <gdkmm/rectangle.h> // Gtk::Allocation
#include <cairomm/refptr.h>
#include <cairomm/context.h>

namespace roulette
{
	class BaseControl :
		public Gtk::Widget,
		public IErrorHandler,
		public Color
	{
	protected:
		// constructors
		// the name argument will be drawn onto control
		BaseControl(const std::string&& name);
		virtual ~BaseControl();

		// Overrides derived from Gtk::Widget
		Gtk::SizeRequestMode get_request_mode_vfunc() const override;
		void get_preferred_width_vfunc(int& minimum_width, int& natural_width) const override;
		void get_preferred_height_for_width_vfunc(int width, int& minimum_height, int& natural_height) const  override;
		void get_preferred_height_vfunc(int& minimum_height, int& natural_height) const override;
		void get_preferred_width_for_height_vfunc(int height, int& minimum_width, int& natural_width) const override;
		void on_size_allocate(Gtk::Allocation& allocation) override;
		void on_map() override;
		void on_unmap() override;
		void on_realize() override;
		void on_unrealize() override;
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

		// members
		Glib::RefPtr<Gdk::Window> refGdkWindow;

		// methods
		void draw_text(const Cairo::RefPtr<Cairo::Context>& cr, int control_width, int control_height);

		// members
		/// begin initializer list
		std::string m_name;
		Pango::FontDescription m_font;
		Glib::RefPtr<Pango::Layout> m_layout;
		/// end initializer list

	private:
		// deleted
		BaseControl(const BaseControl&) = delete;
		BaseControl(const BaseControl&&) = delete;
		BaseControl& operator=(const BaseControl&) = delete;
		BaseControl& operator=(const BaseControl&&) = delete;
	};

} // namespace roulette

#endif // ! CONTROL_HH
