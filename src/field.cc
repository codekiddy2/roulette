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
// DRAG AND DROP CALL STACK:
//
// on_drag_data_received
// calculate_points
// signal.emit
// m_chips.push_back
// refGdkWindow->invalidate
// on_draw
// for_each cr->paint();
// draw neighboring chips
//
///</summary>

// std
#include "pch.hh"
#include "field.hh"
#include "table.hh"
#include "main.hh"
#include "color.hh"
#include "engine.hh"

namespace roulette
{

#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER

	using std::cout;
	using std::endl;
	using std::to_string;
	using std::make_shared;
	using std::shared_ptr;
	using std::make_pair;
	using std::pair;

	extern std::vector<Gtk::TargetEntry> dnd_targets;
	
	Field::Field(EField field_index, Table* p_table) :
		Glib::ObjectBase("Field"), // The GType name will be gtkmm__CustomObject_Field
		Gtk::Widget(),
		IErrorHandler("Field"),
		m_background(Color::get_background_color()),
		mp_table(p_table),
		m_index(field_index)
	{
		if (!p_table) error_handler(error("Engine -> p_table is NULL"));

		set_has_window(true);
		set_events(Gdk::EventMask::ALL_EVENTS_MASK);

		assign_apperance(field_index);
		m_font.set_family("Arial");
		m_layout->set_font_description(m_font);

		mp_table->signal_clear_all.connect(sigc::mem_fun(*this, &Field::clear_all));

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
	// neighborng fields will adjust chip x y in signal handlers instead.
	// last parameter is used to avoid re-emiting signals on window resize.
	EBet Field::calculate_points(type_chip chip, bool emit /*= true*/)
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

		// default is center (ex: StraightUp)
		point.set_x(cx);
		point.set_y(cy);

		switch (m_index)
		{
		case roulette::EField::Number0:
			if (x < right)
				return EBet::StraightUp; // no chip drawing signal	
			else // x > right
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

				point.set_x(width);
				if (y < check_street1)
				{
					point.set_y(split1);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Split))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_split1.emit(m_index, chip);
					}
					break;
				}
				else if (y < check_split2)
				{
					point.set_y(street1);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Street))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_street1.emit(m_index, chip);
					}
				}
				else if (y < check_street2)
				{
					point.set_y(split2);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Split))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_split2.emit(m_index, chip);
					}
				}
				else if (y < check_split3)
				{
					point.set_y(street2);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Street))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_street2.emit(m_index, chip);
					}
				}
				else if (y < check_basket)
				{
					point.set_y(split3);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Corner))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_split3.emit(m_index, chip);
					}
				}
				else
				{
					point.set_y(basket);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Basket))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_basket.emit(m_index, chip);
					}
				}
			} // x > right
		break;
		case roulette::EField::Number3:
			if (x < left)
			{
				point.set_x(0);
				if (y > down)
				{
					point.set_y(height);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Corner))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_bottom_left.emit(m_index, chip);
					}
				}
				else if (emit)
				{
					if (mp_table->check_limits(m_chips, chip, EBet::Split))
						return EBet::LIMIT_EXCEEDED;
					signal_bet_left.emit(m_index, chip);
				}
			}
			else if (x > right)
			{
				point.set_x(width);
				if (y > down)
				{
					point.set_y(height);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Corner))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_bottom_right.emit(m_index, chip);
					}
				}
				else if (emit)
				{
					if (mp_table->check_limits(m_chips, chip, EBet::Split))
						return EBet::LIMIT_EXCEEDED;
					signal_bet_right.emit(m_index, chip);
				}
			}
			else if (y > down) // x == cx
			{
				point.set_y(height);
				if (emit)
				{
					if (mp_table->check_limits(m_chips, chip, EBet::Split))
						return EBet::LIMIT_EXCEEDED;
					signal_bet_bottom.emit(m_index, chip);
				}
			}
			else return EBet::StraightUp; // cx, cy -> no chip drawing signal
			break;
		case roulette::EField::Number34:
		case roulette::EField::Number35:
			if (x < left)
			{
				point.set_x(0);
				if (y < top)
				{
					point.set_y(0);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Corner))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_top_left.emit(m_index, chip);
					}
				}
				else if (y > down)
				{
					point.set_y(height);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Corner))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_bottom_left.emit(m_index, chip);
					}
				}
				else if (emit)
				{
					if (mp_table->check_limits(m_chips, chip, EBet::Split))
						return EBet::LIMIT_EXCEEDED;
					signal_bet_left.emit(m_index, chip);
				}
			}
			else if (y < top) // x == cx
			{
				point.set_y(0);
				if (emit)
				{
					if (mp_table->check_limits(m_chips, chip, EBet::Split))
						return EBet::LIMIT_EXCEEDED;
					signal_bet_top.emit(m_index, chip);
				}
			}
			else if (y > down)
			{
				point.set_y(height);
				if (emit)
				{
					if (mp_table->check_limits(m_chips, chip, EBet::Split))
						return EBet::LIMIT_EXCEEDED;
					signal_bet_bottom.emit(m_index, chip);
				}
			}
			else return EBet::StraightUp; // cx, cy -> no chip drawing signal
			break;
		case roulette::EField::Number36:
			if (x < left)
			{
				point.set_x(0);
				if (y > down)
				{
					point.set_y(height);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Corner))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_bottom_left.emit(m_index, chip);
					}
				}
				else if (emit)
				{
					if (mp_table->check_limits(m_chips, chip, EBet::Split))
						return EBet::LIMIT_EXCEEDED;
					signal_bet_left.emit(m_index, chip);
				}
			}
			else if (y > down) // x == cx
			{
				point.set_y(height);
				if (emit)
				{
					if (mp_table->check_limits(m_chips, chip, EBet::Split))
						return EBet::LIMIT_EXCEEDED;
					signal_bet_bottom.emit(m_index, chip);
				}
			}
			else return EBet::StraightUp; // cx, cy -> no chip drawing signal
			break;
		case roulette::EField::Number00:
			break;
		case roulette::EField::Red:
		case roulette::EField::Black:
		case roulette::EField::Even:
		case roulette::EField::Odd:
		case roulette::EField::High:
		case roulette::EField::Low:
		case roulette::EField::Column1:
		case roulette::EField::Column2:
		case roulette::EField::Column3:
			return static_cast<EBet>(m_index); // WARNING: this is supposed to be same enum number defined in sets.hh
		case roulette::EField::Dozen1:
		case roulette::EField::Dozen2:
		case roulette::EField::Dozen3:
			if (y > top)
				return static_cast<EBet>(m_index); // WARNING: this is supposed to be same enum number defined in sets.hh
			else // line or street bet
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

				point.set_y(0);
				if (x < check_street1)
				{
					point.set_x(line1);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Corner))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_line1.emit(m_index, chip);
					}
				}
				else if (x < check_line2)
				{
					point.set_x(street1);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Street))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_street1.emit(m_index, chip);
					}
				}
				else if (x < check_street2)
				{
					point.set_x(line2);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Line))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_line2.emit(m_index, chip);
					}
				}
				else if (x < check_line3)
				{
					point.set_x(street2);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Street))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_street2.emit(m_index, chip);
					}
				}
				else if (x < check_street3)
				{
					point.set_x(line3);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Line))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_line3.emit(m_index, chip);
					}
				}
				else if (x < check_line4)
				{
					point.set_x(street3);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Street))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_street3.emit(m_index, chip);
					}
				}
				else if (x < check_street4)
				{
					point.set_x(line4);
					if (emit) 
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Line))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_line4.emit(m_index, chip);
					}
				}
				else if (x < check_line5 || m_index == EField::Dozen3)  // skip line5 for dozen3
				{
					point.set_x(street4);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Street))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_street4.emit(m_index, chip);
					}
				}
				else // x > check_line5
				{
					point.set_x(line5);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Line))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_line5.emit(m_index, chip);
					}
				} // else if (y < top)
			break;
			} // else line or street bet
		case roulette::EField::Dummy1:
			if (x > right && y < top / 2)
			{
				point.set_x(width);
				point.set_y(0);
				if (emit)
				{
					if (mp_table->check_limits(m_chips, chip, EBet::Corner))
						return EBet::LIMIT_EXCEEDED;
					signal_bet_basket.emit(m_index, chip);
				}
				return EBet::Corner0;
			}
		case roulette::EField::Dummy2:
		case roulette::EField::Dummy3:
			break;
		case roulette::EField::Number1:
		case roulette::EField::Number2:
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
			if (x < left)
			{
				point.set_x(0);
				if (y < top && (which_column(m_index) != 3))
				{
					point.set_y(0);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Corner))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_top_left.emit(m_index, chip);
					}
				}
				else if (y > down)
				{
					point.set_y(height);
					if (emit)
					{
						if (which_column(m_index) == 1) // signal_bet_bottom_left can be either street, Line or Corner
						{
							if (m_index == EField::Number1)
							{
								if (mp_table->check_limits(m_chips, chip, EBet::Corner))
									return EBet::LIMIT_EXCEEDED;
							}
							if (mp_table->check_limits(m_chips, chip, EBet::Line))
								return EBet::LIMIT_EXCEEDED;
						}
						else if (mp_table->check_limits(m_chips, chip, EBet::Corner))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_bottom_left.emit(m_index, chip);
					}
				}
				else if (emit)
				{
					if (mp_table->check_limits(m_chips, chip, EBet::Split))
						return EBet::LIMIT_EXCEEDED;
					signal_bet_left.emit(m_index, chip);
				}
			}
			else if (x > right)
			{
				point.set_x(width);
				if (y < top && (which_column(m_index) != 3))
				{
					point.set_y(0);
					if (emit)
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Corner))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_top_right.emit(m_index, chip);
					}
				}
				else if (y > down)
				{
					point.set_y(height);
					if (emit)
					{
						if (which_column(m_index) == 1) // signal_bet_bottom_right can be either street or Line
						{
							if (mp_table->check_limits(m_chips, chip, EBet::Line))
								return EBet::LIMIT_EXCEEDED;
						}
						else if (mp_table->check_limits(m_chips, chip, EBet::Corner))
							return EBet::LIMIT_EXCEEDED;
						signal_bet_bottom_right.emit(m_index, chip);
					}
				}
				else if (emit)
				{
					if (mp_table->check_limits(m_chips, chip, EBet::Split))
						return EBet::LIMIT_EXCEEDED;
					signal_bet_right.emit(m_index, chip);
				}
			}
			else if (y < top && (which_column(m_index) != 3)) // x == cx
			{
				point.set_y(0);
				if (emit)
				{
					if (mp_table->check_limits(m_chips, chip, EBet::Split))
						return EBet::LIMIT_EXCEEDED;
					signal_bet_top.emit(m_index, chip);
				}
			}
			else if (y > down)
			{
				point.set_y(height);
				if (emit)
				{
					if (which_column(m_index) == 1) // signal_bet_bottom can be either street or split
					{
						if (mp_table->check_limits(m_chips, chip, EBet::Street))
							return EBet::LIMIT_EXCEEDED;
					}
					else if (mp_table->check_limits(m_chips, chip, EBet::Split))
						return EBet::LIMIT_EXCEEDED;
					signal_bet_bottom.emit(m_index, chip);
				}
			}
			else return EBet::StraightUp; // y == cy, x = cx
			break;
		default:
			error_handler(error("calculate_points -> missing case statement"));
		} // switch

		// the bet is undefined, it will be defined in signal handlers
		return EBet::UNDEFINED;
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

			mp_table->signal_bet.emit(make_shared<Bet>(EBet::StraightUp, chip,
				make_shared<type_raw_set>(type_raw_set{ static_cast<unsigned>(m_index) })));

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
			m_layout = create_pango_layout("00");
			break;
		case roulette::EField::Column1:
			m_layout = create_pango_layout("2 to 1");
			break;
		case roulette::EField::Column2:
			m_layout = create_pango_layout("2 to 1");
			break;
		case roulette::EField::Column3:
			m_layout = create_pango_layout("2 to 1");
			break;
		case roulette::EField::Dozen1:
			m_layout = create_pango_layout("1st 12");
			break;
		case roulette::EField::Dozen2:
			m_layout = create_pango_layout("2nd 12");
			break;
		case roulette::EField::Dozen3:
			m_layout = create_pango_layout("3rd 12");
			break;
		case roulette::EField::Red:
			m_background.set("Red");
			m_layout = create_pango_layout("RED");
			break;
		case roulette::EField::Black:
			m_background.set("Black");
			m_layout = create_pango_layout("BLACK");
			break;
		case roulette::EField::Even:
			m_layout = create_pango_layout("EVEN");
			break;
		case roulette::EField::Odd:
			m_layout = create_pango_layout("ODD");
			break;
		case roulette::EField::High:
			m_layout = create_pango_layout("HIGH");
			break;
		case roulette::EField::Low:
			m_layout = create_pango_layout("LOW");
			break;
		case roulette::EField::Dummy1:
		case roulette::EField::Dummy2:
		case roulette::EField::Dummy3:
			m_layout = create_pango_layout("");
			break;
		default:
			m_layout = create_pango_layout(to_string(static_cast<int>(index)));
			if (is_red(static_cast<int>(index)))
			{
				m_background.set("Red");
			}
			else if (is_black(static_cast<int>(index)))
			{
				m_background.set("Black");
			}
		} // switch
	}

	void Field::clear_all()
	{
		// TODO: some fields might not have Gdk::Window (dummies on different tables)
		if (refGdkWindow)
		{
			if (!m_chips.empty())
			{
				if (m_debug)
				{
					print("INFO: all chips cleared");
					print("Source: Field", true);
					print("Field index: ", true);
					print(m_index);
					print();
				} // if debug

				m_chips.clear();
				refGdkWindow->invalidate(false);
			}
		}
	}

	void Field::clear(Gdk::Point& chip_point)
	{
		if (m_chips.empty())
			return;

		auto iter = m_chips.begin();

		for (size_t i = 1; i <= m_chips.size(); ++i)
		{
			if (iter->get()->second.equal(chip_point))
			{
				if (m_debug)
				{
					print("INFO: clear chips");
					print("Source: Field", true);
					print("Field index: ", true);
					print(m_index);
					print();
				} // if debug

				m_chips.erase(iter);
				--i;
			} // if not end
			iter = m_chips.begin() + i;
		} // for
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
			if (m_debug)
			{
				print("INFO: drop refused");
				print("Source: Field", true);
				print("Reason: invalid target", true);
				print();
			} // if debug

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
		int x, int y, const Gtk::SelectionData& selection_data, guint info, guint time)
	{
		// chips can't be drawn on dummy2 
		if (m_index != EField::Dummy2)
		{
			if (selection_data.get_format() == format)
			{
				int length = selection_data.get_length();

				if (length == sizeof(Engine))
				{
					const Engine* p_engine = reinterpret_cast<const Engine*>(selection_data.get_data(length));

					if (p_engine)
					{
						// make chip, we need a chip regardless of bankroll status
						type_chip chip = make_shared<type_chip_pair>(make_pair(static_cast<EChip>(info), Gdk::Point(x, y)));

						// check bankroll
						if (p_engine->get_bankroll() >= info)
						{
							// check table limit
							if ((p_engine->get_bet() + info) > mp_table->get_table_limit())
							{
								Gtk::Window* top_window = dynamic_cast<Gtk::Window*>(get_toplevel());

								if (top_window->get_is_toplevel())
								{
									Gtk::MessageDialog dialog(*top_window, "Information");
									dialog.set_secondary_text("Table limit exceeded");
									dialog.set_position(Gtk::WIN_POS_CENTER);
									dialog.run();
									return context->drag_finish(true, false, time);
								} // if is_toplevel
								else error_handler(error("ERROR: get_toplevel did not return a top level window"));
							}
							// if bankroll and table limit is OK calculate chip drop zone
							EBet bet = calculate_points(chip);

							// refuse drop on dummy, accept if bet is Corner0 -> 0,1,2,3
							if ((m_index == EField::Dummy1) && (bet != EBet::Corner0))
							{
								if (m_debug)
								{
									print("INFO: drop refused");
									print("Source: Field", true);
									print("Reason: invalid target", true);
									print();
								} // if debug

								return context->drag_finish(true, false, time);
							} // if bad dummy

							// if table or bet limit is reached refuse drop
							if (bet == EBet::LIMIT_EXCEEDED)
							{
								return context->drag_finish(true, false, time);
							}
							else if (bet != EBet::UNDEFINED && bet != EBet::Corner0)
								if (mp_table->check_limits(m_chips, chip, bet))
									return context->drag_finish(true, false, time);

							if (m_debug)
							{
								print("INFO: chip dorpped");
								print("Source: Field", true);
								print("Field index: ", true);
								print(m_index);
								print();
							} // if debug

							// if this is eraser don't draw it, just clear existing chips
							chip->first != EChip::Eraser ?
								m_chips.push_back(chip) : clear(chip->second);

							type_set p_set = nullptr;

							// TODO: move line and street bets here too
							switch (bet)
							{
							case roulette::EBet::StraightUp:
								// TODO: making type_set for single number is not smart
								p_set = make_shared<type_raw_set>(type_raw_set{ static_cast<unsigned>(m_index) });
								break;
							case roulette::EBet::Column1:
								p_set = Column1;
								break;
							case roulette::EBet::Column2:
								p_set = Column2;
								break;
							case roulette::EBet::Column3:
								p_set = Column3;
								break;
							case roulette::EBet::Dozen1:
								p_set = Dozen1;
								break;
							case roulette::EBet::Dozen2:
								p_set = Dozen2;
								break;
							case roulette::EBet::Dozen3:
								p_set = Dozen3;
								break;
							case roulette::EBet::Red:
								p_set = Red;
								break;
							case roulette::EBet::Black:
								p_set = Black;
								break;
							case roulette::EBet::Even:
								p_set = Even;
								break;
							case roulette::EBet::Odd:
								p_set = Odd;
								break;
							case roulette::EBet::High:
								p_set = High;
								break;
							case roulette::EBet::Low:
								p_set = Low;
								break;
							default: // the bet is already emited by signal handlers during calculate_points
								return context->drag_finish(true, false, time);
							} // switch bet

							// emit bet not emited by signal handlers if limits are not reached
							mp_table->signal_bet.emit(make_shared<Bet>(bet, chip, p_set));
						} // if bankroll
						else if ((m_index == EField::Dummy1) && (calculate_points(chip, false) != EBet::Corner0) && m_debug)
						{
							print("INFO: drop refused");
							print("Source: Field", true);
							print("Reason: invalid target", true);
							print();
						}
						else // just out of bankroll
						{
							Gtk::Window* top_window = dynamic_cast<Gtk::Window*>(get_toplevel());

							if (top_window->get_is_toplevel())
							{
								Gtk::MessageDialog dialog(*top_window, "Information");
								dialog.set_secondary_text("Not enough bankroll to place a bet");
								dialog.set_position(Gtk::WIN_POS_CENTER);
								dialog.run();
							} // if is_toplevel
							else error_handler(error("ERROR: get_toplevel did not return a top level window"));
						} // if out of bankroll -> case handled
					} // if p_engine
					else error_handler(error("ERROR: p_engine is null"));
				} // if length of Engine
				else error_handler(error("ERROR: Engine length mismatch"));
			} // if format match
			else error_handler(error("EROOR: format does not match"));
		} // if not dummy2
		context->drag_finish(true, false, time);
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
		Gdk::Cairo::set_source_rgba(cr, m_background);
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

	// Draw text or number in the middle
	void Field::draw_text(const Cairo::RefPtr<Cairo::Context>& cr,
		int field_width, int field_height)
	{
		int text_width;
		int text_height;

		//get the text dimensions (it updates the variables -- by reference)
		m_layout->get_pixel_size(text_width, text_height);

		Gdk::Cairo::set_source_rgba(cr, Color::get_foreground_color());
		cr->move_to((field_width - text_width) / 2, (field_height - text_height) / 2);

		m_layout->show_in_cairo_context(cr);
	}

#ifdef _MSC_VER
#pragma endregion drawing

#pragma region
#endif // _MSC_VER

	// signal handlers emit bet signals for all bets except those emited in calculate_points function
	// the order of numbers in split and corner bets matters, it should be from lowest to highest
	// so that we do not need to sort selection of numbers, this is useful so that engine can
	// compare two sets on removing a bet.
	// TODO: check why need to check for gdkwindow, why throws
	void Field::on_signal_bet_bottom(const EField& sender, type_chip chip)
	{
		Gdk::Point point = chip->second;
		Gtk::Allocation alloc = get_allocation();
		point.set_x(static_cast<int>(alloc.get_width() * .5));
		point.set_y(alloc.get_height());

		// if signal is sent from dozens to first column we need to figure out on which numbers is street bet placed
		if (sender == EField::Dozen1 || sender == EField::Dozen2 || sender == EField::Dozen3)
		{
			type_set p_set = nullptr;

			switch (m_index)
			{
			case roulette::EField::Number1:
				p_set = Street1;
				break;
			case roulette::EField::Number4:
				p_set = Street2;
				break;
			case roulette::EField::Number7:
				p_set = Street3;
				break;
			case roulette::EField::Number10:
				p_set = Street4;
				break;
			case roulette::EField::Number13:
				p_set = Street5;
				break;
			case roulette::EField::Number16:
				p_set = Street6;
				break;
			case roulette::EField::Number19:
				p_set = Street7;
				break;
			case roulette::EField::Number22:
				p_set = Street8;
				break;
			case roulette::EField::Number25:
				p_set = Street9;
				break;
			case roulette::EField::Number28:
				p_set = Street10;
				break;
			case roulette::EField::Number31:
				p_set = Street11;
				break;
			case roulette::EField::Number34:
				p_set = Street12;
				break;
			default:
				error_handler(error("on_signal_bet_bottom -> case statement missing"));
			} // switch m_index
			if (!p_set) error_handler(error("on_signal_bet_bottom -> p_set is nullptr"));
			mp_table->signal_bet.emit(make_shared<Bet>(EBet::Street, chip, p_set));
		} // if sender is dozen
		else
		{
			// sender is number from column below, therefore their number is this fields' number - 1
			unsigned neighbor_number = static_cast<unsigned>(m_index) - 1;
			mp_table->signal_bet.emit(make_shared<Bet>(
				EBet::Split, chip, make_shared<type_raw_set>(
					type_raw_set{ neighbor_number, static_cast<unsigned>(m_index) })));
		}

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

		// if signal is sent from first column to dozens we need to figure out on which numbers is street bet placed
		if (m_index == EField::Dozen1 || m_index == EField::Dozen2 || m_index == EField::Dozen3)
		{
			type_set p_set = nullptr;

			switch (sender)
			{
			case EField::Number1:
				point.set_x(street1);
				p_set = Street1;
				break;
			case EField::Number13:
				point.set_x(street1);
				p_set = Street5;
				break;
			case EField::Number25:
				point.set_x(street1);
				p_set = Street9;
				break;
			case EField::Number4:
				point.set_x(street2);
				p_set = Street2;
				break;
			case EField::Number16:
				point.set_x(street2);
				p_set = Street6;
				break;
			case EField::Number28:
				point.set_x(street2);
				p_set = Street10;
				break;
			case EField::Number7:
				point.set_x(street3);
				p_set = Street3;
				break;
			case EField::Number19:
				point.set_x(street3);
				p_set = Street7;
				break;
			case EField::Number31:
				point.set_x(street3);
				p_set = Street11;
				break;
			case EField::Number10:
				point.set_x(street4);
				p_set = Street4;
				break;
			case EField::Number22:
				point.set_x(street4);
				p_set = Street8;
				break;
			case EField::Number34:
				point.set_x(street4);
				p_set = Street12;
				break;
			default:
				error_handler(error("on_signal_bet_top -> case statement missing"));
			} // switch sender
			if (!p_set) error_handler(error("on_signal_bet_top -> p_set is nullptr"));
			mp_table->signal_bet.emit(make_shared<Bet>(EBet::Street, chip, p_set));
		} // if dozen
		else
		{
			// sender is number from column above, therefore their number is this fields' number + 1
			unsigned neighbor_number = static_cast<unsigned>(m_index) + 1;
			mp_table->signal_bet.emit(make_shared<Bet>(
				EBet::Split, chip, make_shared<type_raw_set>(
					type_raw_set{ static_cast<unsigned>(m_index), neighbor_number })));
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

	void Field::on_signal_bet_left(const EField& /*sender*/, type_chip chip)
	{
		Gdk::Point point = chip->second;
		Gtk::Allocation alloc = get_allocation();
		point.set_x(0);
		point.set_y(static_cast<int>(alloc.get_height() * .5));

		if (m_index > EField::Number2)
		{
			// sender is number from the left, therefore their number is this fields' number - 3
			unsigned neighbor_number = static_cast<unsigned>(m_index) - 3;
			mp_table->signal_bet.emit(make_shared<Bet>(
				EBet::Split, chip, make_shared<type_raw_set>(
					type_raw_set{ neighbor_number, static_cast<unsigned>(m_index) })));
		}
		else // this is number 1 or 2 and neighbor is 0
		{
			mp_table->signal_bet.emit(make_shared<Bet>(
				EBet::Split, chip, make_shared<type_raw_set>(
					type_raw_set{ 0, static_cast<unsigned>(m_index) })));
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
				break;
			}
			// sender is either 1, 2 or 3 so we need to adjust on which numbers the bet is placed (0 and sender)
			mp_table->signal_bet.emit(make_shared<Bet>(
				EBet::Split, chip, make_shared<type_raw_set>(
					type_raw_set{ static_cast<unsigned>(m_index), static_cast<unsigned>(sender) })));
		}
		else if (m_index <= EField::Number36)
		{
			// sender is number from the right, therefore their number is this fields' number + 3
			unsigned neighbor_number = static_cast<unsigned>(m_index) + 3;
			mp_table->signal_bet.emit(make_shared<Bet>(
				EBet::Split, chip, make_shared<type_raw_set>(
					type_raw_set{ static_cast<unsigned>(m_index), neighbor_number })));
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
		type_set p_set = nullptr; // global
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
				mp_table->signal_bet.emit(make_shared<Bet>(EBet::Street, chip, Street01));
				break;
			case EField::Number2:
				point.set_y(static_cast<int>(alloc.get_height() * .334)); // rounded up
				mp_table->signal_bet.emit(make_shared<Bet>(EBet::Street, chip, Street02));
			}
		}
		// if signal is sent from first column to dozens we need to figure out on which numbers is line bet placed
		else if (m_index == EField::Dozen1 || m_index == EField::Dozen2 || m_index == EField::Dozen3)
		{
			switch (sender)
			{
			case EField::Number25: // has 2 neighboring dozens
				if (m_index == EField::Dozen2)
				{
					point.set_x(line5);
					p_set = Line8;
				}
				else // m_index == EField::Dozen3
				{
					point.set_x(line2);
					p_set = Line9;
				}
				break;
			case EField::Number1:
				point.set_x(line2);
				p_set = Line1;
				break;
			case EField::Number4:
				point.set_x(line3);
				p_set = Line2;
				break;
			case EField::Number16:
				point.set_x(line3);
				p_set = Line6;
				break;
			case EField::Number28:
				point.set_x(line3);
				p_set = Line10;
				break;
			case EField::Number7:
				point.set_x(line4);
				p_set = Line3;
				break;
			case EField::Number19:
				point.set_x(line4);
				p_set = Line7;
				break;
			case EField::Number31:
				point.set_x(line4);
				p_set = Line11;
				break;
			case EField::Number10:
				point.set_x(line5);
				if (m_index != EField::Dozen2) goto dozen_2_will_emit_this_bet;
				p_set = Line4;
				break;
			case EField::Number22:
				point.set_x(line5);
				p_set = Line8;
				break;
			case EField::Number34:
				point.set_x(line5);
				// no signal
				break;
			case EField::Number13: // has 2 neighboring dozens (1 and 2)
				if (m_index == EField::Dozen1)
				{
					point.set_x(line5);
					if (m_index != EField::Dozen2) goto dozen_2_will_emit_this_bet;
					p_set = Line4;
				}
				else // m_index == EField::Dozen2
				{
					point.set_x(line2);
					p_set = Line5;
				}
				break;
			case EField::Dozen2:
				p_set = Line4;
				break;
			case EField::Dozen3:
				p_set = Line8;
				break;
			default:
				error_handler(error("on_signal_bet_top_right -> case statement missing"));
			} // switch sender
			if (!p_set) error_handler(error("on_signal_bet_top_right -> p_set is nullptr"));
			mp_table->signal_bet.emit(make_shared<Bet>(EBet::Line, chip, p_set));
		} // if dozen
		// TODO: temp check
		else if ((m_index == EField::Dummy1) && (sender == EField::Dozen1)) // Corner0
		{
			mp_table->signal_bet.emit(make_shared<Bet>(EBet::Corner, chip, Corner0));
		}
		else if((sender != EField::Number0) && (sender != EField::Number1)) // signal is received from column 2 or 3 (corner bets)
		{
			unsigned neighbor1 = static_cast<unsigned>(m_index) + 1;
			unsigned neighbor2 = static_cast<unsigned>(m_index) + 3;
			unsigned neighbor3 = static_cast<unsigned>(m_index) + 4;
			p_set = make_shared<type_raw_set>(type_raw_set{static_cast<unsigned>(m_index), neighbor1, neighbor2, neighbor3});
			mp_table->signal_bet.emit(make_shared<Bet>(EBet::Corner, chip, p_set));
		}
	// signal will be emited by dozen2, skip re-emiting
	dozen_2_will_emit_this_bet:

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
		type_set p_set = nullptr; // global
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

		// if signal is sent from first column to dozens we need to figure out on which numbers is line bet placed
		if (m_index == EField::Dozen1 || m_index == EField::Dozen2 || m_index == EField::Dozen3)
		{
			switch (sender)
			{
			case EField::Dummy1:
			case EField::Number0:
			case EField::Number1: // corner 0,1,2,3
				point.set_x(line1);
				p_set = Corner0;
				break;
			case EField::Number13:
				point.set_x(line1);
				p_set = Line4;
				break;
			case EField::Number25:
				point.set_x(line1);
				if (m_index != EField::Dozen2) goto dozen_2_will_emit_this_bet;
				p_set = Line8;
				break;
			case EField::Number4:
				point.set_x(line2);
				p_set = Line1;
				break;
			case EField::Number16:
				point.set_x(line2);
				p_set = Line5;
				break;
			case EField::Number28:
				point.set_x(line2);
				p_set = Line9;
				break;
			case EField::Number7:
				point.set_x(line3);
				p_set = Line2;
				break;
			case EField::Number19:
				point.set_x(line3);
				p_set = Line6;
				break;
			case EField::Number31:
				point.set_x(line3);
				p_set = Line10;
				break;
			case EField::Number22: // has 2 neighboring dozens
				if (m_index == EField::Dozen3)
				{
					point.set_x(line1);
					if (m_index != EField::Dozen2) goto dozen_2_will_emit_this_bet;
					p_set = Line8;
				}
				else  // m_index == EField::Dozen2
				{
					point.set_x(line4);
					p_set = Line7;
				}
				break;
			case EField::Number34:
				point.set_x(line4);
				p_set = Line11;
				break;
			case EField::Number10: // has 2 neighboring dozens (1 and 2)
				if (m_index == EField::Dozen2)
				{
					point.set_x(line1);
					p_set = Line4;
				}
				else // m_index == EField::Dozen1
				{
					point.set_x(line4);
					p_set = p_set = Line3;
				}
				break;
			case EField::Dozen2:
				p_set = Line8;
				break;
			case EField::Dozen1:
				p_set = Line4;
				break;
			default:
				error_handler(error("on_signal_bet_top_left -> case statement missing"));
			} // switch sender
			if (!p_set) error_handler(error("on_signal_bet_top_left -> p_set is nullptr"));
			// this is either corner bet (0, 1, 2, 3) or line bet.
			((sender == EField::Number1) || (sender == EField::Number0) || (sender == EField::Dummy1)) ?
				mp_table->signal_bet.emit(make_shared<Bet>(EBet::Corner, chip, p_set)) :
			mp_table->signal_bet.emit(make_shared<Bet>(EBet::Line, chip, p_set));
		} // if dozen
		else if (sender == EField::Number0)
		{
			m_index == EField::Number1 ?
				mp_table->signal_bet.emit(make_shared<Bet>(EBet::Street, chip, Street01)) :
				mp_table->signal_bet.emit(make_shared<Bet>(EBet::Street, chip, Street02)); // m_index == Efield::Number2
		}
		// signal is received from column 2 or 3 (corner bets)
		else if(static_cast<unsigned>(sender) == (static_cast<unsigned>(m_index) - 3) )
		{
			unsigned neighbor1 = static_cast<unsigned>(m_index) - 3;
			unsigned neighbor2 = static_cast<unsigned>(m_index) - 2;
			unsigned neighbor3 = static_cast<unsigned>(m_index) + 1;
			p_set = make_shared<type_raw_set>(type_raw_set{ neighbor1, neighbor2, static_cast<unsigned>(m_index), neighbor3 });
			mp_table->signal_bet.emit(make_shared<Bet>(EBet::Corner, chip, p_set));
		}

	// signal will be emited by dozen2, skip re-emiting
	dozen_2_will_emit_this_bet:

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
				mp_table->signal_bet.emit(make_shared<Bet>(EBet::Street, chip, Street01));
				break;
			case EField::Number3:
				point.set_y(static_cast<int>(alloc.get_height() *.334)); // rounded up
				mp_table->signal_bet.emit(make_shared<Bet>(EBet::Street, chip, Street02));
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

	void Field::on_signal_bet_bottom_left(const EField& sender, type_chip chip)
	{
		Gdk::Point point = chip->second;
		Gtk::Allocation alloc = get_allocation();
		point.set_x(0);
		point.set_y(alloc.get_height());

		// if signal is sent from dozens to first column we need to figure out on which numbers is line bet placed
		if (sender == EField::Dozen1 || sender == EField::Dozen2 || sender == EField::Dozen3)
		{
			type_set p_set = nullptr;

			switch (m_index)
			{
			case roulette::EField::Number4:
				p_set = Line1;
				break;
			case roulette::EField::Number7:
				p_set = Line2;
				break;
			case roulette::EField::Number10:
				p_set = Line3;
				break;
			case roulette::EField::Number13:
				if (m_index != EField::Dozen2) goto dozen_2_will_emit_this_bet;
				p_set = Line4;
				break;
			case roulette::EField::Number16:
				p_set = Line5;
				break;
			case roulette::EField::Number19:
				p_set = Line6;
				break;
			case roulette::EField::Number22:
				p_set = Line7;
				break;
			case roulette::EField::Number25:
				if (m_index != EField::Dozen2) goto dozen_2_will_emit_this_bet;
				p_set = Line8;
				break;
			case roulette::EField::Number28:
				p_set = Line9;
				break;
			case roulette::EField::Number31:
				p_set = Line10;
				break;
			case roulette::EField::Number34:
				p_set = Line11;
				break;
			default:
				if(m_index != EField::Number1)
					error_handler(error("on_signal_bet_bottom_left -> case statement missing"));
			} // switch m_index

			if (!p_set && (m_index != EField::Number1))
				error_handler(error("on_signal_bet_bottom_left -> p_set is nullptr"));

			if (m_index != EField::Number1)
				mp_table->signal_bet.emit(make_shared<Bet>(EBet::Line, chip, p_set));
		} // if sender is dozen

	// signal will be emited by dozen2, skip re-emiting
	dozen_2_will_emit_this_bet:

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
