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
//	field.cc
//
//	Definition of Field class
//
//	TODO: add description
//
///</summary>

#include "pch.hh"
#include "field.hh"
#include "sets.hh"
#include "chipset.hh"
#include "table.hh"

namespace roulette
{
	using std::cerr;
	using std::endl;
	using std::cout;
	using std::string;

	extern std::vector<Gtk::TargetEntry> dnd_targets;

#ifdef _MSC_VER
#pragma region begin
#endif // _MSC_VER

	Field::Field(const int num, Table* parent) :
		Glib::ObjectBase("Field"), // The GType name will be gtkmm__CustomObject_Field
		Gtk::Widget(),
		mName(std::to_string(num)),
		mBackground("rgb(0, 102, 0)"), // green
		mLayout(create_pango_layout(mName.c_str()))
	{
		set_has_window(true);
		set_events(Gdk::EventMask::ALL_EVENTS_MASK);

		mFont.set_family("Arial");
		mLayout->set_font_description(mFont);

		if (is_red(num))
		{
			mBackground.set("Red");
		}
		else if (num != 0)
		{
			mBackground.set("Black");
		}

		parent->signal_clear.connect(sigc::mem_fun(*this, &Field::clear));

		// Make Field a drop target
		drag_dest_set(dnd_targets, Gtk::DestDefaults::DEST_DEFAULT_ALL, Gdk::DragAction::ACTION_COPY);
	}


	Field::Field(const string text, Table* parent) :
		Glib::ObjectBase("Field"), // The GType name will be gtkmm__CustomObject_Field
		Gtk::Widget(),
		mName(text),
		mBackground("rgb(0, 102, 0)"), // green
		mLayout(create_pango_layout(text))
	{
		set_has_window(true);
		set_events(Gdk::EventMask::ALL_EVENTS_MASK);

		mFont.set_family("Arial");
		mLayout->set_font_description(mFont);

		if (text == "RED")
		{
			mBackground.set("Red");
		}
		else if (text == "BLACK")
		{
			mBackground.set("Black");
		}

		parent->signal_clear.connect(sigc::mem_fun(*this, &Field::clear));

		// Make Field a drop target
		drag_dest_set(dnd_targets, Gtk::DestDefaults::DEST_DEFAULT_ALL, Gdk::DragAction::ACTION_COPY);
	}


	void Field::clear()
	{
		mChips.clear();
		refGdkWindow->invalidate(false);

#ifdef DEBUG_SIGNALS
		cout << "clear: " << mName << endl;
#endif // DEBUG_SIGNALS
	}

#ifdef _MSC_VER
#pragma endregion

#pragma region dnd
#endif //_MSC_VER
	/*
	The destination widget will emit these signals, in this order:

	drag_motion:
	Provides DragContext and coordinates.
	You can call the drag_status() method of the DragContext to indicate which action will be accepted.

	drag_drop:
	Provides DragContext and coordinates.
	You can call drag_get_data(), which triggers the drag_data_get signal in the source widget,
	and then the drag_data_received signal in the destination widget.

	drag_data_received:
	Provides info about the dragged data format,
	and a Gtk::SelectionData structure which contains the dropped data.
	You should call the drag_finish() method of the DragContext to indicate whether the operation was successful.

	drag_leave:
	*/



#ifdef _MSC_VER
	// #pragma warning (disable: 4100) // TODO: unreferenced formal parameter
#endif // _MSC_VER

