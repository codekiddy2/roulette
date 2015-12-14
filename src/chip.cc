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
//	chip.cc
//
//	Definition of Chip class
//
//	TODO: add description
//
///</summary>

#include "pch.hh"
#include "chip.hh"
#include "chipset.hh"

namespace roulette
{
	using std::cerr;
	using std::endl;
	using std::cout;
	using std::string;

#ifdef _MSC_VER
#pragma region begin
#endif // _MSC_VER

	Gdk::RGBA Chip::mBackground;
	std::vector<Gtk::TargetEntry> dnd_targets;

	Chip::Chip(const int chip_value) :
		Glib::ObjectBase("Chip"), // The GType name will be gtkmm__CustomObject_Chip
		Gtk::Widget(),
		mValue(chip_value)
	{
		set_has_window(true);
		set_events(Gdk::EventMask::BUTTON_PRESS_MASK); // TODO: implement chip behaviour for other masks

		// set up chip icon

		string chip_name = "Chip" + std::to_string(chip_value);
		string file_name = chip_name + ".ico";


		if (boost::filesystem::exists(file_name))
		{
			int chip_size = Chipset::get_chipsize();
			refIcon = Gdk::Pixbuf::create_from_file(file_name, chip_size, chip_size); // load size x size version from ico file
		}
#ifdef DEBUG_FILE_LOG
		else
		{
			cout << "Chip::Chip(const int value)" << endl;
			cerr << "-> ERROR: " << file_name << " not found" << endl;
		}
#endif // DEBUG_FILE_LOG

		// Make this Chip a drag source
		std::vector<Gtk::TargetEntry> this_source;
		Gtk::TargetEntry entry(chip_name, Gtk::TargetFlags::TARGET_OTHER_WIDGET, static_cast<guint>(chip_value));

		dnd_targets.push_back(entry);
		this_source.push_back(entry);

		drag_source_set(this_source, Gdk::ModifierType::BUTTON1_MASK, Gdk::ACTION_COPY);
	}

#ifdef _MSC_VER
#pragma endregion

#pragma region dnd
#endif //_MSC_VER

	/*
	The source widget will emit these signals, in this order:

	drag_begin:
	Provides DragContext.

	drag_data_get:
	Provides info about the dragged data format, and a Gtk::SelectionData structure,
	in which you should put the requested data.

	drag_end:
	Provides DragContext.
	*/


#ifdef _MSC_VER
	// #pragma warning (disable: 4100) // TODO: unreferenced formal parameter
#endif // _MSC_VER


	void Chip::on_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context)
	{
		context->set_icon(refIcon, // the GdkPixbuf to use as the drag icon.
			refIcon->get_width() / 2, // the X offset within widget of the hotspot.
			refIcon->get_height() / 2); // the Y offset within widget of the hotspot.

#ifdef DEBUG_DND_LOG
		cout << endl;
		cout << "Chip::on_drag_begin()" << endl;
		cout << "-> INFO: context->set_icon()" << endl;
		cout << "-> INFO: pixel pointer = " << refIcon->get_pixels() << endl;
#endif // DEBUG_DND_LOG
	}


	void Chip::on_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& /*context*/,
		Gtk::SelectionData& selection_data, guint info, guint time)
	{
		static const int format = 8;

		selection_data.set(selection_data.get_target(), format, nullptr, 0);

#ifdef DEBUG_DND_LOG
		cout << endl;
		cout << "Chip::on_drag_data_get()" << endl;;
		cout << "-> INFO: target: " << selection_data.get_target() << endl;
		cout << "-> INFO: pointer: " << selection_data.get_data() << endl;
		cout << "-> INFO: length: " << selection_data.get_length() << endl;
		cout << "-> INFO: format = " << format << endl;
		cout << "-> INFO: info = " << info << endl;
		cout << "-> INFO: time = " << time << endl;
#endif // DEBUG_DND_LOG

#ifdef DEBUG_DND_VERBOSE
		if (selection_data.set_pixbuf(refIcon))
		{
			Glib::RefPtr<const Gdk::Pixbuf> temp = selection_data.get_pixbuf();
			cout << "-> INFO: pixbuf size = " << temp->get_byte_length() << endl;
		}
		else
		{
			cerr << "-> WARNING: get_pixbuf() did not return a pixbuf" << endl;
			cout << "-> INFO: if targets include image = " << selection_data.targets_include_image(false) << endl;
		}
#endif // DEBUG_DND_VERBOSE
	}


	void Chip::on_drag_end(const Glib::RefPtr<Gdk::DragContext>& context)
	{
#ifdef DEBUG_DND_LOG
		cout << endl;
		cout << "Chip::on_drag_end()" << endl;
#endif // DEBUG_DND_LOG

		// TODO: implement on_drag_end functionality
		//return Gtk::Widget::on_drag_end(context);
	}


#ifdef _MSC_VER
	// #pragma warning (default: 4100) // unreferenced formal parameter

#pragma endregion

#pragma region drawing
#endif // _MSC_VER

// Draw on the supplied Cairo::Context.
	bool Chip::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
	{
		Gtk::Allocation allocation = get_allocation();

		// paint the background
		Gdk::Cairo::set_source_rgba(cr, mBackground);
		cr->paint();

		// draw chip in the middle
		Gdk::Cairo::set_source_pixbuf(cr, refIcon,
			allocation.get_width() * 0.5 - (refIcon->get_width() / 2),
			allocation.get_height() * 0.5 - (refIcon->get_height() / 2));

		cr->paint();

		return true;
	}

	void Chip::set_background_color(const Gdk::RGBA & color)
	{
		mBackground = color;
	}

#ifdef _MSC_VER
#pragma endregion

#pragma region widget
#endif // _MSC_VER

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
}

#ifdef _MSC_VER
#pragma endregion
#endif // _MSC_VER
