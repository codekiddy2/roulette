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
		mp_table(p_table),
		mp_history(p_history)
	{

		mp_table->signal_bet.connect(sigc::mem_fun(*this, &Engine::place_bet));
	}

#ifdef _MSC_VER
#pragma endregion begin

#pragma region
#endif // _MSC_VER

	void Engine::spin(const ETable table_type)
	{
		typedef boost::random::uniform_smallint<> type_dist;

		string red_output, black_output, green_output;
		string single_space = " ", triple_space = "   ", newline = "\n", tab = "\t";

		switch (table_type)
		{
		case ETable::NoZero:
			break;
		case ETable::European:
		{
			static type_dist dist(0, static_cast<int>(EuropeanWheel.size()));
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
			break;
		}
	}

#ifdef _MSC_VER
#pragma endregion methods
#endif // _MSC_VER

} // namespace roulette
