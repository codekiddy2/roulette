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

#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER

	using std::cerr;
	using std::endl;
	using std::cout;
	using std::string;
	using std::to_string;
	using std::make_shared;
	using std::shared_ptr;
	using std::for_each;
	using std::make_pair;
	using std::pair;

	extern std::vector<Gtk::TargetEntry> dnd_targets;
	
	Field::Field(EField field_index, Table* parent) :
		Glib::ObjectBase("Field"), // The GType name will be gtkmm__CustomObject_Field
		Gtk::Widget(),
		mBackground("rgb(0, 102, 0)"), // green
		p_parent(parent),
		m_index(field_index)
	{
		set_has_window(true);
		set_events(Gdk::EventMask::ALL_EVENTS_MASK);

		assign_apperance(field_index);
		mFont.set_family("Arial");
		mLayout->set_font_description(mFont);

		parent->signal_clear.connect(sigc::mem_fun(*this, &Field::clear_all));

		// Make Field a drop target
		drag_dest_set(dnd_targets, Gtk::DestDefaults::DEST_DEFAULT_ALL, Gdk::DragAction::ACTION_COPY);
		signal_button_press_event().connect(sigc::mem_fun(*this, &Field::on_clicked));
	}

#ifdef _MSC_VER
#pragma endregion begin

