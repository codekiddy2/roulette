
#include "stdafx.h"
#include "field.hpp"
#include "NumberSets.hpp"

Field::Field(int num) :
	//The GType name will actually be gtkmm__CustomObject_Field
	Glib::ObjectBase("Field"),
	Gtk::Widget(),
	mName(std::to_string(num)),
	mLayout(create_pango_layout(mName.c_str()))
{
	set_has_window(true);

	mFont.set_family("Sherif");
	mLayout->set_font_description(mFont);

	if (num == 0)
	{
		mBackground.set_rgb_p(0.0, 0.5, 0.0);
	}
	else if (IsRed(num))
	{
		mBackground.set("Red");
	}
	else
	{
		mBackground.set("Black");
	}
}


Field::Field(std::string text) :
	//The GType name will actually be gtkmm__CustomObject_Field
	Glib::ObjectBase("Field"),
	Gtk::Widget(),
	mName(text),
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
	else
	{
		mBackground.set_rgb_p(0.0, 0.5, 0.0);
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

	if (m_refGdkWindow)
	{
		m_refGdkWindow->move_resize(allocation.get_x(), allocation.get_y(),
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

	if (!m_refGdkWindow)
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

		m_refGdkWindow = Gdk::Window::create(get_parent_window(), &attributes,
			GDK_WA_X | GDK_WA_Y);
		set_window(m_refGdkWindow);

		//make the widget receive expose events
		m_refGdkWindow->set_user_data(gobj());
	}
}

// (optional) Break the association with the Gdk::Window.
void Field::on_unrealize()
{
	m_refGdkWindow.reset();

	//Call base class:
	Gtk::Widget::on_unrealize();
}

// Draw on the supplied Cairo::Context.
bool Field::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();


	// paint the background
	double red = mBackground.get_red_p();
	double green = mBackground.get_green_p();
	double blue = mBackground.get_blue_p();

	cr->set_source_rgb(red, green, blue);
	cr->paint();

	// stroke lines around filed
	cr->set_source_rgb(1.0, 1.0, 1.0);
	cr->set_line_width(1.0);
	cr->rectangle(0.0, 0.0, width, height);
	cr->stroke();

	// show text
	draw_text(cr, width, height);

	return true;
}

void Field::draw_text(const Cairo::RefPtr<Cairo::Context>& cr,
	int rectangle_width, int rectangle_height)
{
	int text_width;
	int text_height;

	//get the text dimensions (it updates the variables -- by reference)
	mLayout->get_pixel_size(text_width, text_height);

	static Gdk::Color color("White");
	static double red = color.get_red();
	static double green = color.get_green();
	static double blue = color.get_blue();

	cr->set_source_rgb(red, green, blue);

	cr->move_to((rectangle_width - text_width) / 2, (rectangle_height - text_height) / 2);

	mLayout->show_in_cairo_context(cr);
}