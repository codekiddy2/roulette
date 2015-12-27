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
//	bet.cc
//
//	Definition of Bet class
//
// TODO: make print_properties print into a widget
//	TODO: add description
//
///</summary>

#include "pch.hh"
#include "sets.hh"
#include "chip.hh"
#include "bet.hh"

#include <cmath>		// due to set_part_2
#include <iostream>		// due to PrintProperties
#include <algorithm>	// due to sort in set_part_1

//#include <boost/uuid/uuid_generators.hpp>

namespace roulette
{

#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER

	using std::make_shared;
	using std::move;
	using std::to_string;
	using std::get;

	// TODO selection as array
	//Bet::Bet(const ETable table, const EBet bet, unsigned chip_info, Gdk::Point& point,
	//	std::shared_ptr<type_selection> selection, Bet* parent) :
	//	mId(bet),
	//	mpParent(parent),
	//	mpChilds(nullptr),
	//	mpSelection(selection),
	//	mpName(nullptr),
	//	mCoverage(1),
	//	mChips(static_cast<unsigned>(chip_info)),
	//	mReturn(0.f),
	//	mPayout(0.f),
	//	mWin(0.f),
	//	mResult(0.f),
	//	mLose(0.f),
	//	mOdds(0.f),
	//	mProbWin(0.f),
	//	mProbPush(0.f),
	//	mProbLose(0.f),
	//	mExpectedValue(0.f),
	//	mExpectedReturn(0.f),
	//	mAverageWin(0.f),
	//	mFirstMoment(0),
	//	mSecondMoment(0),
	//	mThirdMoment(0),
	//	mFourthMoment(0),
	//	mSkewness(0.f),
	//	mKurtosis(0.f),
	//	mVariance(0.f),
	//	mBinomialVariance(0.f),
	//	mStandardDeviation(0.f),
	//	mBinomialStandardDeviation(0.f),
	//	m_point(point)
	//{
	//	assign_name();

	//	if (parent)
	//		set_part_1(mChips);
	//	else
	//	{
	//		mpChilds = make_shared<Childs_t>();
	//		mpSelection = make_shared<type_selection>();
	//		fill_childs(table, selection, mChips, m_point);
	//		unsigned nums = table > ETable::American ? 37 : static_cast<unsigned>(table);

	//		for (unsigned i = 0; i < mpChilds->size(); ++i)
	//			mpChilds->at(i)->set_part_2(table, nums, mChips);

	//		set_part_1(mChips);
	//		set_part_2(table, nums, mChips);
	//	}
	//}

	Bet::Bet(/*const*/ type_chip chip, type_set selection) :
		IErrorHandler("Bet"),
		m_chip(chip),
		mp_set(selection),
		mCoverage(1),
		mReturn(0.f),
		mPayout(0.f),
		mWin(0.f),
		mResult(0.f),
		mLose(0.f),
		mOdds(0.f),
		mProbWin(0.f),
		mProbPush(0.f),
		mProbLose(0.f),
		mExpectedValue(0.f),
		mExpectedReturn(0.f),
		mAverageWin(0.f),
		mFirstMoment(0),
		mSecondMoment(0),
		mThirdMoment(0),
		mFourthMoment(0),
		mSkewness(0.f),
		mKurtosis(0.f),
		mVariance(0.f),
		mBinomialVariance(0.f),
		mStandardDeviation(0.f),
		mBinomialStandardDeviation(0.f)
	{
		assign_name();
	}

	Bet::Bet(Bet&& ref) :
		IErrorHandler("Bet"),
		m_chip(ref.m_chip),
		mp_set(std::move(ref.mp_set))
	{
	}

	Bet::Bet(const Bet& ref) :
		IErrorHandler("Bet"),
		m_chip(ref.m_chip),
		mp_set(ref.mp_set)
	{
	}

	Bet& Bet::operator=(Bet&& ref)
	{
		if (this != &ref)
		{
			m_chip = ref.m_chip;
			mp_set = ref.mp_set;
		}
		return *this;
	}

	Bet& Bet::operator=(const Bet& ref)
	{
		if (this != &ref)
		{
			m_chip = ref.m_chip;
			mp_set = ref.mp_set;
		}
		return *this;
	}

