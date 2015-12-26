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
// infobar.cc
//
// Defines Infobar class
//
///</summary>

// roulette
#include "pch.hh"
#include "infobar.hh"
#include "engine.hh"
#include "table.hh"

// std
#include <string>
using std::to_string;

#include <utility>

namespace roulette
{

#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER

	using std::string;
	using std::to_string;
	using std::make_pair;

	InfoBar::InfoBar(Engine* p_engine, Table* p_table) :
		IErrorHandler("InfoBar"),
		mp_engine(p_engine),
		mp_table(p_table)
	{
		// InfoBar properties
		set_size_request(500, 100);
		font.set_family("Arial");

		// status
		m_layouts.insert(make_pair(ELayout::Bankroll, create_pango_layout("Bankroll\t" + to_string(mp_engine->get_bankroll()))));
		m_layouts.insert(make_pair(ELayout::TotalBet, create_pango_layout("Total Bet")));
		m_layouts.insert(make_pair(ELayout::LastBet, create_pango_layout("Last bet")));
		m_layouts.insert(make_pair(ELayout::Numbers, create_pango_layout("Numbers")));
		// limits
		m_layouts.insert(make_pair(ELayout::InsideMin, create_pango_layout("Inside min\t\t" + to_string(mp_table->get_minimum(EMinimum::Inside)))));
		m_layouts.insert(make_pair(ELayout::OutsideMin, create_pango_layout("Outside min\t" + to_string(mp_table->get_minimum(EMinimum::Outside)))));
		m_layouts.insert(make_pair(ELayout::TableMin, create_pango_layout("Table min\t\t" + to_string(mp_table->get_minimum(EMinimum::Table)))));
		m_layouts.insert(make_pair(ELayout::TableMax, create_pango_layout("Table max\t\t" + to_string(mp_table->get_table_limit()))));
		// inside bets
		m_layouts.insert(make_pair(ELayout::Inside, create_pango_layout("Inside bets\tpays\t\tlimit")));
		m_layouts.insert(make_pair(ELayout::Straight, create_pango_layout("Straight\t\t35 to 1\t" + to_string(mp_table->get_limit(EBet::StraightUp)))));
		m_layouts.insert(make_pair(ELayout::Split, create_pango_layout("Split\t\t\t17 to 1\t" + to_string(mp_table->get_limit(EBet::Split)))));
		m_layouts.insert(make_pair(ELayout::Street, create_pango_layout("Street\t\t11 to 1\t" + to_string(mp_table->get_limit(EBet::Street)))));
		m_layouts.insert(make_pair(ELayout::Corner, create_pango_layout("Corner\t\t8 to 1\t" + to_string(mp_table->get_limit(EBet::Corner)))));
		m_layouts.insert(make_pair(ELayout::Line, create_pango_layout("Line\t\t\t5 to 1\t" + to_string(mp_table->get_limit(EBet::Line)))));
		// outside bets
		m_layouts.insert(make_pair(ELayout::Outside, create_pango_layout("Outside bets\tpays\t\tlimit")));
		m_layouts.insert(make_pair(ELayout::Dozen, create_pango_layout("Dozen\t\t2 to 1\t" + to_string(mp_table->get_limit(EBet::Dozen1)))));
		m_layouts.insert(make_pair(ELayout::High_Low, create_pango_layout("High/Low\t\t1 to 1\t" + to_string(mp_table->get_limit(EBet::High)))));
		m_layouts.insert(make_pair(ELayout::Red_Black, create_pango_layout("Red/Black\t\t1 to 1\t" + to_string(mp_table->get_limit(EBet::Red)))));
		m_layouts.insert(make_pair(ELayout::Even_Odd, create_pango_layout("Even/Odd\t\t1 to 1\t" + to_string(mp_table->get_limit(EBet::Even)))));
		m_layouts.insert(make_pair(ELayout::Column, create_pango_layout("Column\t\t2 to 1\t" + to_string(mp_table->get_limit(EBet::Column1)))));

		for (auto pair : m_layouts)
		{
			pair.second->set_font_description(font);
		}
	}

#ifdef _MSC_VER
#pragma endregion begin
#pragma region
#endif // _MSC_VER

