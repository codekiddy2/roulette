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

#include "pch.hh"
#include "chip.hh"

Gdk::RGBA Chip::mBackground;

Chip::Chip(const std::string file_name) :
	//The GType name will actually be gtkmm__CustomObject_Chip
	Glib::ObjectBase("Chip"),
	Gtk::Widget()
{
	set_has_window(true);

	if (boost::filesystem::exists(file_name))
	{
		refIcon = Gdk::Pixbuf::create_from_file(file_name, 48, 48); // load 48 x 48 version from ico file
	}
}

void Chip::set_background_color(const Gdk::RGBA & color)
{
	mBackground = color;
}

// (optional) Return what Gtk::SizeRequestMode is preferred by the widget.
Gtk::SizeRequestMode Chip::get_request_mode_vfunc() const
{
	//Accept the default value supplied by the base class.
	return Gtk::Widget::get_request_mode_vfunc();
}

// Calculate the minimum and natural width of the widget.
void Chip::get_preferred_width_vfunc(int& minimum_width, int& natural_width) const
{
	// or refIcon->get_width();
	minimum_width = 50;
	natural_width = 50;
}


// Calculate the minimum and natural height of the widget.
void Chip::get_preferred_height_vfunc(int& minimum_height, int& natural_height) const
{
	// or refIcon->get_height();
	minimum_height = 50;
	natural_height = 50;
}

// Calculate the minimum and natural width of the widget, if it would be given the specified height.
void Chip::get_preferred_width_for_height_vfunc(int /* height */,
	int& minimum_width, int& natural_width) const
{
	minimum_width = 50;
	natural_width = 50;
}

// Calculate the minimum and natural height of the widget, if it would be given the specified width.
void Chip::get_preferred_height_for_width_vfunc(int /* width */,
	int& minimum_height, int& natural_height) const
{
	minimum_height = 50;
	natural_height = 50;
}

// Position the widget, given the height and width that it has actually been given.
void Chip::on_size_allocate(Gtk::Allocation& allocation)
{
	//Do something with the space that we have actually been given:
	//(We will not be given heights or widths less than we have requested, though
	//we might get more)

	//Use the offered allocation for this container:
	set_allocation(allocation);

	if (refGdkWindow)
	{
		refGdkWindow->move_resize(allocation.get_x(), allocation.get_y(),
			allocation.get_width(), allocation.get_height());
	}
}

// (optional)
void Chip::on_map()
{
	//Call base class:
	Gtk::Widget::on_map();
}

// (optional)
void Chip::on_unmap()
{
	//Call base class:
	Gtk::Widget::on_unmap();
}

// Associate a Gdk::Window with the widget.
void Chip::on_realize()
{
	//Do not call base class Gtk::Widget::on_realize().
	//It's intended only for widgets that set_has_window(false).

	set_realized();

	if (!refGdkWindow)
	{
		//Create the GdkWindow:

		GdkWindowAttr attributes;
		memset(&attributes, 0, sizeof(attributes));

		Gtk::Allocation allocation = get_allocation();

		//Set initial position and size of the Gdk::Window:
		attributes.x = allocation.get_x();
		attributes.y = allocation.get_y();
		attributes.width = allocation.get_width();
		attributes.height = allocation.get_height();

		attributes.event_mask = get_events() | Gdk::EXPOSURE_MASK;
		attributes.window_type = GDK_WINDOW_CHILD;
		attributes.wclass = GDK_INPUT_OUTPUT;

		refGdkWindow = Gdk::Window::create(get_parent_window(), &attributes,
			GDK_WA_X | GDK_WA_Y);
		set_window(refGdkWindow);

		//make the widget receive expose events
		refGdkWindow->set_user_data(gobj());
	}
}

// (optional) Break the association with the Gdk::Window.
void Chip::on_unrealize()
{
	refGdkWindow.reset();

	//Call base class:
	Gtk::Widget::on_unrealize();
}

// Draw on the supplied Cairo::Context.
bool Chip::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gtk::Allocation allocation = get_allocation();

	// TODO: these variables are used only once, consider removing them
	const double cx = allocation.get_width() * 0.5;
	const double cy = allocation.get_height() * 0.5;

	const int chip_cx = refIcon->get_width() / 2;
	const int chip_cy = refIcon->get_height() / 2;

	// paint the background
	// TODO: background color change will have no affect here
	static double red = mBackground.get_red();
	static double green = mBackground.get_green();
	static double blue = mBackground.get_blue();

	cr->set_source_rgb(red, green, blue);
	cr->paint();

	// draw chip in the middle
	Gdk::Cairo::set_source_pixbuf(cr, refIcon, cx - chip_cx, cy - chip_cy);
	cr->paint();

	return true;
}