	void Bet::assign_name()
	{
		switch (get<2>(*m_chip))
		{
		case EBet::StraightUp:
			m_name = "Straight up";
			break;
		case EBet::Split:
			m_name = "Split";
			break;
		case EBet::Street:
			m_name = "Street";
			break;
		case EBet::Corner:
			m_name = "Corner";
			break;
		case EBet::Basket:
			m_name = "Basket";
			break;
		case EBet::Line:
			m_name = "Line";
			break;
		case EBet::Column1:
			m_name = "Column1";
			break;
		case EBet::Column2:
			m_name = "Column2";
			break;
		case EBet::Column3:
			m_name = "Column3";
			break;
		case EBet::Dozen1:
			m_name = "Dozen1";
			break;
		case EBet::Dozen2:
			m_name = "Dozen2";
			break;
		case EBet::Dozen3:
			m_name = "Dozen3";
			break;
		case EBet::High:
			m_name = "High";
			break;
		case EBet::Low:
			m_name = "Low";
			break;
		case EBet::Red:
			m_name = "Red";
			break;
		case EBet::Black:
			m_name = "Black";
			break;
		case EBet::Even:
			m_name = "Even";
			break;
		case EBet::Odd:
			m_name = "Odd";
			break;
		case EBet::VoisinsDeZero:
			m_name = "Voisins de zero";
			break;
		case EBet::TriesDuCylindre:
			m_name = "Tries du cylindre";
			break;
		case EBet::OrphelinsEnPlen:
			m_name = "Orphelins en plen";
			break;
		case EBet::OrphelinsACheval:
			m_name = "Orphelins a Cheval";
			break;
		case EBet::Jeu0:
			m_name = "Jeu 0";
			break;
		case EBet::Jeu79:
			m_name = "Jeu 7/9";
			break;
		case EBet::RedSplits:
			m_name = "Red splits";
			break;
		case EBet::BlackSplits:
			m_name = "Black Splits";
			break;
		case EBet::Snake:
			m_name = "Snake";
			break;
		case EBet::Neighbor1:
			m_name = "Neighbor 1";
			break;
		case EBet::Neighbor2:
			m_name = "Neighbor 2";
			break;
		case EBet::Neighbor3:
			m_name = "Neighbor 3";
			break;
		case EBet::Neighbor4:
			m_name = "Neighbor 4";
			break;
		case EBet::Neighbor5:
			m_name = "Neighbor 5";
			break;
		case EBet::FinalesEnPlen0:
			m_name = "Finales en plen 0";
			break;
		case EBet::FinalesEnPlen1:
			m_name = "Finales en plen 1";
			break;
		case EBet::FinalesEnPlen2:
			m_name = "Finales en plen 2";
			break;
		case EBet::FinalesEnPlen3:
			m_name = "Finales en plen 3";
			break;
		case EBet::FinalesEnPlen4:
			m_name = "Finales en plen 4";
			break;
		case EBet::FinalesEnPlen5:
			m_name = "Finales en plen 5";
			break;
		case EBet::FinalesEnPlen6:
			m_name = "Finales en plen 6";
			break;
		case EBet::FinalesEnPlen7:
			m_name = "Finales en plen 7";
			break;
		case EBet::FinalesEnPlen8:
			m_name = "Finales en plen 8";
			break;
		case EBet::FinalesEnPlen9:
			m_name = "Finales en plen 9";
			break;
		case EBet::FinalesACheval01:
			m_name = "Finales a cheval 0/1";
			break;
		case EBet::FinalesACheval12:
			m_name = "Finales a cheval 1/2";
			break;
		case EBet::FinalesACheval23:
			m_name = "Finales a cheval 2/3";
			break;
		case EBet::FinalesACheval34:
			m_name = "Finales a cheval 3/4";
			break;
		case EBet::FinalesACheval45:
			m_name = "Finales a cheval 4/5";
			break;
		case EBet::FinalesACheval56:
			m_name = "Finales a cheval 5/6";
			break;
		case EBet::FinalesACheval67:
			m_name = "Finales a cheval 6/7";
			break;
		case EBet::FinalesACheval78:
			m_name = "Finales a cheval 7/8";
			break;
		case EBet::FinalesACheval89:
			m_name = "Finales a cheval 8/9";
			break;
		case EBet::FinalesACheval910:
			m_name = "Finales a cheval 9/10";
			break;
		case EBet::FinalesACheval03:
			m_name = "Finales a cheval 0/3";
			break;
		case EBet::FinalesACheval14:
			m_name = "Finales a cheval 1/4";
			break;
		case EBet::FinalesACheval25:
			m_name = "Finales a cheval 2/5";
			break;
		case EBet::FinalesACheval36:
			m_name = "Finales a cheval 3/6";
			break;
		case EBet::FinalesACheval47:
			m_name = "Finales a cheval 4/7";
			break;
		case EBet::FinalesACheval58:
			m_name = "Finales a cheval 5/8";
			break;
		case EBet::FinalesACheval69:
			m_name = "Finales a cheval 6/9";
			break;
		case EBet::FinalesACheval710:
			m_name = "Finales a cheval 7/10";
			break;
		case EBet::FinalesACheval811:
			m_name = "Finales a cheval 8/11";
			break;
		case EBet::FinalesACheval912:
			m_name = "Finales a cheval 9/12";
			break;
		case EBet::Maximus0:
			m_name = "Maximus 0";
			break;
		case EBet::Maximus00:
			m_name = "Maximus 00";
			break;
		case EBet::Maximus13:
			m_name = "Maximus 1/3";
			break;
		case EBet::Maximus2:
			m_name = "Maximus 2";
			break;
		case EBet::Maximus35:
			m_name = "Maximus 35";
			break;
		case EBet::Maximus3436:
			m_name = "Maximus 34, 36";
			break;
		case EBet::MaximusColumn2:
			m_name = "Maximus column 2";
			break;
		case EBet::MaximusColumn13:
			m_name = "Maximus column 13";
			break;
		default:
			error_handler(error("Bet -> assign_name -> Name not found"));
		}
	}

#if 0
	Bet::Bet(const Bet& ref) :
		mId(ref.mId),
		mpParent(ref.mpParent),
		mpChilds(nullptr), // 1a.
		mpSelection(nullptr), // 2a.
		mpName(ref.mpName),
		mCoverage(ref.mCoverage),
		mChips(ref.mChips),
		mReturn(ref.mReturn),
		mPayout(ref.mPayout),
		mWin(ref.mWin),
		mResult(ref.mResult),
		mLose(ref.mLose),
		mOdds(ref.mOdds),
		mProbWin(ref.mProbWin),
		mProbPush(ref.mProbPush),
		mProbLose(ref.mProbLose),
		mExpectedValue(ref.mExpectedValue),
		mExpectedReturn(ref.mExpectedReturn),
		mAverageWin(ref.mAverageWin),
		mFirstMoment(ref.mFirstMoment),
		mSecondMoment(ref.mSecondMoment),
		mThirdMoment(ref.mThirdMoment),
		mFourthMoment(ref.mFourthMoment),
		mSkewness(ref.mSkewness),
		mKurtosis(ref.mKurtosis),
		mVariance(ref.mVariance),
		mBinomialVariance(ref.mBinomialVariance),
		mStandardDeviation(ref.mStandardDeviation),
		mBinomialStandardDeviation(ref.mBinomialStandardDeviation),
		m_point(ref.m_point)
	{
		if (ref.mpChilds)
		{
			mpChilds = make_shared<Childs_t>(*ref.mpChilds); // 1b.
		}
		if (ref.mpSelection)
		{
			mpSelection = make_shared<type_selection>(*ref.mpSelection); // 2b.
		}
	}

