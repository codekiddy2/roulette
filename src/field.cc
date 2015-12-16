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
#include "main.hh"

namespace roulette
{
	using std::cerr;
	using std::endl;
	using std::cout;
	using std::string;
	using std::to_string;
	using std::make_shared;
	using std::shared_ptr;
	using std::for_each;

	extern std::vector<Gtk::TargetEntry> dnd_targets;

#ifdef _MSC_VER
#pragma region begin
#endif // _MSC_VER

	Field::Field(EField field_index, Table* parent) :
		Glib::ObjectBase("Field"), // The GType name will be gtkmm__CustomObject_Field
		Gtk::Widget(),
		//mName(to_string(num)), // TODO: used for signal debug
		mBackground("rgb(0, 102, 0)"), // green
		p_parent(parent),
		m_index(field_index)
	{
		set_has_window(true);
		set_events(Gdk::EventMask::ALL_EVENTS_MASK);

		assign_apperance(field_index);
		mFont.set_family("Arial");
		mLayout->set_font_description(mFont);

		parent->signal_clear.connect(sigc::mem_fun(*this, &Field::clear));

		// Make Field a drop target
		drag_dest_set(dnd_targets, Gtk::DestDefaults::DEST_DEFAULT_ALL, Gdk::DragAction::ACTION_COPY);
		signal_button_press_event().connect(sigc::mem_fun(*this, &Field::on_clicked));
	}

	void Field::clear()
	{
		m_bets.clear();
		// TODO: some fields might not have Gdk::Window (dummies on different tables)
		if (refGdkWindow)
		{
			refGdkWindow->invalidate(false);
		}
#ifdef DEBUG_SIGNALS
		cout << "clear: " << mName << endl;
#endif // DEBUG_SIGNALS
	}