#pragma region
#endif // _MSC_VER

	// calculate where to place a drawn chip or portion of a chip
	// and then emit signal to neighboring fields so that they do the same
	// neighborng fields will calculate x y in signal handlers instead.
	// last parameter is used to avoid re-emiting signals on window resize.
	void Field::calculate_points(type_chip chip, bool emit /*= true*/)
	{
		Gtk::Allocation alloc = get_allocation();
		Gdk::Point& point = chip->second;
		
		const int x = point.get_x();
		const int y = point.get_y();

		const int width = alloc.get_width(); // right
		const int height = alloc.get_height(); // down

		const int cx	= static_cast<int>(width	* .5);
		const int cy	= static_cast<int>(height	* .5);
		const int left = static_cast<int>(width	* .333);
		const int top	= static_cast<int>(height	* .333);
		const int right= static_cast<int>(width	* .666); // was left *2;
		const int down	= static_cast<int>(height	* .666); // was top * 2;

		switch (m_index)
		{
		case roulette::EField::Number0:
		{
			// TODO: move to global scope, used in signal handlers too (check ??)
			const int split1	= static_cast<int>(height * .167); // rounded up
			const int street1 = static_cast<int>(height * .334); // rounded up
			const int split2	= static_cast<int>(height * .5);
			const int street2 = static_cast<int>(height * .667); // rounded up
			const int split3	= static_cast<int>(height * .834); // rounded up
			const int basket	= height;

			const int check = width / 5; // was	*.125 not rounded up

			const int check_street1 = street1 - check;
			const int check_split2 = split2 - check;
			const int check_street2 = street2 - check;
			const int check_split3 = split3 - check;
			const int check_basket = basket - check;

			point.set_x(cx);
			if (x < right)
			{
				point.set_y(cy);
				// no signal
			}
			else // x > right
			{
				point.set_x(width);
				if (y < check_street1)
				{
					point.set_y(split1);
					emit ? signal_bet_split1.emit(m_index, chip) : 0;
					break;
				}
				else if (y < check_split2)
				{
					point.set_y(street1);
					emit ? signal_bet_street1.emit(m_index, chip) : 0;
				}
				else if (y < check_street2)
				{
					point.set_y(split2);
					emit ? signal_bet_split2.emit(m_index, chip) : 0;
				}
				else if (y < check_split3)
				{
					point.set_y(street2);
					emit ? signal_bet_street2.emit(m_index, chip) : 0;
				}
				else if (y < check_basket)
				{
					point.set_y(split3);
					emit ? signal_bet_split3.emit(m_index, chip) : 0;
				}
				else
				{
					point.set_y(basket);
					emit ? signal_bet_basket.emit(m_index, chip) : 0;
				}
			}
		}
		break;
		case roulette::EField::Number1:
		case roulette::EField::Number2:
			goto set_default;
		case roulette::EField::Number3:
			if (x < left)
			{
				point.set_x(0);
				if (y > down)
				{
					point.set_y(height);
					emit ? signal_bet_bottom_left.emit(m_index, chip) : 0;
				}
				else
				{
					point.set_y(cy);
					emit ? signal_bet_left.emit(m_index, chip) : 0;
				}
			}
			else if (x > right)
			{
				point.set_x(width);
				if (y > down)
				{
					point.set_y(height);
					emit ? signal_bet_bottom_right.emit(m_index, chip) : 0;
				}
				else
				{
					point.set_y(cy);
					emit ? signal_bet_right.emit(m_index, chip) : 0;
				}
			}
			else // x == cx
			{
				point.set_x(cx);
				if (y > down)
				{
					point.set_y(height);
					emit ? signal_bet_bottom.emit(m_index, chip) : 0;
				}
				else // y == cy
				{
					point.set_y(cy);
					// cx, cy -> no signal
				}
			}
			break;
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
			goto set_default;
		case roulette::EField::Number34:
		case roulette::EField::Number35:
			if (x < left)
			{
				point.set_x(0);
				if (y < top)
				{
					point.set_y(0);
					emit ? signal_bet_top_left.emit(m_index, chip) : 0;
				}
				else if (y > down)
				{
					point.set_y(height);
					emit ? signal_bet_bottom_left.emit(m_index, chip) : 0;
				}
				else
				{
					point.set_y(cy);
					emit ? signal_bet_left.emit(m_index, chip) : 0;
				}
			}
			else // x == cx
			{
				point.set_x(cx);
				if (y < top)
				{
					point.set_y(0);
					emit ? signal_bet_top.emit(m_index, chip) : 0;
				}
				else if (y > down)
				{
					point.set_y(height);
					emit ? signal_bet_bottom.emit(m_index, chip) : 0;
				}
				else // y == cy
				{
					point.set_y(cy);
					// cx, cy -> no signal
				}
			}
			break;
		case roulette::EField::Number36:
			if (x < left)
			{
				point.set_x(0);
				if (y > down)
				{
					point.set_y(height);
					emit ? signal_bet_bottom_left.emit(m_index, chip) : 0;
				}
				else
				{
					point.set_y(cy);
					emit ? signal_bet_left.emit(m_index, chip) : 0;
				}
			}
			else // x == cx
			{
				point.set_x(cx);
				if (y > down)
				{
					point.set_y(height);
					emit ? signal_bet_bottom.emit(m_index, chip) : 0;
				}
				else // y == cy
				{
					point.set_y(cy);
					// cx, cy -> no signal
				}
			}
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
		{
			const int line1	= 0;
			const int street1 = static_cast<int>(width * .126); // rounded up
			const int line2	= static_cast<int>(width * .25);
			const int street2	= static_cast<int>(width * .376); // rounded up
			const int line3	= static_cast<int>(width * .5);
			const int street3 = static_cast<int>(width * .626); // rounded up
			const int line4	= static_cast<int>(width * .75);
			const int street4 = static_cast<int>(width * .876); // rounded up
			const int line5	= width;

			const int check = static_cast<int>(width	* .0625);

			const int check_street1 = street1 - check;
			const int check_line2	= line2 - check;
			const int check_street2 = street2 - check;
			const int check_line3	= line3 - check;
			const int check_street3 = street3 - check;
			const int check_line4	= line4 - check;
			const int check_street4 = street4 - check;
			const int check_line5	= line5 - check;

			if (y < top)
			{
				point.set_y(0);
				if (x < check_street1)
				{
					point.set_x(line1);
					emit ? signal_bet_line1.emit(m_index, chip) : 0;
				}
				else if (x < check_line2)
				{
					point.set_x(street1);
					emit ? signal_bet_street1.emit(m_index, chip) : 0;
				}
				else if (x < check_street2)
				{
					point.set_x(line2);
					emit ? signal_bet_line2.emit(m_index, chip) : 0;
				}
				else if (x < check_line3)
				{
					point.set_x(street2);
					emit ? signal_bet_street2.emit(m_index, chip) : 0;
				}
				else if (x < check_street3)
				{
					point.set_x(line3);
					emit ? signal_bet_line3.emit(m_index, chip) : 0;
				}
				else if (x < check_line4)
				{
					point.set_x(street3);
					emit ? signal_bet_street3.emit(m_index, chip) : 0;
				}
				else if (x < check_street4)
				{
					point.set_x(line4);
					emit ? signal_bet_line4.emit(m_index, chip) : 0;
				}
				else if (x < check_line5 || m_index == EField::Dozen3)  // skip line5 for dozen3
				{
					point.set_x(street4);
					emit ? signal_bet_street4.emit(m_index, chip) : 0;
				}
				else // x > check_line5
				{
					point.set_x(line5);
					emit ? signal_bet_line5.emit(m_index, chip) : 0;
				}
			}
			else // y > top
			{
				point.set_x(cx);
				point.set_y(cy);
			} // if
		} // case
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
			if (x > right && y < top / 2)
			{
				point.set_x(width);
				point.set_y(0);
				emit ? signal_bet_basket.emit(m_index, chip) : 0;
				break;
			}
			point.set_x(0); // this value indicates a drop will not be accepted
			break;
		case roulette::EField::Dummy2:
		case roulette::EField::Dummy3:
			break;
		default: set_default:
			if (x < left)
			{
				point.set_x(0);
				if (y < top)
				{
					point.set_y(0);
					emit ? signal_bet_top_left.emit(m_index, chip) : 0;
				}
				else if (y > down)
				{
					point.set_y(height);
					emit ? signal_bet_bottom_left.emit(m_index, chip) : 0;
				}
				else
				{
					point.set_y(cy);
					emit ? signal_bet_left.emit(m_index, chip) : 0;
				}
			}
			else if (x > right)
			{
				point.set_x(width);
				if (y < top)
				{
					point.set_y(0);
					emit ? signal_bet_top_right.emit(m_index, chip) : 0;
				}
				else if (y > down)
				{
					point.set_y(height);
					emit ? signal_bet_bottom_right.emit(m_index, chip) : 0;
				}
				else
				{
					point.set_y(cy);
					emit ? signal_bet_right.emit(m_index, chip) : 0;
				}
			}
			else // x == cx
			{
				point.set_x(cx);
				if (y < top)
				{
					point.set_y(0);
					emit ? signal_bet_top.emit(m_index, chip) : 0;
				}
				else if (y > down)
				{
					point.set_y(height);
					emit ? signal_bet_bottom.emit(m_index, chip) : 0;
				}
				else // y == cy
				{
					point.set_y(cy);
					// cx, cy -> no signal
				}
			}
			break;
		} // switch
	} // calculate_points

	bool Field::on_clicked(GdkEventButton* button_event)
	{
		if (button_event->type == GdkEventType::GDK_DOUBLE_BUTTON_PRESS)
		{
			type_chip_pair chip_pair = make_pair(EChip::Eraser, Gdk::Point(0, 0));
			type_chip chip = make_shared<type_chip_pair>(chip_pair);

			signal_bet_bottom.emit(m_index, chip);
			signal_bet_top.emit(m_index, chip);
			signal_bet_left.emit(m_index, chip);
			signal_bet_right.emit(m_index, chip);
			signal_bet_bottom_left.emit(m_index, chip);
			signal_bet_bottom_right.emit(m_index, chip);
			signal_bet_top_left.emit(m_index, chip);
			signal_bet_top_right.emit(m_index, chip);

			clear_all();
			refGdkWindow->invalidate(false);
			return true;
		}
		else return false;
	}

	void Field::assign_apperance(EField index)
	{
		switch (index)
		{
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
			mLayout = create_pango_layout("");
			break;
		default:
			mLayout = create_pango_layout(to_string(static_cast<int>(index)));
			if (is_red(static_cast<int>(index)))
			{
				mBackground.set("Red");
			}
			else if (is_black(static_cast<int>(index)))
			{
				mBackground.set("Black");
			}
		}
	}

	void Field::clear_all()
	{
		// TODO: some fields might not have Gdk::Window (dummies on different tables)
		if (refGdkWindow)
		{
			m_chips.clear();
			refGdkWindow->invalidate(false);
		}
	}

	void Field::clear(Gdk::Point& chip_point)
	{
		for (auto iter = m_chips.begin(); iter != m_chips.end(); iter++)
		{
			if (iter->get()->second.equal(chip_point))
			{
				m_chips.erase(iter);
				iter = m_chips.begin();
				if (iter == m_chips.end()) break;
			}
		}
		return refGdkWindow->invalidate(false);
	}

