
#ifndef CONTROL_HH
#define CONTROL_HH 1

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
//	control.hh
//
//	Declaration of Control class
//
//	TODO: add description
//
///</summary>

#include <string>
#include <gtkmm/widget.h>
#include <glibmm/refptr.h>
#include <pangomm/layout.h>
#include <pangomm/fontdescription.h>
#include <gdkmm/rgba.h>
#include <gdkmm/window.h>
#include <gdkmm/rectangle.h> // Gtk::Allocation
#include <cairomm/refptr.h>
#include <cairomm/context.h>

namespace roulette
{
	class Control final
		: public Gtk::Widget
	{
	public:
		// constructors
		Control(const std::string name);

		// methods
		// TODO: consider global background setup
		static void set_background_color(const Gdk::RGBA& color);

	protected:
		// Overrides
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

	private:
		// methods
		void draw_text(const Cairo::RefPtr<Cairo::Context>& cr, int control_width, int control_height);

		// members
		Pango::FontDescription mFont;
		static Gdk::RGBA mBackground;

		/// begin initializer list
		std::string mName;
		Glib::RefPtr<Pango::Layout> mLayout;
		/// end initializer list

		// deleted
		Control(const Control&) = delete;
		Control(const Control&&) = delete;
		Control& operator=(const Control&) = delete;
		Control& operator=(const Control&&) = delete;
	};
} // namespace roulette

#endif // ! CONTROL_HH
