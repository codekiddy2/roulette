
#ifndef ENGINE_HH
#define ENGINE_HH 1

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
//	engine.hh
//
//	Declaration of Engine class
//
//	Engine class is used to spin numbers,
// store and place bets
//
// it also perform calculations of outcome and manages
// player bankrol odds and looses
//
///</summary>

// roulette
#include "bet.hh"
#include "error.hh"
#include "main.hh"

// gtkmm
#include <sigc++/signal.h>

// boost
#include <boost/random/random_device.hpp>

namespace roulette
{

#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER

	class Engine final :
		public IErrorHandler
	{
	public:
		// constructors
		Engine();

		// place a bet into the engine bet container
		void place_bet(type_bet bet);

		// spin a roulette wheel
		void spin(const ETable table_type);

		// remove all previously placed bets
		void clear_all_bets();

		// get total value of bets placed
		inline unsigned get_bet() const;

		// get current player bankroll
		inline unsigned get_bankroll() const;

		// get value of last bet placed
		inline unsigned get_last_bet() const;

		// get numbers on which the bet has been placed
		inline type_set get_numbers() const;

		// signal the spin
		sigc::signal1<void, int> signal_spin;

	private:
		// clear a single bet from the engine store
		void clear_bet(type_bet& bet);

		// members
		type_bet_container m_bets;
		static boost::random::random_device m_rng;

		/// begin initializer list
		unsigned m_current_bet;
		unsigned m_last_bet;
		unsigned m_bankroll;
		/// end initializer list

		// deleted
		Engine(const Engine&) = delete;
		Engine(const Engine&&) = delete;
		Engine& operator=(const Engine&) = delete;
		Engine& operator=(const Engine&&) = delete;
	};

#ifdef _MSC_VER
#pragma endregion begin

#pragma region
#endif // _MSC_VER

	unsigned Engine::get_bankroll() const
	{
		return m_bankroll;
	}

	unsigned Engine::get_bet() const
	{
		return m_current_bet;
	}

	unsigned Engine::get_last_bet() const
	{
		return m_last_bet;
	}

	type_set Engine::get_numbers() const
	{
		// if bets are cleared from the table return nullptr
		if (m_bets.empty())
		{
			return nullptr;
		}
		else
		{
			return m_bets.back()->get_selection();
		}
	}

#ifdef _MSC_VER
#pragma endregion inlines
#endif // _MSC_VER

} // namespace roulette

#endif // !ENGINE_HH