#ifdef _MSC_VER
#pragma endregion methods

#pragma region
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

	bool Field::on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int /*x*/, int /*y*/, guint time)
	{
		// TODO: implement drag motion functionality
		context->drag_status(Gdk::DragAction::ACTION_COPY, time);

		return true; // Return whether the cursor position is in a drop zone.
	}

	bool Field::on_drag_drop(const Glib::RefPtr<Gdk::DragContext>& context, int /*x*/, int /*y*/, guint time)
	{
		if (m_index == EField::Dummy2 || m_index == EField::Dummy3)
		{
			// not drawing on these dummies
			context->drop_reply(false, time);
			return false;
		}
		else
		{
			context->drop_finish(true, time); // end drag operation
			return true; // Return whether the cursor position is in a drop zone.
		}
	}
	
	void Field::on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
		int x, int y, const Gtk::SelectionData& /*selection_data*/, guint info, guint time)
	{
		// TODO: make use of selection data
		type_chip_pair chip_pair = make_pair(static_cast<EChip>(info), Gdk::Point(x, y));
		type_chip chip = make_shared<type_chip_pair>(chip_pair);
		calculate_points(chip); // chip will now be modified and emited

		if (info == static_cast<unsigned>(EChip::Eraser))
		{
			clear(chip->second);
			context->drag_finish(false, false, time);
			return refGdkWindow->invalidate(false);
		}

		if (m_index == EField::Dummy1 && !chip->second.get_x())
		{
			// if dummy's x is zero then dropped chips won't be drawn on it.
			return context->drag_finish(true, false, time);
		}

		m_chips.push_back(chip);
		return context->drag_finish(false, false, time);
	}

	void Field::on_drag_leave(const Glib::RefPtr<Gdk::DragContext>& context, guint time)
	{
		// TODO: implement on_drag_leave functionality
		return Gtk::Widget::on_drag_leave(context, time);
	}

