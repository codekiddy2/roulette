
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
//	TODO: add description
//
///</summary>

#include "bet.hh"
#include "error.hh"

#include <iostream>
#include <vector>
#include <memory>
#include <boost/random/random_device.hpp>

namespace roulette
{

#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER

	class History;
	class Table;

	class Engine final :
		public IErrorHandler
	{
	public:
		// constructors
		Engine(Table* p_table, History* p_history/*, InfoBar* p_infobar*/);

		// methods
		void spin(const ETable table_type);
		inline unsigned get_bet() const;
		inline unsigned get_bankroll() const;
		inline unsigned get_last_bet() const;
		inline type_set get_numbers() const;
		inline void place_bet(std::shared_ptr<Bet> bet);

	private:
		// members
		std::vector<std::shared_ptr<Bet>> m_bets;
		static boost::random::random_device m_rng;

		/// begin initializer list
		Table* mp_table;
		History* mp_history;
		unsigned m_current_bet = 0;
		unsigned m_last_bet = 0;
		unsigned m_bankroll = 2000;
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
		return m_bets.back()->get_selection();
	}

#ifdef _MSC_VER
#pragma endregion inlines
#endif // _MSC_VER

} // namespace roulette

#endif // !ENGINE_HH