	EBet Field::calculate_points(Gdk::Point& point)
	{
		Gtk::Allocation alloc = get_allocation();

		int x = point.get_x();
		int y = point.get_y();

		const int width = alloc.get_width(); // right
		const int height = alloc.get_height(); // down

		const double cx = width * .5;
		const double cy = height * .5;

		const double left = width * .333;
		const double top = height * .333;
		const double right = left * 2;
		const double down = top * 2;

		static const int format = 8;

		EBet bet = EBet::Corner;
		if ((x < left || x > right) && (y < top || y > down))
			bet = EBet::Split;
		else if ((cx == point.get_x()) && (cy == point.get_y()))
			bet = EBet::StraightUp;

		switch (m_index)
		{
		case roulette::EField::Number0:
		{
			const double split1 = height	* .166;
			const double street1 = height * .33;
			const double split2 = height	* .5;
			const double street2 = height * .66;
			const double split3 = height	* .833;
			const double basket = height * 1;

			const double check = width	* .125;

			const double check_split1 = split1 - check;
			const double check_street1 = street1 - check;
			const double check_split2 = split2 - check;
			const double check_street2 = street2 - check;
			const double check_split3 = split3 - check;
			const double check_basket = basket - check;

			x > right ? point.set_x(width) : point.set_x(cx);

			if (x < right)
				point.set_y(cy);
			else
			{
				y < check_split1 ? point.set_y(split1) :
					y < check_street1 ? point.set_y(split1) :
					y < check_split2 ? point.set_y(street1) :
					y < check_street2 ? point.set_y(split2) :
					y < check_split3 ? point.set_y(street2) :
					y < check_basket ? point.set_y(split3) :
					point.set_y(basket);
			}
		}
		break;
		case roulette::EField::Number1:
		case roulette::EField::Number2:
			goto set_default;
		case roulette::EField::Number3:
			x < left ? point.set_x(0) : x > right ? point.set_x(width) : point.set_x(cx);
			y > down ? point.set_y(height) : point.set_y(cy);
			break;
		case roulette::EField::Number4:
		case roulette::EField::Number5:
			goto set_default;
		case roulette::EField::Number6:
			goto set_column3;
		case roulette::EField::Number7:
		case roulette::EField::Number8:
			goto set_default;
		case roulette::EField::Number9:
			goto set_column3;
		case roulette::EField::Number10:
		case roulette::EField::Number11:
			goto set_default;
		case roulette::EField::Number12:
			goto set_column3;
		case roulette::EField::Number13:
		case roulette::EField::Number14:
			goto set_default;
		case roulette::EField::Number15:
			goto set_column3;
		case roulette::EField::Number16:
		case roulette::EField::Number17:
			goto set_default;
		case roulette::EField::Number18:
			goto set_column3;
		case roulette::EField::Number19:
		case roulette::EField::Number20:
			goto set_default;
		case roulette::EField::Number21:
			goto set_column3;
		case roulette::EField::Number22:
		case roulette::EField::Number23:
			goto set_default;
		case roulette::EField::Number24:
			goto set_column3;
		case roulette::EField::Number25:
		case roulette::EField::Number26:
			goto set_default;
		case roulette::EField::Number27:
			goto set_column3;
		case roulette::EField::Number28:
		case roulette::EField::Number29:
			goto set_default;
		case roulette::EField::Number30:
			goto set_column3;
		case roulette::EField::Number31:
		case roulette::EField::Number32:
			goto set_default;
		case roulette::EField::Number33:
			goto set_column3;
		case roulette::EField::Number34:
		case roulette::EField::Number35:
			x < left ? point.set_x(0) : point.set_x(cx);
			y < top ? point.set_y(0) : y > down ? point.set_y(height) : point.set_y(cy);
			break;
		case roulette::EField::Number36:
			x < left ? point.set_x(0) : point.set_x(cx);
			y > down ? point.set_y(height) : point.set_y(cy);
			break;
		case roulette::EField::Number00:
			break;
		case roulette::EField::Column1:
		case roulette::EField::Column2:
		case roulette::EField::Column3:
			point.set_x(cx);
			point.set_y(cy);
			break;
		case roulette::EField::Dozen1:
		case roulette::EField::Dozen2:
		case roulette::EField::Dozen3:
			if (y < top)
			{
				const double basket = width * 0;
				const double street1 = width	* .125;
				const double line1 = width		* .25;
				const double street2 = width	* .375;
				const double line2 = width		* .5;
				const double street3 = width	* .625;
				const double line3 = width		* .75;
				const double street4 = width	* .875;
				const double line4 = width * 1;

				const double check = width	* .0625;

				const double check_street1 = street1 - check;
				const double check_line1 = line1 - check;
				const double check_street2 = street2 - check;
				const double check_line2 = line2 - check;
				const double check_street3 = street3 - check;
				const double check_line3 = line3 - check;
				const double check_street4 = street4 - check;
				const double check_line4 = line4 - check;

				x < basket ? point.set_x(basket) : // basket
					x < check_street1 ? point.set_x(basket) : // street
					x < check_line1 ? point.set_x(street1) : // line
					x < check_street2 ? point.set_x(line1) : // street
					x < check_line2 ? point.set_x(street2) : // line
					x < check_street3 ? point.set_x(line2) : // street
					x < check_line3 ? point.set_x(street3) : // line
					x < check_street4 ? point.set_x(line3) : // street
					x < check_line4 ? point.set_x(street4) : // line
					point.set_x(line4); // line
				point.set_y(0);
			}
			else
			{
				point.set_x(cx);
				point.set_y(cy);
			}
			break;
		case roulette::EField::Red:
		case roulette::EField::Black:
		case roulette::EField::Even:
		case roulette::EField::Odd:
		case roulette::EField::High:
		case roulette::EField::Low:
			point.set_x(cx);
			point.set_y(cy);
			break;
		case roulette::EField::Dummy1:
		case roulette::EField::Dummy2:
		case roulette::EField::Dummy3:
			break;
		default:
			set_column3:
				x < left ? point.set_x(0) : x > right ? point.set_x(width) : point.set_x(cx);
				y > down ? point.set_y(height) : point.set_y(cy);
				break;
			set_default:
				x < left ? point.set_x(0) : x > right ? point.set_x(width) : point.set_x(cx);
				y < top ? point.set_y(0) : y > down ? point.set_y(height) : point.set_y(cy);
				break;
		} // switch
		return bet;
	}

	bool Field::on_clicked(GdkEventButton* button_event)
	{
		if (button_event->type == GdkEventType::GDK_2BUTTON_PRESS)
		{
			clear();
			refGdkWindow->invalidate(false);
			return true;
		}
		else return false;
	}