#ifdef _MSC_VER
#pragma endregion drag and drop

#pragma region
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

		// draw neighboring chips
		for (size_t i = 0; i < m_chips.size(); i++)
		{
			Glib::RefPtr<Gdk::Pixbuf> pixbuf = get_pixbuf(m_chips.at(i)->first);
			Gdk::Point point = m_chips.at(i)->second;

			const int x = point.get_x();
			const int y = point.get_y();

			const int pixbuf_x = pixbuf->get_width() / 2;
			const int pixbuf_y = pixbuf->get_height() / 2;

			Gdk::Cairo::set_source_pixbuf(cr, pixbuf, x - pixbuf_x, y - pixbuf_y);
			cr->paint();
		}
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
#pragma endregion drawing

#pragma region
#endif // _MSC_VER

	// TODO: check why need to check for gdkwindow, why throws
	void Field::on_signal_bet_bottom(const EField& /*sender*/, type_chip chip)
	{
		Gdk::Point point = chip->second;
		Gtk::Allocation alloc = get_allocation();
		point.set_x(static_cast<int>(alloc.get_width() * .5));
		point.set_y(alloc.get_height());

		if (chip->first == EChip::Eraser)
		{
			clear(point);
			return;
		}

		type_chip_pair chip_pair = make_pair(chip->first, point);
		type_chip chip_copy = make_shared<type_chip_pair>(chip_pair);
		m_chips.push_back(chip_copy);

		if(refGdkWindow)
			refGdkWindow->invalidate(false);
	}

	void Field::on_signal_bet_top(const EField& sender, type_chip chip)
	{
		Gdk::Point point = chip->second;
		Gtk::Allocation alloc = get_allocation();
		const int width = alloc.get_width();
		point.set_x(static_cast<int>(width * .5));
		point.set_y(0);

		const int line1 = 0;
		const int street1 = static_cast<int>(width * .126); // rounded up
		const int line2	= static_cast<int>(width * .25);
		const int street2 = static_cast<int>(width * .376); // rounded up
		const int line3	= static_cast<int>(width * .5);
		const int street3 = static_cast<int>(width * .626); // rounded up
		const int line4	= static_cast<int>(width * .75);
		const int street4 = static_cast<int>(width * .876); // rounded up
		const int line5	= width;

		if (m_index == EField::Dozen1 || m_index == EField::Dozen2 || m_index == EField::Dozen3)
		{
			switch (sender)
			{
			case EField::Number1:
			case EField::Number13:
			case EField::Number25:
				point.set_x(street1);
				break;
			case EField::Number4:
			case EField::Number16:
			case EField::Number28:
				point.set_x(street2);
				break;
			case EField::Number7:
			case EField::Number19:
			case EField::Number31:
				point.set_x(street3);
				break;
			case EField::Number10:
			case EField::Number22:
			case EField::Number34:
				point.set_x(street4);
			}
		}
		if (chip->first == EChip::Eraser)
		{
			clear(point);
			return;
		}

		type_chip_pair chip_pair = make_pair(chip->first, point);
		type_chip chip_copy = make_shared<type_chip_pair>(chip_pair);
		m_chips.push_back(chip_copy);

		if (refGdkWindow)
			refGdkWindow->invalidate(false);
	}

	void Field::on_signal_bet_left(const EField&, type_chip chip)
	{
		Gdk::Point point = chip->second;
		Gtk::Allocation alloc = get_allocation();
		point.set_x(0);
		point.set_y(static_cast<int>(alloc.get_height() * .5));

		if (chip->first == EChip::Eraser)
		{
			clear(point);
			return;
		}

		type_chip_pair chip_pair = make_pair(chip->first, point);
		type_chip chip_copy = make_shared<type_chip_pair>(chip_pair);
		m_chips.push_back(chip_copy);

		if (refGdkWindow)
			refGdkWindow->invalidate(false);
	}

	void Field::on_signal_bet_right(const EField& sender, type_chip chip)
	{
		Gdk::Point point = chip->second;
		Gtk::Allocation alloc = get_allocation();
		point.set_x(alloc.get_width());
		point.set_y(static_cast<int>(alloc.get_height() * .5));

		if (m_index == EField::Number0)
		{
			switch (sender)
			{
			case EField::Number1:
				point.set_y(static_cast<int>(alloc.get_height() * .834)); // rounded up
				break;
			case EField::Number3:
				point.set_y(static_cast<int>(alloc.get_height() * .167)); // rounded up
			}
		}
		if (chip->first == EChip::Eraser)
		{
			clear(point);
			return;
		}

		type_chip_pair chip_pair = make_pair(chip->first, point);
		type_chip chip_copy = make_shared<type_chip_pair>(chip_pair);
		m_chips.push_back(chip_copy);

		if (refGdkWindow)
			refGdkWindow->invalidate(false);
	}

	void Field::on_signal_bet_top_right(const EField& sender, type_chip chip)
	{
		Gdk::Point point = chip->second;
		Gtk::Allocation alloc = get_allocation();
		const int width = alloc.get_width();
		point.set_x(width);
		point.set_y(0);

		const int line1	= 0;
		const int street1 = static_cast<int>(width * .126); // rounded up
		const int line2	= static_cast<int>(width * .25);
		const int street2 = static_cast<int>(width * .376); // rounded up
		const int line3	= static_cast<int>(width * .5);
		const int street3 = static_cast<int>(width * .626); // rouended up
		const int line4	= static_cast<int>(width * .75);
		const int street4 = static_cast<int>(width * .876); // rounded up
		const int line5	= width;

		if (m_index == EField::Number0)
		{
			switch (sender)
			{
			case EField::Number1:
				point.set_y(static_cast<int>(alloc.get_height() * .667)); // rounded up
				break;
			case EField::Number2:
				point.set_y(static_cast<int>(alloc.get_height() * .334)); // rounded up
			}
		}
		else if (m_index == EField::Dozen1 || m_index == EField::Dozen2 || m_index == EField::Dozen3)
		{
			switch (sender)
			{
			case EField::Number25: // has 2 neighboring dozens
				if (m_index == EField::Dozen2)
					point.set_x(line5);
				else // m_index == EField::Dozen3
					point.set_x(line2);
				break;
			case EField::Number1:
				point.set_x(line2);
				break;
			case EField::Number4:
			case EField::Number16:
			case EField::Number28:
				point.set_x(line3);
				break;
			case EField::Number7:
			case EField::Number19:
			case EField::Number31:
				point.set_x(line4);
				break;
			case EField::Number10:
			case EField::Number22:
			case EField::Number34:
				point.set_x(line5);
				break;
			case EField::Number13: // has 2 neighboring dozens (1 and 2)
				if (m_index == EField::Dozen1)
					point.set_x(line5);
				else // m_index == EField::Dozen2
					point.set_x(line2);
			}
		}
		if (chip->first == EChip::Eraser)
		{
			clear(point);
			return;
		}

		type_chip_pair chip_pair = make_pair(chip->first, point);
		type_chip chip_copy = make_shared<type_chip_pair>(chip_pair);
		m_chips.push_back(chip_copy);

		if (refGdkWindow)
			refGdkWindow->invalidate(false);
	}

	void Field::on_signal_bet_top_left(const EField& sender, type_chip chip)
	{
		Gdk::Point point = chip->second;
		Gtk::Allocation alloc = get_allocation();
		const int width = alloc.get_width();
		point.set_x(0);
		point.set_y(0);

		const int line1	= 0;
		const int street1 = static_cast<int>(width * .126); // rounded up
		const int line2	= static_cast<int>(width * .25);
		const int street2 = static_cast<int>(width * .376); // rounded up
		const int line3	= static_cast<int>(width * .5);
		const int street3 = static_cast<int>(width * .626); // rounded up
		const int line4	= static_cast<int>(width * .75);
		const int street4 = static_cast<int>(width * .876); // rounded up
		const int line5	= width;

		if (m_index == EField::Dozen1 || m_index == EField::Dozen2 || m_index == EField::Dozen3)
		{
			switch (sender)
			{
			case EField::Number1:
			case EField::Number13:
			case EField::Number25:
				point.set_x(line1);
				break;
			case EField::Number4:
			case EField::Number16:
			case EField::Number28:
				point.set_x(line2);
				break;
			case EField::Number7:
			case EField::Number19:
			case EField::Number31:
				point.set_x(line3);
				break;
			case EField::Number22: // has 2 neighboring dozens
				if (m_index == EField::Dozen3)
					point.set_x(line1);
				else  // m_index == EField::Dozen2
					point.set_x(line4);
					break;
			case EField::Number34:
				point.set_x(line4);
				break;
			case EField::Number10: // has 2 neighboring dozens (1 and 2)
				if (m_index == EField::Dozen2)
					point.set_x(line1);
				else // m_index == EField::Dozen2
					point.set_x(line4);
			}
		}
		if (chip->first == EChip::Eraser)
		{
			clear(point);
			return;
		}

		type_chip_pair chip_pair = make_pair(chip->first, point);
		type_chip chip_copy = make_shared<type_chip_pair>(chip_pair);
		m_chips.push_back(chip_copy);

		if (refGdkWindow)
			refGdkWindow->invalidate(false);
	}

	void Field::on_signal_bet_bottom_right(const EField& sender, type_chip chip)
	{
		Gdk::Point point = chip->second;
		Gtk::Allocation alloc = get_allocation();
		point.set_x(alloc.get_width());
		point.set_y(alloc.get_height());

		if (m_index == EField::Number0)
		{
			switch (sender)
			{
			case EField::Number2:
				point.set_y(static_cast<int>(alloc.get_height() * .667)); // rounded up
				break;
			case EField::Number3:
				point.set_y(static_cast<int>(alloc.get_height() *.334)); // rounded up
			}
		}
		if (chip->first == EChip::Eraser)
		{
			clear(point);
			return;
		}

		type_chip_pair chip_pair = make_pair(chip->first, point);
		type_chip chip_copy = make_shared<type_chip_pair>(chip_pair);
		m_chips.push_back(chip_copy);

		if (refGdkWindow)
			refGdkWindow->invalidate(false);
	}

	void Field::on_signal_bet_bottom_left(const EField& /*sender*/, type_chip chip)
	{
		Gdk::Point point = chip->second;
		Gtk::Allocation alloc = get_allocation();
		point.set_x(0);
		point.set_y(alloc.get_height());

		if (chip->first == EChip::Eraser)
		{
			clear(point);
			return;
		}

		type_chip_pair chip_pair = make_pair(chip->first, point);
		type_chip chip_copy = make_shared<type_chip_pair>(chip_pair);
		m_chips.push_back(chip_copy);

		if (refGdkWindow)
			refGdkWindow->invalidate(false);
	}

