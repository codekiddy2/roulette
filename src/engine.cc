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
///</summary>

// roulette
#include "pch.hh"
#include "engine.hh"
#include "main.hh"

// std
#include <algorithm>
using std::equal;

namespace roulette
{

#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER

	boost::random::random_device Engine::m_rng;

	Engine::Engine() :
		IErrorHandler("Engine"),
		m_current_bet(0),
		m_last_bet(0),
		m_bankroll(2000)
	{
	}

#ifdef _MSC_VER
#pragma endregion begin

#pragma region
#endif // _MSC_VER

	void Engine::place_bet(type_bet bet)
	{
		// do not count eraser as a bet EChip::Eraser equals to 0
		if (!bet->get_chip_value())
			return clear_bet(bet);

		if (m_debug)
		{
			if (!bet->get_selection())
				error_handler(error("place_bet -> bet contains no numbers"));

			for (auto var : *bet->get_selection())
			{
				if ((var < 0) || (var > 36))
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
		} // if debug

		m_bets.push_back(bet);
		m_last_bet = bet->get_chip_value();
		m_bankroll -= m_last_bet;
		m_current_bet += m_last_bet;

		if (m_debug)
		{
			print("INFO: bet placed ");
			print("Source: Engine", true);
			print("Chips: ", true);
			print(bet->get_chip_value());
			print("Numbers: ", true);

			for (auto num : *m_bets.back()->get_selection())
			{
				print(num);
				print(" ");
			}
			print();
		} // if debug
	}

	void Engine::spin(const ETable table_type)
	{
		typedef boost::random::uniform_smallint<> type_dist;

		switch (table_type)
		{
		case ETable::NoZero:
			error_handler(error("spin -> table_type not implemented"));
			break;
		case ETable::European:
		{
			static type_dist dist(0, static_cast<int>(EuropeanWheel->size()));
			int result = dist(Engine::m_rng);

			signal_spin.emit(result);
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

	void Engine::clear_all_bets()
	{
		if (!m_bets.empty())
		{
			for (auto bet : m_bets)
			{
				m_bankroll += bet->get_chip_value();
			}

			m_current_bet = 0;
			m_last_bet = 0;
			m_bets.clear();

			if (m_debug)
			{
				print("INFO: all bets cleared");
				print("Source: Engine", true);
				print();
			} // if debug
		}
	}

	void Engine::clear_bet(type_bet& bet)
	{
		if (m_bets.empty())
			return;

		auto iter = m_bets.begin();
		type_set selection = bet->get_selection();

		// begin from current bet, which is first element
		for (size_t current = 1; current <= m_bets.size(); ++current)
		{
			// if Bet types (id's) and thus the amount of numbers do not match then std::equal will not work as expected,
			// for example split bet 1,2 will be treated same as bet column2 which is 1,2,3... by std::equal
			if (bet->get_id() == iter->get()->get_id())
			{
				// all numbers *including* the order of sequence must match, it's important both number selections are sorted
				// we achieve this during bet construction in signal handlers while emiting
				if (equal(selection->begin(), selection->end(), iter->get()->get_selection()->begin()))
				{
					if (m_debug)
					{
						print("INFO: bet removed");
						print("Source: Engine", true);
						print("Chips: ", true);
						print(iter->get()->get_chip_value());
						print("Numbers: ", true);
						for (auto num : *iter->get()->get_selection())
						{
							print(num);
							print(" ");
						}
						print();
					} // if debug

					m_bankroll += iter->get()->get_chip_value();
					m_current_bet -= iter->get()->get_chip_value();
					m_bets.erase(iter);

					// if bet is removed, the size of container also changes to -1
					--current;
				} // if match
			}
			// wether size changed or not move iter to next element not yet processed
			iter = m_bets.begin() + current;
		} // for
		if (m_bets.size())
		{
			m_last_bet = m_bets.back()->get_chip_value();
		}
		else // last chip from the table has been removed
		{
			m_last_bet = 0;
		}

		if (m_debug)
			print();
	}

#ifdef _MSC_VER
#pragma endregion methods
#endif // _MSC_VER

} // namespace roulette
