
#include "stdafx.h"
#include "chip.hh"


Chip::Chip(std::string text) :
	//The GType name will actually be gtkmm__CustomObject_Chip
	Glib::ObjectBase("Chip"),
	Gtk::Widget(),
	mName(text)
{
	set_has_window(true);

	mBackground.set_rgb_p(0.0, 0.5, 0.0);

	if (boost::filesystem::exists(mName))
	{
		refIcon = Gdk::Pixbuf::create_from_file(mName, 48, 48); // load 48 x 48 from ico file
	}

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

	if (m_refGdkWindow)
	{
		m_refGdkWindow->move_resize(allocation.get_x(), allocation.get_y(),
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
void Chip::on_unrealize()
{
	m_refGdkWindow.reset();

	//Call base class:
	Gtk::Widget::on_unrealize();
}

// Draw on the supplied Cairo::Context.
bool Chip::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	const double cx = width * 0.5;
	const double cy = height * 0.5;
	const int chip_cx = refIcon->get_width() / 2;
	const int chip_cy = refIcon->get_height() / 2;

	// paint the background
	static double red = mBackground.get_red_p();
	static double green = mBackground.get_green_p();
	static double blue = mBackground.get_blue_p();

	cr->set_source_rgb(red, green, blue);
	cr->paint();

	// draw chip
	//cr->rectangle(20, 20, refIcon->get_width(), refIcon->get_height());
	//cr->clip();
	Gdk::Cairo::set_source_pixbuf(cr, refIcon, cx - chip_cx, cy - chip_cy);

	//cr->move_to(width / 2, height / 2);
	cr->paint();

	return true;
}