	void Field::assign_apperance(EField index)
	{
		switch (index)
		{
		case roulette::EField::Number0:
		case roulette::EField::Number1:
		case roulette::EField::Number2:
		case roulette::EField::Number3:
		case roulette::EField::Number4:
		case roulette::EField::Number5:
		case roulette::EField::Number6:
		case roulette::EField::Number7:
		case roulette::EField::Number8:
		case roulette::EField::Number9:
		case roulette::EField::Number10:
		case roulette::EField::Number11:
		case roulette::EField::Number12:
		case roulette::EField::Number13:
		case roulette::EField::Number14:
		case roulette::EField::Number15:
		case roulette::EField::Number16:
		case roulette::EField::Number17:
		case roulette::EField::Number18:
		case roulette::EField::Number19:
		case roulette::EField::Number20:
		case roulette::EField::Number21:
		case roulette::EField::Number22:
		case roulette::EField::Number23:
		case roulette::EField::Number24:
		case roulette::EField::Number25:
		case roulette::EField::Number26:
		case roulette::EField::Number27:
		case roulette::EField::Number28:
		case roulette::EField::Number29:
		case roulette::EField::Number30:
		case roulette::EField::Number31:
		case roulette::EField::Number32:
		case roulette::EField::Number33:
		case roulette::EField::Number34:
		case roulette::EField::Number35:
		case roulette::EField::Number36:
			mLayout = create_pango_layout(to_string(static_cast<int>(index)));
			break;
		case roulette::EField::Number00:
			mLayout = create_pango_layout("00");
			break;
		case roulette::EField::Column1:
			mLayout = create_pango_layout("2 to 1");
			break;
		case roulette::EField::Column2:
			mLayout = create_pango_layout("2 to 1");
			break;
		case roulette::EField::Column3:
			mLayout = create_pango_layout("2 to 1");
			break;
		case roulette::EField::Dozen1:
			mLayout = create_pango_layout("1st 12");
			break;
		case roulette::EField::Dozen2:
			mLayout = create_pango_layout("2nd 12");
			break;
		case roulette::EField::Dozen3:
			mLayout = create_pango_layout("3rd 12");
			break;
		case roulette::EField::Red:
			mBackground.set("Red");
			mLayout = create_pango_layout("RED");
			break;
		case roulette::EField::Black:
			mBackground.set("Black");
			mLayout = create_pango_layout("BLACK");
			break;
		case roulette::EField::Even:
			mLayout = create_pango_layout("EVEN");
			break;
		case roulette::EField::Odd:
			mLayout = create_pango_layout("ODD");
			break;
		case roulette::EField::High:
			mLayout = create_pango_layout("HIGH");
			break;
		case roulette::EField::Low:
			mLayout = create_pango_layout("LOW");
			break;
		case roulette::EField::Dummy1:
		case roulette::EField::Dummy2:
		case roulette::EField::Dummy3:
		default:
			mLayout = create_pango_layout("");
			break;
		}

		if (is_red(static_cast<int>(index)))
		{
			mBackground.set("Red");
		}
		else if (is_black(static_cast<int>(index)))
		{
			mBackground.set("Black");
		}
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


		if (m_index == EField::Dummy1 || m_index == EField::Dummy2 || m_index == EField::Dummy3)
		{
			// not drawing on dummies
			context->drag_finish(true, false, time);
		}
		else
		{
			Gdk::Point point(x, y);
			EBet bet = calculate_points(point);
			m_bets.push_back(make_shared<Bet>(p_parent->get_table_type(), bet, info, point));

			context->drag_finish(false, false, time);
		}
		

#if 0
		// TODO: this is redundant, make use of selection data
		static const int format = 8;
		if ((selection_data.get_length() == 0) && (selection_data.get_format() == format))
		{
			context->drag_finish(true, false, time); // drop finished, data no longer required
		}
#endif
	}


	void Field::on_drag_leave(const Glib::RefPtr<Gdk::DragContext>& /*context*/, guint time)
	{
#ifdef DEBUG_DND_LOG
		cout << endl;
		cout << "Field::on_drag_leave()" << endl;
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
		Gtk::Allocation allocation = get_allocation();

		const int field_width = allocation.get_width();
		const int field_height = allocation.get_height();

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
		for_each(m_bets.begin(), m_bets.end(), [&](shared_ptr<Bet>& bet) {

			Glib::RefPtr<Gdk::Pixbuf> pixbuf = get_pixbuf(bet->get_chips());
			Gdk::Point point = bet->get_points();

			const int x = point.get_x();
			const int y = point.get_y();

			const int pixbuf_x = pixbuf->get_width() / 2;
			const int pixbuf_y = pixbuf->get_height() / 2;

			Gdk::Cairo::set_source_pixbuf(cr, pixbuf, x - pixbuf_x, y - pixbuf_y);
			cr->paint();
		});

		return true;

//#ifdef DEBUG_DND_LOG
//		cout << endl;
//		cout << "Field::on_draw()" << endl;
//#endif // DEBUG_DND_LOG
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
			const int width = allocation.get_width();
			const int height = allocation.get_height();

			refGdkWindow->move_resize(allocation.get_x(), allocation.get_y(),
				allocation.get_width(), allocation.get_height());

			// recalculate chip points
			// TODO: going to full screen or resizing a window fast will not update points properly
			for_each(m_bets.begin(), m_bets.end(), [this](shared_ptr<Bet>& bet) {
				Gdk::Point point = bet->get_points();
				calculate_points(point);
				bet->set_points(point);
			});

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