	Bet::Bet(Bet&& ref) :
		mId(ref.mId),
		mpParent(ref.mpParent),
		mpChilds(move(ref.mpChilds)),
		mpSelection(move(ref.mpSelection)),
		mpName(ref.mpName),
		mCoverage(ref.mCoverage),
		mChips(ref.mChips),
		mReturn(ref.mReturn),
		mPayout(ref.mPayout),
		mWin(ref.mWin),
		mResult(ref.mResult),
		mLose(ref.mLose),
		mOdds(ref.mOdds),
		mProbWin(ref.mProbWin),
		mProbPush(ref.mProbPush),
		mProbLose(ref.mProbLose),
		mExpectedValue(ref.mExpectedValue),
		mExpectedReturn(ref.mExpectedReturn),
		mAverageWin(ref.mAverageWin),
		mFirstMoment(ref.mFirstMoment),
		mSecondMoment(ref.mSecondMoment),
		mThirdMoment(ref.mThirdMoment),
		mFourthMoment(ref.mFourthMoment),
		mSkewness(ref.mSkewness),
		mKurtosis(ref.mKurtosis),
		mVariance(ref.mVariance),
		mBinomialVariance(ref.mBinomialVariance),
		mStandardDeviation(ref.mStandardDeviation),
		mBinomialStandardDeviation(ref.mBinomialStandardDeviation),
		m_point(ref.m_point)
	{
		//ref.mpChilds = nullptr;
		//ref.mpSelection = nullptr;
	}

	Bet& Bet::operator=(Bet&& ref)
	{
		if (this != &ref)
		{
			mId = ref.mId;
			mpParent = ref.mpParent;
			//delete mpChilds; // 1.
			mpChilds = std::move(ref.mpChilds);
			//ref.mpChilds = nullptr;
			//delete mpSelection; // 2.
			mpSelection = std::move(ref.mpSelection);
			//ref.mpSelection = nullptr;
			m_name = ref.mpName;
			mCoverage = ref.mCoverage;
			mChips = ref.mChips;
			mReturn = ref.mReturn;
			mPayout = ref.mPayout;
			mWin = ref.mWin;
			mResult = ref.mResult;
			mLose = ref.mLose;
			mOdds = ref.mOdds;
			mProbWin = ref.mProbWin;
			mProbPush = ref.mProbPush;
			mProbLose = ref.mProbLose;
			mExpectedValue = ref.mExpectedValue;
			mExpectedReturn = ref.mExpectedReturn;
			mAverageWin = ref.mAverageWin;
			mFirstMoment = ref.mFirstMoment;
			mSecondMoment = ref.mSecondMoment;
			mThirdMoment = ref.mThirdMoment;
			mFourthMoment = ref.mFourthMoment;
			mSkewness = ref.mSkewness;
			mKurtosis = ref.mKurtosis;
			mVariance = ref.mVariance;
			mBinomialVariance = ref.mBinomialVariance;
			mStandardDeviation = ref.mStandardDeviation;
			mBinomialStandardDeviation = ref.mBinomialStandardDeviation;
			m_point = ref.m_point;
		}
		return *this;
	}

