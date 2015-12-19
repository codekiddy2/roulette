
#ifndef BET_HH
#define BET_HH 1

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
// bet.hh
//
//	Bet class is used to set, calculate and print bet properties
//	or to place a bet on the table (Table class)
//
// TODO: add description
//
///</summary>

#include "error.hh"
#include "sets.hh"

#include <iostream>
#include <vector>	// due to and Childs_t
#include <memory>

#include <gdkmm/types.h> // Gdk::Point
#include <gdkmm/pixbuf.h>
#include <glibmm/refptr.h>

namespace roulette
{
	//typedef std::vector<unsigned> type_selection; // numbers selected for the bet (ALSO DEFINED AS type_set !)

	class Bet final
	{
	public:
		// constructors
		//Bet(const ETable table,
		//	const EBet bet,
		//	unsigned chip_info,
		//	Gdk::Point& point,
		//	std::shared_ptr<type_selection> selection = nullptr,
		//	Bet* parent = nullptr
		//	);

		Bet(/*const*/ EBet bet,
			/*const*/ EChip chip,
			type_set selection = nullptr
			);

		Bet(Bet&& ref);
		Bet(const Bet& ref);
		Bet& operator=(Bet&& ref);
		Bet& operator=(const Bet& ref);

		inline EBet get_id() const;
		inline unsigned get_chips() const; // amount of chips
		inline type_set get_selection() const; // numbers included in this bet

	private:
		// new constructor
		EBet m_bet;
		unsigned m_chip;
		type_set mp_set;

#if 0
		// methods
		EBet get_id() const; // ID
		unsigned get_childs() const; // amount of childs
		unsigned get_numbers() const; // amount of numbers
		type_selection get_selection() const;
		unsigned get_number(const unsigned& index) const; // reference number
		
		void set_points(Gdk::Point& point);
		Gdk::Point get_points() const;

		EBet get_child_id(const unsigned& child) const; // ID of a child 
		unsigned get_child_chip_count(const unsigned& child) const; // amount of chips of a child
		unsigned get_child_number_count(const unsigned& child) const; // amount of numbers of a child
		unsigned get_child_number(const unsigned& child, const unsigned& index) const; // reference number of a child

		void print_properties(const bool& childs = false) const;

	private:
		// typedefs
		typedef std::vector<std::shared_ptr<Bet>> Childs_t; // each bet has at least 1 child, so this is a "bet container"

		/// begin initilizer list
		EBet mId;
		const Bet* mpParent;
		std::shared_ptr<Childs_t> mpChilds;
#endif

#if 0

		std::shared_ptr<type_selection> mpSelection;
		const char* mpName;
		signed mCoverage;
		unsigned mChips;
		float mReturn;
		float mPayout;
		float mWin;
		float mResult;
		float mLose;
		float mOdds;
		float mProbWin;
		float mProbPush;
		float mProbLose;
		float mExpectedValue;
		float mExpectedReturn;
		float mAverageWin;
		short mFirstMoment;
		short mSecondMoment;
		int mThirdMoment;
		int mFourthMoment;
		float mSkewness;
		float mKurtosis;
		float mVariance;
		float mBinomialVariance;
		float mStandardDeviation;
		float mBinomialStandardDeviation;
		Gdk::Point m_point;
		/// end initilizer list
		
		// methods
		void assign_name();
		void set_part_1(const unsigned& chips);
		void set_part_2(const ETable& table, const unsigned& nums, const unsigned& chips);
		void fill_childs(const ETable& table, const std::shared_ptr<type_selection> selection, const int& chips, Gdk::Point point);
#endif
	};
	EBet Bet::get_id() const
	{
		return m_bet;
	}

	unsigned Bet::get_chips() const
	{
		return m_chip;
	}

	type_set Bet::get_selection() const
	{
		return mp_set;
	}

#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER
#if 0
	inline EBet Bet::get_id() const
	{
		return mId;
	}

	inline void Bet::set_points(Gdk::Point& point)
	{
		m_point = point;
	}

