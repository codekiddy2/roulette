
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

#include <vector>		// due to Selection_t and Childs_t

#include "error.hh"
#include "sets.hh"

namespace roulette
{
	typedef unsigned short Ushort_t;	// size type of a vector
	typedef std::vector<short> Selection_t; // numbers selected for the bet


	class Bet final
	{
	public:
		Bet(const ETable table,
			const EBet bet,
			const float chips,
			Selection_t* selection = nullptr,
			Bet* parent = nullptr);

		~Bet();
		Bet(Bet&& ref);
		Bet(const Bet& ref);
		Bet& operator=(Bet&& ref);

		EBet Id() const; // ID
		float Chips() const; // amount of chips
		Ushort_t Childs() const; // amount of childs
		Ushort_t Numbers() const; // amount of numbers
		Selection_t GetSelection() const;
		short Number(const short& index) const; // reference number

		EBet ChildId(const short& child) const; // ID of a child 
		float ChildChips(const short& child) const; // amount of chips of a child
		Ushort_t ChildNumbers(const short& child) const; // amount of numbers of a child
		short ChildNumber(const short& child, const short& index) const; // reference number of a child

		void PrintProperties(const bool& childs = false) const;

	private:
		typedef std::vector<Bet> Childs_t;			// each bet has at least 1 child

		EBet mId;
		const Bet* mpParent;
		Childs_t* mpChilds;
		Selection_t* mpSelection;
		const char* mpName;
		short mCoverage;
		float mChips;
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

		void AssignName();
		void SetPart1(const float& chips);
		Bet& operator=(const Bet& ref);
		void SetPart2(const ETable& table, const short& nums, const float& chips);
		void FillChilds(const ETable& table, const Selection_t* const selection, const float& chips);
	};

#pragma region Inline

	inline EBet Bet::Id() const
	{
		return mId;
	}

	inline EBet Bet::ChildId(const short& child) const
	{
		return mpChilds->at(child).mId;
	}

	inline float Bet::Chips() const
	{
		return mChips;
	}

	inline Selection_t Bet::GetSelection() const
	{
		return *mpSelection;
	}

	inline Ushort_t Bet::Childs() const
	{
		return static_cast<Ushort_t>(mpChilds->size());
	}

	inline Ushort_t Bet::Numbers() const
	{
		return static_cast<Ushort_t>(mpSelection->size());
	}

	inline short Bet::Number(const short& index) const
	{
		return mpSelection->at(index);
	}

	inline float Bet::ChildChips(const short& child) const
	{
		return mpChilds->at(child).mChips;
	}

	inline Ushort_t Bet::ChildNumbers(const short& child) const
	{
		return static_cast<Ushort_t>(mpChilds->at(child).mpSelection->size());
	}

	inline short Bet::ChildNumber(const short& child, const short& index) const
	{
		return mpChilds->at(child).mpSelection->at(index);
	}

#pragma endregion Inline methods
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