	bool Field::on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint time)
	{
#ifdef DEBUG_DND_LOG
		if (motion_count < 3)
		{
			++motion_count;
			cout << endl;
			cout << "Field::on_drag_motion()" << endl;
			cout << "-> INFO: name = " << mName << endl;
			cout << "-> INFO: x = " << x << endl;
			cout << "-> INFO: y = " << y << endl;
			cout << "-> INFO: time = " << time << endl;
		}
#endif // DEBUG_DND_VERBOSE

		// TODO: implement drag motion functionality
		context->drag_status(Gdk::DragAction::ACTION_COPY, time);

		return true; // Return whether the cursor position is in a drop zone.
	}


	bool Field::on_drag_drop(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint time)
	{
#ifdef DEBUG_DND_LOG
		cout << endl;
		cout << "Field::on_drag_drop()" << endl;
		cout << "-> INFO: x = " << x << endl;
		cout << "-> INFO: y = " << y << endl;
		cout << "-> INFO: time = " << time << endl;
#endif // DEBUG_DND_LOG

		context->drop_reply(true, time); // accept the drop
		context->drop_finish(true, time); // end drag operation

		return true; // Return whether the cursor position is in a drop zone.
	}


	void Field::on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
		int x, int y, const Gtk::SelectionData& selection_data, guint info, guint time)
	{
#ifdef DEBUG_DND_LOG
		cout << endl;
		cout << "Field::on_drag_data_received()" << endl;
		cout << "-> INFO: target = " << selection_data.get_target() << endl;
		cout << "-> INFO: pointer: " << selection_data.get_data() << endl;
		cout << "-> INFO: length = " << selection_data.get_length() << endl;
		cout << "-> INFO: format = " << selection_data.get_format() << endl;
		cout << "-> INFO: info = " << info << endl;
		cout << "-> INFO: time = " << time << endl;
		cout << "-> INFO: x = " << x << endl;
		cout << "-> INFO: y = " << y << endl;
#endif // DEBUG_DND_LOG

#ifdef DEBUG_DND_VERBOSE

		Glib::RefPtr<const Gdk::Pixbuf> temp = selection_data.get_pixbuf();

		if (temp)
		{
			cout << "-> INFO: pixbuf size = " << temp->get_byte_length() << endl;
		}
		else
		{
			cerr << "-> WARNING: get_pixbuf() did not return a pixbuf" << endl;
			cout << "-> INFO: if targets include image = " << selection_data.targets_include_image(false) << endl;
		}

#endif // DEBUG_DND_LOG

		static const int format = 8;

		if ((selection_data.get_length() == 0) && (selection_data.get_format() == format))
		{
			mChips.push_back(info);
		}

		context->drag_finish(true, false, time); // drop finished, data no longer required
	}


	void Field::on_drag_leave(const Glib::RefPtr<Gdk::DragContext>& context, guint time)
	{
#ifdef DEBUG_DND_LOG
		cout << endl;
		cout << "Field::on_drag_leave()" << endl;
		cout << "-> INFO: name = " << mName << endl;
		cout << "-> INFO: time = " << time << endl;
#endif // DEBUG_DND_LOG

		// TODO: implement on_drag_leave functionality
		// return Gtk::Widget::on_drag_leave(context, time);
	}


#ifdef _MSC_VER
	// #pragma warning (default: 4100) // unreferenced formal parameter

#pragma endregion

#pragma region drawing
#endif // _MSC_VER

// Draw on the supplied Cairo::Context.
	bool Field::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
	{
		// TODO: load pixbufs and share memory with Chip objects. 
		typedef Glib::RefPtr<Gdk::Pixbuf> type_chip_icon;
		const int chip_size = Chipset::get_chipsize();

		// TODO: check file existence
		static type_chip_icon icon1 = Gdk::Pixbuf::create_from_file("Chip1.ico", chip_size, chip_size);
		static type_chip_icon icon5 = Gdk::Pixbuf::create_from_file("Chip5.ico", chip_size, chip_size);
		static type_chip_icon icon25 = Gdk::Pixbuf::create_from_file("Chip25.ico", chip_size, chip_size);
		static type_chip_icon icon50 = Gdk::Pixbuf::create_from_file("Chip50.ico", chip_size, chip_size);
		static type_chip_icon icon100 = Gdk::Pixbuf::create_from_file("Chip100.ico", chip_size, chip_size);

		Gtk::Allocation allocation = get_allocation();

		const int field_width = allocation.get_width();
		const int field_height = allocation.get_height();
		const int icon_cx = icon1->get_width() / 2;
		const int icon_cy = icon1->get_height() / 2;

		const double cx = field_width * 0.5;
		const double cy = field_height * 0.5;

		// paint the background
		Gdk::Cairo::set_source_rgba(cr, mBackground);
		cr->paint();

		// stroke lines around filed
		cr->set_source_rgb(1.0, 1.0, 1.0); // white lines
		cr->set_line_width(1.0);
		cr->rectangle(0.0, 0.0, field_width, field_height);
		cr->stroke();

		// show text
		draw_text(cr, field_width, field_height);

		// draw chips
		std::for_each(mChips.begin(), mChips.end(), [&](unsigned& value) {
			switch (value)
			{
			case 1:
				Gdk::Cairo::set_source_pixbuf(cr, icon1, cx - icon_cx, cy - icon_cy);
				break;
			case 5:
				Gdk::Cairo::set_source_pixbuf(cr, icon5, cx - icon_cx, cy - icon_cy);
				break;
			case 25:
				Gdk::Cairo::set_source_pixbuf(cr, icon25, cx - icon_cx, cy - icon_cy);
				break;
			case 50:
				Gdk::Cairo::set_source_pixbuf(cr, icon50, cx - icon_cx, cy - icon_cy);
				break;
			case 100:
				Gdk::Cairo::set_source_pixbuf(cr, icon100, cx - icon_cx, cy - icon_cy);
				break;
			}
			cr->paint();
		});
#ifdef DEBUG_DND_LOG
		cout << endl;
		cout << "Field::on_draw()" << endl;
#endif // DEBUG_DND_LOG

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
#ifdef _MSC_VER
#pragma endregion

#pragma region widget
#endif // _MSC_VER

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

#ifdef _MSC_VER
#pragma endregion
#endif // _MSC_VER

} // namespace roulette