	inline Gdk::Point Bet::get_points() const
	{
		return m_point;
	}

	inline EBet Bet::get_child_id(const unsigned& child) const
	{
		if (mpChilds)
		{
			return mpChilds->at(child)->mId;
		}
		else
		{
			std::cout << "WARNING: get_child_id() -> child does not exist, returning 'UNDEFINED' id " << std::endl;
			return EBet::UNDEFINED;
		}
	}


	inline type_selection Bet::get_selection() const
	{
		if (mpSelection)
		{
			return *mpSelection;
		}
		else
		{
			std::cout << "WARNING: get_selection() -> pointer is null, returning empty type_selection " << std::endl;

			return type_selection();
		}
	}

	inline unsigned Bet::get_childs() const
	{
		if (mpChilds)
		{
			return static_cast<unsigned>(mpChilds->size());
		}
		else
		{
			return 0;
		}
	}

	inline unsigned Bet::get_numbers() const
	{
		if (mpSelection)
		{
			return static_cast<unsigned>(mpSelection->size());
		}
		else
		{
			return 0;
		}
	}

	inline unsigned Bet::get_number(const unsigned& index) const
	{
		if (mpSelection)
		{
			return *mpSelection->find(index);
		}
		else
		{
			std::cout << "WARNING: get_number() -> no number at: " << index << std::endl;
			return 0;
		}
	}

	inline unsigned Bet::get_child_chip_count(const unsigned& child) const
	{
		if (mpChilds)
		{
			return mpChilds->at(child)->mChips;
		}
		else
		{
			return 0;
		}
	}

	inline unsigned Bet::get_child_number_count(const unsigned& child) const
	{
		if (mpChilds)
		{
			if (mpChilds->at(child))
			{
				if (mpChilds->at(child)->mpSelection)
				{
					return static_cast<unsigned>(mpChilds->at(child)->mpSelection->size());
				}
			}
		}
		else
		{
			return 0;
		}
	}

	inline unsigned Bet::get_child_number(const unsigned& child, const unsigned& index) const
	{
		if (mpChilds)
		{
			if (mpChilds->at(child))
			{
				if (mpChilds->at(child)->mpSelection)
				{
					return *mpChilds->at(child)->mpSelection->find(index);
				}
			}
		}
		else
		{
			return 0;
		}
	}
#ifdef _MSC_VER
#pragma endregion inlines
#endif // _MSC_VER

#endif
} // namespace roulette

///<summary>
//
//	Construction order
//
//
//BetID			(bet identifier)
//CheckMemory		(check if numbers container is created by constructor)
//ptrParent		(pointer to parent bet/container)
//ptrLayouts		(supported tables)
//ptrMembers		(ptr to members class)
//ptrChilds		(nullptr means bet is SubBet)
//ptrNumbers		(first number is 0 or 1 (1 = next are real numbers, 0 = next are random numbers))
//
//Name			(name of a bet)
//
//FILL SUBBETS
//SET NUMBERS
//
//Coverage		(numbers covered)
//Minimum			(minimum chips allowed)
//Maximum			(maximum chips allowed)
//Chips			(chips placed / chips lost in 1 spin)
//Return			(cips returned if win)
//Payout			(payout factor)
//Win				(chips paid if win)	NEEDS RESULT FOR CONTAINER BET
//Result			(chips paid assuming wining all in a row)
//Lose			(chips lost assuming loosing all in a row)
//Odds			(odds against wining)
//ProbWin
//ProbPush
//ProbLose
//ExpectedReturn	(expected return in one spin)
//ExpectedValue	(player edge)
//AverageWin		(ratio of win and lose per 1 spin)
//
//FirstMoment
//SecondMoment
//ThirdMoment
//FourthMoment
//
//Skewness;
//Kurtosis;
//BinomialVariance;
//BinomStandardDeviation;
//Variance;
//StandardDeviation;
//
//
///</summary>

#endif // BET_HH