	bool InfoBar::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
	{
		if (m_layouts.empty())
		{
			return false;
		}

		int text_width;
		int text_height;

		m_layouts.begin()->second->get_pixel_size(text_width, text_height);

		Gtk::Allocation alloc = get_allocation();
		const int width = alloc.get_width();
		const int height = alloc.get_height();
		// inside bets
		const int inside_bets_x = 0;
		const int inside_bets_y = 0;
		const int straight_x = 0;
		const int straight_y = text_height;
		const int split_x = 0;
		const int split_y = text_height * 2;
		const int street_x = 0;
		const int street_y = text_height * 3;
		const int corner_x = 0;
		const int corner_y = text_height * 4;
		const int line_x = 0;
		const int line_y = text_height * 5;
		// outside bets
		const int outside_bets_x = width / 4;
		const int outside_bets_y = 0;
		const int dozen_x = width / 4;
		const int dozen_y = text_height;
		const int column_x = width / 4;
		const int column_y = text_height * 2;
		const int red_black_x = width / 4;
		const int red_black_y = text_height * 3;
		const int odd_even_x = width / 4;
		const int odd_even_y = text_height * 4;
		const int low_high_x = width / 4;
		const int low_high_y = text_height * 5;
		// table limits
		const int inside_min_x = width / 2;
		const int inside_min_y = 0;
		const int outside_min_x = width / 2;
		const int outside_min_y = text_height;
		const int tablemin_x = width / 2;
		const int tablemin_y = text_height * 2;
		const int tablemax_x = width / 2;
		const int tablemax_y = text_height * 3;
		// bankroll and bet
		const int bankroll_x = static_cast<int>(width * .70);
		const int bankroll_y = 0;
		const int bet_x = static_cast<int>(width * .70);
		const int bet_y = text_height;
		const int last_bet_x = static_cast<int>(width * .70);
		const int last_bet_y = text_height * 2;
		const int numbers_x = static_cast<int>(width * .70);
		const int numbers_y = text_height * 3;


		Gdk::Cairo::set_source_rgba(cr, m_background);
		cr->paint();
		Gdk::Cairo::set_source_rgba(cr, m_foreground);

		// inside bets
		cr->move_to(inside_bets_x, inside_bets_y);
		m_layouts.find(ELayout::Inside)->second->show_in_cairo_context(cr);
		cr->move_to(straight_x, straight_y);
		m_layouts.find(ELayout::Straight)->second->show_in_cairo_context(cr);
		cr->move_to(split_x, split_y);
		m_layouts.find(ELayout::Split)->second->show_in_cairo_context(cr);
		cr->move_to(street_x, street_y);
		m_layouts.find(ELayout::Street)->second->show_in_cairo_context(cr);
		cr->move_to(corner_x, corner_y);
		m_layouts.find(ELayout::Corner)->second->show_in_cairo_context(cr);
		cr->move_to(line_x, line_y);
		m_layouts.find(ELayout::Line)->second->show_in_cairo_context(cr);
		// outside bets
		cr->move_to(outside_bets_x, outside_bets_y);
		m_layouts.find(ELayout::Outside)->second->show_in_cairo_context(cr);
		cr->move_to(dozen_x, dozen_y);
		m_layouts.find(ELayout::Dozen)->second->show_in_cairo_context(cr);
		cr->move_to(column_x, column_y);
		m_layouts.find(ELayout::Column)->second->show_in_cairo_context(cr);
		cr->move_to(low_high_x, low_high_y);
		m_layouts.find(ELayout::High_Low)->second->show_in_cairo_context(cr);
		cr->move_to(red_black_x, red_black_y);
		m_layouts.find(ELayout::Red_Black)->second->show_in_cairo_context(cr);
		cr->move_to(odd_even_x, odd_even_y);
		m_layouts.find(ELayout::Even_Odd)->second->show_in_cairo_context(cr);
		// table minimums
		cr->move_to(inside_min_x, inside_min_y);
		m_layouts.find(ELayout::InsideMin)->second->show_in_cairo_context(cr);
		cr->move_to(outside_min_x, outside_min_y);
		m_layouts.find(ELayout::OutsideMin)->second->show_in_cairo_context(cr);
		cr->move_to(tablemin_x, tablemin_y);
		m_layouts.find(ELayout::TableMin)->second->show_in_cairo_context(cr);
		cr->move_to(tablemax_x, tablemax_y);
		m_layouts.find(ELayout::TableMax)->second->show_in_cairo_context(cr);
		// bankrol and bet 
		cr->move_to(bankroll_x, bankroll_y);
		m_layouts.find(ELayout::Bankroll)->second->show_in_cairo_context(cr);
		cr->move_to(bet_x, bet_y);
		m_layouts.find(ELayout::TotalBet)->second->show_in_cairo_context(cr);
		cr->move_to(last_bet_x, last_bet_y);
		m_layouts.find(ELayout::LastBet)->second->show_in_cairo_context(cr);
		cr->move_to(numbers_x, numbers_y);
		m_layouts.find(ELayout::Numbers)->second->show_in_cairo_context(cr);

		return true;
	}

	void InfoBar::on_update(type_bet /*bet*/)
	{
		auto result = m_layouts.find(ELayout::Bankroll);
		if (result != m_layouts.end())
		{
			result->second->set_text("Bankroll\t" + to_string(mp_engine->get_bankroll()));
		}
		else error_handler(error("on_signal_bet -> layout not found"));

		result = m_layouts.find(ELayout::TotalBet);
		if (result != m_layouts.end())
		{
			result->second->set_text("TotalBet\t" + to_string(mp_engine->get_bet()));
		}
		else error_handler(error("on_signal_bet -> layout not found"));

		result = m_layouts.find(ELayout::LastBet);
		if (result != m_layouts.end())
		{
			result->second->set_text("Last Bet\t" + to_string(mp_engine->get_last_bet()));
		}
		else error_handler(error("on_signal_bet -> layout not found"));

		result = m_layouts.find(ELayout::Numbers);
		if (result != m_layouts.end())
		{
			string numbers = "";
			type_set number_set = mp_engine->get_numbers(); // could be nullptr (ex: no bets are placed)

			if (number_set)
			{
				type_raw_set::const_iterator iter = number_set->begin();

				if (number_set->size() > 8) // let layout show 8 numbers in a row
				{
					for (size_t i = 0; i < 8; i++, iter++)
					{
						numbers.append(to_string(*iter));
						numbers.append(" ");
					}
					numbers.append("\n\t\t");
				}
				while (iter != number_set->end()) // show the rest in second row (if any)
				{
					numbers.append(to_string(*iter));
					numbers.append(" ");
					++iter;
				}
			}
			result->second->set_text("Numbers\t" + numbers); // show numbers (if any)
		}
		else error_handler(error("on_signal_bet -> layout not found"));

		// TODO: move assignement into constructor
		if (!refGdkWindow)
		{
			refGdkWindow = get_window();
		}
		refGdkWindow->invalidate(false);
	}

#ifdef _MSC_VER
#pragma endregion methods
#endif // _MSC_VER

} // namespace roulette
