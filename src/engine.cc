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
//	engine.cc
//
//	Definition of Engine class
//
//	TODO: add description
//
///</summary>

#include "pch.hh"
#include "engine.hh"
#include "main.hh"
#include "history.hh" // forward declared class
//#include "infobar.hh"
#include "table.hh"

namespace roulette
{

#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER


	using std::string;
	using std::to_string;

	boost::random::random_device Engine::m_rng;

	Engine::Engine(Table* p_table, History* p_history/*, InfoBar* p_infobar*/) :
		IErrorHandler("Chip"),
		mp_table(p_table),
		mp_history(p_history)
	{
		if(!p_table) error_handler(error("Engine -> p_table is NULL"));
		if(!p_history) error_handler(error("spin -> p_infobar is NULL"));

		mp_table->signal_bet.connect(sigc::mem_fun(*this, &Engine::place_bet));
	}

#ifdef _MSC_VER
#pragma endregion begin

#pragma region
#endif // _MSC_VER

	void Engine::place_bet(std::shared_ptr<Bet> bet)
	{
		if (!bet->get_selection()) error_handler(error("place_bet -> bet contains no numbers"));

		for (auto var : *bet->get_selection())
		{
			if((var < 0) || (var > 36))
				error_handler(error("place_bet -> bet contains invalid numbers"));
		}

		switch (bet->get_id())
		{
		case roulette::EBet::UNDEFINED:
			error_handler(error("place_bet -> invalid bet 'UNDEFINED'"));
			break;
		case roulette::EBet::StraightUp:
			if (bet->get_selection()->size() != 1) error_handler(error("place_bet -> invalid numbers for StraightUp"));
			break;
		case roulette::EBet::Split:
			if (bet->get_selection()->size() != 2) error_handler(error("place_bet -> invalid numbers for Split"));
			break;
		case roulette::EBet::Street:
			if (bet->get_selection()->size() != 3) error_handler(error("place_bet -> invalid numbers for Street"));
			break;
		case roulette::EBet::Corner:
			if (bet->get_selection()->size() != 4) error_handler(error("place_bet -> invalid numbers for Corner"));
			break;
		case roulette::EBet::Line:
			if (bet->get_selection()->size() != 6) error_handler(error("place_bet -> invalid numbers for Line"));
			break;
		case roulette::EBet::Column1:
		case roulette::EBet::Column2:
		case roulette::EBet::Column3:
		case roulette::EBet::Dozen1:
		case roulette::EBet::Dozen2:
		case roulette::EBet::Dozen3:
			if (bet->get_selection()->size() != 12) error_handler(error("place_bet -> invalid bet"));
			break;
		case roulette::EBet::Red:
		case roulette::EBet::Black:
		case roulette::EBet::Even:
		case roulette::EBet::Odd:
		case roulette::EBet::High:
		case roulette::EBet::Low:
			if (bet->get_selection()->size() != 18) error_handler(error("place_bet -> invalid bet"));
			break;
		case roulette::EBet::Basket:
			if (bet->get_selection()->size() != 5) error_handler(error("place_bet -> invalid numbers for basket"));
			break;
		default:
			print("WARNING: place_bet -> bet not implemented");
			break;
		}
		m_bets.push_back(bet);
		m_last_bet = bet->get_chips();
		m_bankroll -= m_last_bet;
		m_current_bet += m_last_bet;

		if (m_debug)
		{
			print("INFO: bet placed ");
			print("Chips: ", true);
			print(bet->get_chips());
			print("Numbers: ", true);

			for (auto num : *m_bets.back()->get_selection())
			{
				print(num);
				print(" ");
			}
			std::cout << std::endl;
		}
	}

	void Engine::spin(const ETable table_type)
	{
		typedef boost::random::uniform_smallint<> type_dist;
		if(mp_table->get_table_type() != table_type) error_handler(error("spin -> this table does not exist"));

		string red_output, black_output, green_output;
		string single_space = " ", triple_space = "   ", newline = "\n", tab = "\t";

		switch (table_type)
		{
		case ETable::NoZero:
			error_handler(error("spin -> table_type not implemented"));
			break;
		case ETable::European:
		{
			static type_dist dist(0, static_cast<int>(EuropeanWheel->size()));
			int result = dist(Engine::m_rng);

			// format result to be properly aligned with past results
			if (result == 0)
			{
				green_output.append(triple_space + to_string(result) + tab);
			}
			else if (is_red(result))
			{
				red_output.append(triple_space + to_string(result) + tab);
			}
			else // black result :)
			{
				black_output.append(single_space + to_string(result) + tab);
			}

			// what ever the result each column in history applies text
			green_output.append(newline);
			green_output.append(mp_history->get_green_buffer_text());

			red_output.append(newline);
			red_output.append(mp_history->get_red_buffer_text());

			black_output.append(newline);
			black_output.append(mp_history->get_black_buffer_text());

			mp_history->set_green_buffer_text(green_output);
			mp_history->set_red_buffer_text(red_output);
			mp_history->set_black_buffer_text(black_output);

			// apply colors
			mp_history->apply_tags();
			break;
		}
		case ETable::American:
		case ETable::French:
		case ETable::SingleImprisonment:
		case ETable::DoubleImprisonment:
		case ETable::TripleImprisonment:
		case ETable::InfininiteImprisonment:
			error_handler(error("spin -> table_type not implemented"));
			break;
		}
	}

#ifdef _MSC_VER
#pragma endregion methods
#endif // _MSC_VER

} // namespace roulette
