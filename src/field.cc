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
#include "field.hh"
#include "sets.hh"


Field::Field(const int num) :
	//The GType name will actually be gtkmm__CustomObject_Field
	Glib::ObjectBase("Field"),
	Gtk::Widget(),
	mName(std::to_string(num)),
	mBackground("rgb(0, 102, 0)"), // green
	mLayout(create_pango_layout(mName.c_str()))
{
	set_has_window(true);

	mFont.set_family("Sherif");
	mLayout->set_font_description(mFont);

	if (is_red(num))
	{
		mBackground.set("Red");
	}
	else if (num != 0)
	{
		mBackground.set("Black");
	}
}


Field::Field(const std::string text) :
	//The GType name will actually be gtkmm__CustomObject_Field
	Glib::ObjectBase("Field"),
	Gtk::Widget(),
	mName(text),
	mBackground("rgb(0, 102, 0)"), // green
	mLayout(create_pango_layout(text))
{
	set_has_window(true);

	mFont.set_family("Sherif");
	mLayout->set_font_description(mFont);

	if (text == "RED")
	{
		mBackground.set("Red");
	}
	else if (text == "BLACK")
	{
		mBackground.set("Black");
	}
}


// (optional) Return what Gtk::SizeRequestMode is preferred by the widget.
Gtk::SizeRequestMode Field::get_request_mode_vfunc() const
{
	//Accept the default value supplied by the base class.
	return Gtk::Widget::get_request_mode_vfunc();
}

// Calculate the minimum and natural width of the widget.
void Field::get_preferred_width_vfunc(int& minimum_width, int& natural_width) const
{
	minimum_width = 60;
	natural_width = 60;
}


// Calculate the minimum and natural height of the widget.
void Field::get_preferred_height_vfunc(int& minimum_height, int& natural_height) const
{
	minimum_height = 83;
	natural_height = 83;
}

// Calculate the minimum and natural width of the widget, if it would be given the specified height.
void Field::get_preferred_width_for_height_vfunc(int /* height */,
	int& minimum_width, int& natural_width) const
{
	minimum_width = 60;
	natural_width = 60;
}

// Calculate the minimum and natural height of the widget, if it would be given the specified width.
void Field::get_preferred_height_for_width_vfunc(int /* width */,
	int& minimum_height, int& natural_height) const
{
	minimum_height = 83;
	natural_height = 83;
}

// Position the widget, given the height and width that it has actually been given.
void Field::on_size_allocate(Gtk::Allocation& allocation)
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
void Field::on_map()
{
	//Call base class:
	Gtk::Widget::on_map();
}

// (optional)
void Field::on_unmap()
{
	//Call base class:
	Gtk::Widget::on_unmap();
}

// Associate a Gdk::Window with the widget.
void Field::on_realize()
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
void Field::on_unrealize()
{
	refGdkWindow.reset();

	//Call base class:
	Gtk::Widget::on_unrealize();
}

// Draw on the supplied Cairo::Context.
bool Field::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gtk::Allocation allocation = get_allocation();
	const int field_width = allocation.get_width();
	const int field_height = allocation.get_height();
	
	// paint the background
	cr->set_source_rgb(mBackground.get_red(), mBackground.get_green(), mBackground.get_blue());
	cr->paint();

	// stroke lines around filed
	cr->set_source_rgb(1.0, 1.0, 1.0); // white lines
	cr->set_line_width(1.0);
	cr->rectangle(0.0, 0.0, field_width, field_height);
	cr->stroke();

	// show text
	draw_text(cr, field_width, field_height);

	return true;
}

void Field::draw_text(const Cairo::RefPtr<Cairo::Context>& cr,
	int field_width, int field_height)
{
	int text_width;
	int text_height;

	//get the text dimensions (it updates the variables -- by reference)
	mLayout->get_pixel_size(text_width, text_height);

	cr->set_source_rgb(1.0, 1.0, 1.0); // white text
	cr->move_to((field_width - text_width) / 2, (field_height - text_height) / 2);

	mLayout->show_in_cairo_context(cr);
}