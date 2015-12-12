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

#include "pch.hh"
#include "engine.hh"

#include "history.hh" // forward declared class

boost::random::random_device Engine::rng;

Engine::Engine(History* history) :
	pHistory(history)
{

}

void Engine::spin(const ETable table_type) const
{
	using std::string;
	using std::to_string;

	typedef boost::random::uniform_smallint<> dist_t;

	// TODO: temporary using underscore to avoid C4459,
	// red/black declared in sets.hh as 'Red' and 'Black'
	string red_, black_, green_, newline = "\n", tab = "\t";

	switch (table_type)
	{
	case ETable::NoZero:
		break;
	case ETable::European:
	{
		static dist_t dist(0, static_cast<int>(EuropeanWheel.size()));
		int result = dist(Engine::rng);

		if (result == 0)
		{
			green_.append(to_string(result) + tab);
		}
		else if (is_red(result))
		{
			red_.append(to_string(result) + tab);
		}
		else // black result :)
		{
			black_.append(to_string(result) + tab);
		}

		green_.append(newline);
		green_.append(pHistory->refGreenBuffer->get_text());

		red_.append(newline);
		red_.append(pHistory->refRedBuffer->get_text());

		black_.append(newline);
		black_.append(pHistory->refBlackBuffer->get_text());

		pHistory->refGreenBuffer->set_text(green_);
		pHistory->refRedBuffer->set_text(red_);
		pHistory->refBlackBuffer->set_text(black_);

		pHistory->apply_tags();
		break;
	}
	case ETable::American:
	case ETable::French:
	case ETable::SingleImprisonment:
	case ETable::DoubleImprisonment:
	case ETable::TripleImprisonment:
	case ETable::InfininiteImprisonment:
		break;
	default:
		break;
	}
}