	Bet& Bet::operator=(const Bet& ref)
	{
		if (this != &ref)
		{
			mId = ref.mId;
			mpParent = ref.mpParent;
			//delete mpChilds; // 1.
			mpChilds = make_shared<Childs_t>(*ref.mpChilds);
			//delete mpSelection; // 2.
			mpSelection = make_shared<type_selection>(*ref.mpSelection);
			m_name = ref.mpName;
			mCoverage = ref.mCoverage;
			mChips = ref.mChips;
			mReturn = ref.mReturn;
			mPayout = ref.mPayout;
			mWin = ref.mWin;
			mResult = ref.mResult;
			mLose = ref.mLose;
			mOdds = ref.mOdds;
			mProbWin = ref.mProbWin;
			mProbPush = ref.mProbPush;
			mProbLose = ref.mProbLose;
			mExpectedValue = ref.mExpectedValue;
			mExpectedReturn = ref.mExpectedReturn;
			mAverageWin = ref.mAverageWin;
			mFirstMoment = ref.mFirstMoment;
			mSecondMoment = ref.mSecondMoment;
			mThirdMoment = ref.mThirdMoment;
			mFourthMoment = ref.mFourthMoment;
			mSkewness = ref.mSkewness;
			mKurtosis = ref.mKurtosis;
			mVariance = ref.mVariance;
			mBinomialVariance = ref.mBinomialVariance;
			mStandardDeviation = ref.mStandardDeviation;
			mBinomialStandardDeviation = ref.mBinomialStandardDeviation;
			m_point = ref.m_point;
		}
		return *this;
	}
#endif
#ifdef _MSC_VER
#pragma endregion contructors

#pragma region
#endif // _MSC_VER
#if 0
	// TODO implement map of strings with names 
	void Bet::fill_childs(
		const ETable& table, const std::shared_ptr<type_selection> selection, const int& chips, Gdk::Point point)
	{
#if 0
		short temp[6];
#endif
		switch (mId)
		{
		case EBet::StraightUp:	// TODO these bets do not need a child
		case EBet::Split:
		case EBet::Street:
		case EBet::Corner:
			break;
		case EBet::Line:
			mpChilds->push_back(make_shared<Bet>(table, mId, chips, point, make_shared<type_selection>(*selection), this));
			break;
		case EBet::Basket:
			mpChilds->push_back(make_shared<Bet>(table, mId, chips, point, make_shared<type_selection>(Basket), this));
			break;
		case EBet::Column1:
			mpChilds->push_back(make_shared<Bet>(table, mId, chips, point, make_shared<type_selection>(Column1), this));
			break;
		case EBet::Column2:
			mpChilds->push_back(make_shared<Bet>(table, mId, chips, point, make_shared<type_selection>(Column2), this));
			break;
		case EBet::Column3:
			mpChilds->push_back(make_shared<Bet>(table, mId, chips, point, make_shared<type_selection>(Column3), this));
			break;
		case EBet::Dozen1:
			mpChilds->push_back(make_shared<Bet>(table, mId, chips, point, make_shared<type_selection>(Dozen1), this));
			break;
		case EBet::Dozen2:
			mpChilds->push_back(make_shared<Bet>(table, mId, chips, point, make_shared<type_selection>(Dozen2), this));
			break;
		case EBet::Dozen3:
			mpChilds->push_back(make_shared<Bet>(table, mId, chips, point, make_shared<type_selection>(Dozen3), this));
			break;
		case EBet::High:
			mpChilds->push_back(make_shared<Bet>(table, mId, chips, point, make_shared<type_selection>(High), this));
			break;
		case EBet::Low:
			mpChilds->push_back(make_shared<Bet>(table, mId, chips, point, make_shared<type_selection>(Low), this));
			break;
		case EBet::Red:
			mpChilds->push_back(make_shared<Bet>(table, mId, chips, point, make_shared<type_selection>(Red), this));
			break;
		case EBet::Black:
			mpChilds->push_back(make_shared<Bet>(table, mId, chips, point, make_shared<type_selection>(Black), this));
			break;
		case EBet::Even:
			mpChilds->push_back(make_shared<Bet>(table, mId, chips, point, make_shared<type_selection>(Even), this));
			break;
		case EBet::Odd:
			mpChilds->push_back(make_shared<Bet>(table, mId, chips, point, make_shared<type_selection>(Odd), this));
			break;

#if 0 // TODO: fix code
		case EBet::VoisinsDeZero:
			for (unsigned i = 0; i < 10; i += 2)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(VoisinsDeZero.find(i), VoisinsDeZero.find(i + 2)), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::Street, chips, make_shared<type_selection>(VoisinsDeZero.find(10), VoisinsDeZero.find(13)), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::Corner, chips, make_shared<type_selection>(VoisinsDeZero.find(13), VoisinsDeZero.find(17)), this));
			break;
		case EBet::TriesDuCylindre:
			for (unsigned i = 0; i < 12; i += 2)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(TriesDuCylindre.find(i), TriesDuCylindre.find(i + 2)), this));
			break;
		case EBet::OrphelinsEnPlen:
			for (unsigned i = 0; i < 8; ++i)
				mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(OrphelinsEnPlen.find(1), OrphelinsEnPlen.find(i)), this));
			break;
		case EBet::OrphelinsACheval:
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(OrphelinsACheval.find(1), OrphelinsACheval.find(1)), this));
			for (unsigned i = 1; i < 8; i += 2)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(OrphelinsACheval.find(i), OrphelinsACheval.find(i + 2)), this));
			break;
		case EBet::Jeu0:
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(Jeu0.find(1), Jeu0.find(26)), this));
			for (unsigned i = 1; i < 6; i += 2)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(Jeu0.find(i), Jeu0.find(i + 2)), this));
			break;
		case EBet::Jeu79:
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(Jeu79.find(1), Jeu79.find(19)), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(Jeu79.find(1), Jeu79.find(27)), this));
			for (unsigned i = 2; i < 9; i += 2)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(Jeu79.find(i), Jeu79.find(i + 2)), this));
			break;
		case EBet::RedSplits:
			for (unsigned i = 0; i < 4; i += 2)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(RedSplits.begin(), RedSplits.find(i + 2)), this));
			break;
		case EBet::BlackSplits:
			for (unsigned i = 0; i < 14; i += 2)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(BlackSplits.begin(), BlackSplits.find(i + 2)), this));
			break;
		case EBet::Snake:
			for (unsigned i = 0; i < 12; ++i)
				mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(Snake.begin(), Snake.find(i)), this));
			break;
		case EBet::Neighbor1:
		case EBet::Neighbor2:
		case EBet::Neighbor3:
		case EBet::Neighbor4:
		case EBet::Neighbor5:
			for (short i = -(static_cast<short>(mId) - 4); i <= (static_cast<short>(mId) - 4); ++i)
				mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, get_neighbor(table, *selection->begin(), i)), this));
			break;
		case EBet::FinalesEnPlen0:
		case EBet::FinalesEnPlen1:
		case EBet::FinalesEnPlen2:
		case EBet::FinalesEnPlen3:
		case EBet::FinalesEnPlen4:
		case EBet::FinalesEnPlen5:
		case EBet::FinalesEnPlen6:
			for (short i = static_cast<short>(mId) - 64; i <= static_cast<short>(mId) - 34; i += 10)
				mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, i), this));
			break;
		case EBet::FinalesEnPlen7:
		case EBet::FinalesEnPlen8:
		case EBet::FinalesEnPlen9:
			for (short i = static_cast<short>(mId) - 64; i <= static_cast<short>(mId) - 44; i += 10)
				mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, i), this));
			break;
		case EBet::FinalesACheval01:
			for (temp[0] = 0, temp[1] = 1; temp[0] <= 20; temp[0] += 10, temp[1] += 10)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp, temp + 2), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 30), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 31), this));
			break;
		case EBet::FinalesACheval12:
			temp[0] = 31; temp[1] = 32;
			mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp, temp + 2), this));
			for (temp[0] = 1, temp[1] = 2; temp[0] <= 11; temp[0] += 10, temp[1] + 10)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp, temp + 2), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 21), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 22), this));
			break;
		case EBet::FinalesACheval23:
			temp[0] = 2; temp[1] = 3;
			mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp, temp + 2), this));
			for (temp[0] = 22, temp[1] = 23; temp[0] <= 32; temp[0] += 10, temp[1] + 10)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp, temp + 2), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 12), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 13), this));
			break;
		case EBet::FinalesACheval34:
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 3), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 4), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 33), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 34), this));
			for (temp[0] = 13, temp[1] = 14; temp[0] <= 23; temp[0] += 10, temp[1] + 10)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp, temp + 2), this));
			break;
		case EBet::FinalesACheval45:
			temp[0] = 34; temp[1] = 35;
			mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp, temp + 2), this));
			for (temp[0] = 4, temp[1] = 5; temp[0] <= 14; temp[0] += 10, temp[1] + 10)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp, temp + 2), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 24), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 25), this));
			break;
		case EBet::FinalesACheval56:
			temp[0] = 5; temp[1] = 6;
			mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp, temp + 2), this));
			for (temp[0] = 25, temp[1] = 26; temp[0] <= 35; temp[0] += 10, temp[1] += 10)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp, temp + 2), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 15), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 16), this));
			break;
		case EBet::FinalesACheval67:
			for (temp[0] = 16, temp[1] = 17; temp[0] <= 26; temp[0] += 10, temp[1] + 10)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp, temp + 2), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 6), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 7), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 36), this));
			break;
		case EBet::FinalesACheval78:
			for (temp[0] = 7, temp[1] = 8; temp[0] <= 17; temp[0] += 10, temp[1] + 10)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp, temp + 2), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 27), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 28), this));
			break;
		case EBet::FinalesACheval89:
			temp[0] = 8; temp[1] = 9;
			mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp, temp + 2), this));
			temp[0] = 28; temp[1] = 29;
			mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp, temp + 2), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 18), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 19), this));
			break;
		case EBet::FinalesACheval910:
			for (temp[0] = 19, temp[1] = 20; temp[0] <= 29; temp[0] += 10, temp[1] + 10)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp, temp + 2), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 9), this));
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(1, 10), this));
			break;

		case EBet::FinalesACheval03:
		case EBet::FinalesACheval14:
		case EBet::FinalesACheval25:
		case EBet::FinalesACheval36:
			for (temp[0] = static_cast<short>(mId) - 84, temp[1] = static_cast<short>(mId) - 81; temp[0] <= static_cast<short>(mId) - 54; temp[0] += 10, temp[1] += 10)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp, temp + 2), this));
			break;
		case EBet::FinalesACheval47:
		case EBet::FinalesACheval58:
		case EBet::FinalesACheval69:
		case EBet::FinalesACheval710:
		case EBet::FinalesACheval811:
		case EBet::FinalesACheval912:
			for (temp[0] = static_cast<short>(mId) - 84, temp[1] = static_cast<short>(mId) - 81; temp[0] <= static_cast<short>(mId) - 64; temp[0] += 10, temp[1] += 10)
				mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp, temp + 2), this));
			break;
		case EBet::Maximus00:
			//	TODO Solve maximus bets
			break;
		case EBet::Maximus0:
		{
			type_selection temp(1, 0); // 0
			mpChilds->push_back(make_shared<Bet>(table, EBet::StraightUp, chips, make_shared<type_selection>(temp), this));
			temp.push_back(1); // 0, 1
			mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp), this));
			temp.at(1) = 3; // 0, 3
			mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp), this));
			temp.at(1) = 2; // 0, 2
			mpChilds->push_back(make_shared<Bet>(table, EBet::Split, chips, make_shared<type_selection>(temp), this));
			temp.push_back(1); // 0, 2, 1
			mpChilds->push_back(make_shared<Bet>(table, EBet::Street, chips, make_shared<type_selection>(temp), this));
			temp.at(2) = 3; // 0, 2, 3
			mpChilds->push_back(make_shared<Bet>(table, EBet::Street, chips, make_shared<type_selection>(temp), this));
			switch (table)
			{
			case ETable::American:
				mpChilds->at(2)->mpSelection->at(1) = 37; // 0, 3 ---> 0, 37
				mpChilds->at(5)->mpSelection->at(2) = 37; // 0,2,3 ---> 0, 2, 37
				temp->push_back(1); // 0, 2, 3, 1
				temp->push_back(37);	// 0, 2, 3, 1, 37
				mpChilds->push_back(make_shared<Bet>(table, EBet::Basket, chips, make_shared<type_selection>(temp), this));
				break;
			case ETable::NoZero:
				break;
			default:
				temp.erase(temp.begin() + 4); // 0, 2, 3, 1
				mpChilds->push_back(Bet(table, EBet::Corner, chips, make_shared<type_selection>(temp), this));
				break;

			}
			break;

		}