#ifdef _MSC_VER
#pragma endregion signal handlers

#pragma region
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

			// TODO: going to full screen or resizing a window fast will not update points properly
			for (size_t i = 0; i < m_chips.size(); ++i)
			{
				calculate_points(m_chips.at(i), false);
			}
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
#pragma endregion widget
#endif // _MSC_VER

} // namespace roulette

///<summary>
//
//
// DRAG AND DROP CALL STACK
//
// on_drag_data_received
// 
// calculate_points
//
// signal.emit
//
// m_chips.push_back
//
// refGdkWindow->invalidate
//
// on_draw
//
// for_each cr->paint();
//
// draw neighboring chips
//
//
///<summary>

// not used
#if 0 // DEBUG_DND_LOG
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
#if 0
// TODO: this is redundant, make use of selection data
static const int format = 8;
if ((selection_data.get_length() == 0) && (selection_data.get_format() == format))
{
	context->drag_finish(true, false, time); // drop finished, data no longer required
}
#endif

#endif // DEBUG_DND_LOG
#if 0 //DEBUG_DND_LOG
cout << endl;
cout << "Field::on_drag_leave()" << endl;
cout << "-> INFO: time = " << time << endl;
#endif // DEBUG_DND_LOG
#if 0 // DEBUG_DND_LOG
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

#if 0 // DEBUG_DND_LOG
cout << endl;
cout << "Field::on_drag_drop()" << endl;
cout << "-> INFO: x = " << x << endl;
cout << "-> INFO: y = " << y << endl;
cout << "-> INFO: time = " << time << endl;
#endif // DEBUG_DND_LOG

#ifdef DEBUG_SIGNALS
cout << "clear: " << mName << endl;
#endif // DEBUG_SIGNALS