#endif // 0
		case EBet::Maximus13:
			break;
		case EBet::Maximus2:
			break;
		case EBet::Maximus35:
			break;
		case EBet::Maximus3436:
			break;
		case EBet::MaximusColumn2:
			break;
		case EBet::MaximusColumn13:
			break;
		}
	}

	// TODO printProperties output migh be wrong
	void Bet::print_properties(const bool& childs) const
	{
		using std::cout;
		using std::endl;

		cout << endl << "BET PROPERTIES";
		if (mpParent)
			cout << " Childs_t bet" << endl;
		else
			cout << " Parent bet" << endl;
		cout << "*************************" << endl << endl;
		cout << "mpName			" << mpName << endl;
		cout << "mCoverage		" << mCoverage << endl;
		cout << "mChips			" << mChips << endl;
		cout << "mReturn			" << mReturn << endl;
		cout << "mPayout			" << mPayout << endl;
		cout << "mWin			" << mWin << endl;
		cout << "mProbWin			" << mProbWin << endl;
		cout << "mProbPush		" << mProbPush << endl;
		cout << "mProbLose		" << mProbLose << endl;
		cout << "mResult			" << mResult << endl;
		cout << "Expected value		" << mExpectedValue << endl;
		cout << "mOdds			" << mOdds << endl;
		cout << "Expected return		" << mExpectedReturn << endl;
		cout << "mLose			" << mLose << endl;
		cout << "Average win		" << mAverageWin << endl;
		cout << "1st moment		" << mFirstMoment << endl;
		cout << "2nd moment		" << mSecondMoment << endl;
		cout << "3rd moment		" << mThirdMoment << endl;
		cout << "4th moment		" << mFourthMoment << endl;
		cout << "Binomial variance	" << mBinomialVariance << endl;
		cout << "Binomial StdDev		" << mBinomialStandardDeviation << endl;
		cout << "mVariance		" << mVariance << endl;
		cout << "Stdandard deviation	" << mStandardDeviation << endl;
		cout << "mSkewness		" << mSkewness << endl;
		cout << "mKurtosis		" << mKurtosis << endl;
		cout << "----------------" << endl;
		cout << "Covered numbers:" << endl;

		if (mpChilds) // it is parent
			for (unsigned i = 0; i < mpChilds->size(); ++i)
			{
				cout << mpChilds->at(i)->mpName << ":" << endl;
				for (unsigned j = 0; j < mpChilds->at(i)->mpSelection->size(); ++j)
					cout << *mpChilds->at(i)->mpSelection->find(j) << endl;
			}

		else for (unsigned i = 0; i < mpSelection->size(); ++i)
			cout << *mpSelection->find(i) << endl;

		if (childs)	// print child properties
			for (unsigned i = 0; i < mpChilds->size(); ++i)
				mpChilds->at(i)->print_properties();
	}
	
	
	void Bet::set_part_1(const unsigned& chips)
	{
		using std::sort;

		 //TODO: THIS FUNCTION THROWS, fix it.
#if 0
		 //COVERAGE
		if (mpSelection->empty())  // it is parent
		{
			for (unsigned i = 0; i < mpChilds->size(); ++i)
				for (unsigned j = 0; j < mpChilds->at(i)->mpSelection->size(); ++j)
				{
					mpSelection->insert(*mpChilds->at(i)->mpSelection->find(j));
				}
			// TODO: no sorting with unordered_set!
			//sort(mpSelection->begin(), mpSelection->end());
		}

		if (mpSelection->size())
		{
			for (unsigned i = 0; i < mpSelection->size() - 1; ++i)
			{
				if (mpSelection->find(i) != mpSelection->find(i + 1))
					++mCoverage;
			}
		}
#endif

		// CHIPS
		if (mpChilds)  // it is parent
		{
			for (unsigned i = 0; i < mpChilds->size(); ++i)
				mChips += mpChilds->at(i)->mChips;

			// RETURN
			float SUMproduct = 0.f;
			unsigned SUMcoverage = 0;

			for (unsigned i = 0; i < mpChilds->size(); ++i)
			{
				SUMproduct += mpChilds->at(i)->mCoverage * mpChilds->at(i)->mReturn;
				SUMcoverage += mpChilds->at(i)->mCoverage;
			}
			mReturn = SUMproduct / SUMcoverage;

			// PAYOUT
			SUMproduct = 0.f;
			SUMcoverage = 0;
			for (unsigned i = 0; i < mpChilds->size(); ++i)
			{
				SUMproduct += mpChilds->at(i)->mCoverage * mpChilds->at(i)->mPayout;
				SUMcoverage += mpChilds->at(i)->mCoverage;
			}

			mPayout = SUMproduct / SUMcoverage;
			return;
		}

		// CHIPS
		switch (mpParent->mId)
		{
		case EBet::VoisinsDeZero:
			switch (mId)
			{
			case EBet::Street:
			case EBet::Corner:
				mChips = chips * 2;
				break;
			default:
				mChips = chips;
				break;
			}
			break;
		case EBet::Maximus00:
		case EBet::Maximus0:
		case EBet::Maximus13:
		case EBet::Maximus2:
		case EBet::Maximus35:
		case EBet::Maximus3436:
		case EBet::MaximusColumn2:
		case EBet::MaximusColumn13:
			mChips = mCoverage;
			break;
		default:
			mChips = chips;
		}

		// RETURN
		switch (mpParent->mId)
		{
		case EBet::OrphelinsACheval:
			if (mpSelection->size() != 1)
			{
				if ((*mpSelection->find(0) == 17) || (*mpSelection->find(1) == 17))
				{
					mReturn = mChips * 3.f / 2;
				}
				else
				{
					mReturn = static_cast<float>(mChips);
				}
			}
			else
			{
				mReturn = static_cast<float>(mChips);
			}
			break;
		case EBet::Jeu79:
			if (mpSelection->size() != 1)
				if ((*mpSelection->find(0) == 8) || (*mpSelection->find(1) == 8))
					mReturn = static_cast<float>(mChips) * 3.f / 2;
				else mReturn = static_cast<float>(mChips);
			else
				mReturn = static_cast<float>(mChips);
			break;
		case EBet::BlackSplits: // check numbes order and reduce logical check
			if ((*mpSelection->find(0) == 8) ||
				(*mpSelection->find(0) == 26) ||
				(*mpSelection->find(1) == 13) ||
				(*mpSelection->find(1) == 31))
			{
				mReturn = mChips * 3.f / 2;
			}
			else if (*mpSelection->find(0) != 17)
			{
				mReturn = mChips * 2.f;
			}
			else
			{
				mReturn = static_cast<float>(mChips);
			}
				break;
		case EBet::Maximus00:
		case EBet::Maximus0:
		case EBet::Maximus13:
		case EBet::Maximus2:
		case EBet::Maximus35:
		case EBet::Maximus3436:
		case EBet::MaximusColumn2:
		case EBet::MaximusColumn13:
			throw error("Bet -> set_part_1 -> Maximus return not defined");
			break;
		default:
			mReturn = static_cast<float>(mChips);
		}

		// PAYOUT
		mPayout = floor(36.f / mCoverage - 1);
	}
	
	void Bet::set_part_2(const ETable& table, const unsigned& nums, const unsigned& chips)
	{
		using std::floor;
		using std::pow;
		using std::sqrt;

		// WIN and RESULT
		if (!mpChilds) // it is child
		{
			float SUMchips = 0.f;

			for (unsigned i = 0; i < mpParent->mpChilds->size(); ++i)
				SUMchips += mpParent->mpChilds->at(i)->mChips;

			mWin = mPayout * mChips - (SUMchips - mChips);
			mResult = mCoverage * mWin;
		}
		else // it is parent
		{
			for (unsigned i = 0; i < mpChilds->size(); ++i)
				mResult += mpChilds->at(i)->mResult;

			mWin = mResult / mCoverage;
		}

		// LOSE
		mLose = static_cast<float>( mChips * (nums - mCoverage) );

		// ODDS
		mOdds = static_cast<float>(nums) / mCoverage - 1;

		// PROBABILITY TO WIN
		mProbWin = mCoverage / static_cast<float>(nums);

		// PROBABILITY TO PUSH
		if ((table >= ETable::French) && (mId <= EBet::Low) && (mId >= EBet::Red))
		{
			const float zero = 1.f / 37;
			switch (table)
			{
			case ETable::French:
				mProbPush = zero / 2;
				break;
			case ETable::SingleImprisonment:
				mProbPush = zero * mProbWin;
				break;
			case ETable::DoubleImprisonment:
				mProbPush = zero * mProbWin / (1 - zero * mProbWin);
				break;
			case ETable::TripleImprisonment:
				mProbPush = zero * (1 / (1 - (zero * mProbWin + (zero * zero * (1 / (1 - zero * mProbWin)) * mProbWin * mProbWin)))) * mProbWin;
				break;
			case ETable::InfininiteImprisonment:
				mProbPush = (1 - sqrt(1 - 4 * zero * mProbWin)) / 2;
			}
		}

		// PROBABILITY TO LOSE
		mProbLose = 1 - mProbWin - mProbPush;

		// EXPECTED RETURN AND VALUE
		if (mpChilds) // it is parent
		{
			for (unsigned i = 0; i < mpChilds->size(); ++i)
				mExpectedReturn += mpChilds->at(i)->mExpectedReturn;

			mExpectedValue = mExpectedReturn / mChips;
		}
		else
		{
			mExpectedReturn = mChips * mPayout * mProbWin - mChips * mProbLose;

			if ((mId <= EBet::Low) && (mId >= EBet::Red) && (table >= ETable::French))
				mExpectedValue = mProbWin - mProbLose;
			else
				mExpectedValue = mPayout * mProbWin - mProbLose;
		}

		// AVERAGE WIN
		mAverageWin = mWin / mChips;

		// MOMETS
		mFirstMoment = static_cast<short>(pow(nums - mCoverage, 1) * mCoverage + pow(-mCoverage, 1) * (nums - mCoverage));
		mSecondMoment = static_cast<short>(pow(nums - mCoverage, 2) * mCoverage + pow(-mCoverage, 2) * (nums - mCoverage));
		mThirdMoment = static_cast<int>(pow(nums - mCoverage, 3) * mCoverage + pow(-mCoverage, 3) * (nums - mCoverage));
		mFourthMoment = static_cast<int>(pow(nums - mCoverage, 4) * mCoverage + pow(-mCoverage, 4) * (nums - mCoverage));

		// SKEWNESS AND KURTISIS
		mSkewness = static_cast<float>(sqrt(nums) * mThirdMoment / pow(mSecondMoment, 3.f / 2));
		mKurtosis = static_cast<float>(nums * mFourthMoment / pow(mSecondMoment, 2));

		// VARIANCE AND STANDARD DEVIATION
		mBinomialVariance = pow(sqrt(mProbWin * mProbLose), 2);
		mBinomialStandardDeviation = sqrt(mProbWin * mProbLose);
		mVariance = pow(chips * (mPayout + mReturn) * sqrt(mProbWin * mProbLose), 2);
		mStandardDeviation = chips * (mPayout + mReturn) * sqrt(mProbWin * mProbLose);
	}
#endif
#ifdef _MSC_VER
#pragma endregion methods
#endif // _MSC_VER

} // namespace
