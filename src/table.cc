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

///<summary
//
//	table.cc
//
//	Definition of Table constructor and table methods
//
//	TODO: add description
//	TODO: (OLD) forward declare enum class ans use short enumeration (not default int)
// TODO: make print_properties print into a widget
//
///</summary>

#include "pch.hh"
#include "chipset.hh"
#include "field.hh"
#include "table.hh"
#include "error.hh"

namespace roulette
{

#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER

	using std::cerr;
	using std::endl;
	using std::cout;
	using std::make_pair;
	using roulette::error;

	Table::Table(const ETable table_type) :
		mTableMax(0),
		mTableType(table_type),
		mTotalBets(0)
	{
		set_column_homogeneous(true);
		set_row_homogeneous(true);

#ifdef DEBUG_DND_LOG

		if (!Chipset::is_constructed())
		{
			cerr << "WARNING Chipset must be constructed before Table, DND will not work" << endl;
			cout << "-> Table::Table(const ETable table_type)" << endl;
		}
#endif // DEBUG_DND_LOG

		// create fields
		EField temp;
		for (size_t i = 0; i < static_cast<size_t>(EField::Dummy3); i++)
		{
			temp = static_cast<EField>(i);
			mFields.insert(make_pair(temp, new Field(temp, this)));
		}
		// TODO: check if any signals are connected more than once,
		//ex: debug output how many time handlers get called per chip placed (should be once only)
	
		// get dozens and their neighbors on top (column1) (will be used later, forward declaration.
		auto zerro = mFields.find(EField::Number0)->second;
		auto number1 = mFields.find(EField::Number1)->second;
		auto number2 = mFields.find(EField::Number2)->second;
		auto number3 = mFields.find(EField::Number3)->second;
		auto dozen1 = mFields.find(EField::Dozen1)->second;
		auto dozen2 = mFields.find(EField::Dozen2)->second;
		auto dozen3 = mFields.find(EField::Dozen3)->second;
		auto number4 = mFields.find(EField::Number4)->second;
		auto number7 = mFields.find(EField::Number7)->second;
		auto number10 = mFields.find(EField::Number10)->second;
		auto number13 = mFields.find(EField::Number13)->second;
		auto number16 = mFields.find(EField::Number16)->second;
		auto number19 = mFields.find(EField::Number19)->second;
		auto number22 = mFields.find(EField::Number22)->second;
		auto number25 = mFields.find(EField::Number25)->second;
		auto number28 = mFields.find(EField::Number28)->second;
		auto number31 = mFields.find(EField::Number31)->second;
		auto number34 = mFields.find(EField::Number34)->second;
		auto dummy1 = mFields.find(EField::Dummy1)->second;

		// begin attaching beinning from zero and connect signals by the way
		attach(*zerro, 0, 0, 1, 3);

		// neighbors to the left
		number1->signal_bet_left.connect(sigc::mem_fun(zerro, &Field::on_signal_bet_right));
		number2->signal_bet_left.connect(sigc::mem_fun(zerro, &Field::on_signal_bet_right));
		//number3->signal_bet_left.connect(sigc::mem_fun(zerro, &Field::on_signal_bet_right)); // number 3 will be connected in for loop below

		// signal emited to zero
		number1->signal_bet_top_left.connect(sigc::mem_fun(zerro, &Field::on_signal_bet_top_right));
		number2->signal_bet_top_left.connect(sigc::mem_fun(zerro, &Field::on_signal_bet_top_right));
		number1->signal_bet_bottom_left.connect(sigc::mem_fun(zerro, &Field::on_signal_bet_bottom_right));
		number2->signal_bet_bottom_left.connect(sigc::mem_fun(zerro, &Field::on_signal_bet_bottom_right));

		// signals emitted by zero
		zerro->signal_bet_split1.connect(sigc::mem_fun(number3, &Field::on_signal_bet_left));
		zerro->signal_bet_split2.connect(sigc::mem_fun(number2, &Field::on_signal_bet_left));
		zerro->signal_bet_split3.connect(sigc::mem_fun(number1, &Field::on_signal_bet_left));
		zerro->signal_bet_street1.connect(sigc::mem_fun(number3, &Field::on_signal_bet_bottom_left));
		zerro->signal_bet_street1.connect(sigc::mem_fun(number2, &Field::on_signal_bet_top_left));
		zerro->signal_bet_street2.connect(sigc::mem_fun(number2, &Field::on_signal_bet_bottom_left));
		zerro->signal_bet_street2.connect(sigc::mem_fun(number1, &Field::on_signal_bet_top_left));
		zerro->signal_bet_basket.connect(sigc::mem_fun(dozen1, &Field::on_signal_bet_top_left));
		zerro->signal_bet_basket.connect(sigc::mem_fun(dummy1, &Field::on_signal_bet_top_right));
		zerro->signal_bet_basket.connect(sigc::mem_fun(number1, &Field::on_signal_bet_bottom_left));

		// dummy1 - placed below zero
		attach(*mFields.find(EField::Dummy1)->second, 0, 3, 1, 2);
		dummy1->signal_bet_basket.connect(sigc::mem_fun(zerro, &Field::on_signal_bet_bottom_right));
		dummy1->signal_bet_basket.connect(sigc::mem_fun(number1, &Field::on_signal_bet_bottom_left));
		dummy1->signal_bet_basket.connect(sigc::mem_fun(dozen1, &Field::on_signal_bet_top_left));

		// begin attaching fields column by column where each column is vertical Gtk::Grid column consiting of 3 numbers
		for (int // the numbers (col1, col2 and col3) are equivalent to roulette street numbers beginning from street 1
			col1 = 1, // number from roulette column1 = 1
			col2 = 2, // number from roulette column2 = 2
			col3 = 3, // number from roulette column3 = 3
			col = 1; // the acctual vertical column according to Gtk::Grid / or street acording to roulette table
			col3 <= 36; // using roulette column3 here, it's the same as col2 <= 35 or col3 <= 34
			col1 += 3, // increase number from roulete table column1 by 3 
			col2 += 3, // increase number from roulete table column2 by 3 
			col3 += 3, // increase number from roulete table column3 by 3 
			++col) // iterate street by street
		{
			// attach current street beginning from top to bottom
			attach(*mFields.find(static_cast<EField>(col3))->second, col, 0, 1, 1); // on roulette table this is: Field, street number, column number, size, size
			attach(*mFields.find(static_cast<EField>(col2))->second, col, 1, 1, 1);
			attach(*mFields.find(static_cast<EField>(col1))->second, col, 2, 1, 1);

			// begin connecting signals...
			// get numbers (Fields): 1, 2, 3 from current street ...
			auto c1 = mFields.find(static_cast<EField>(col1))->second;
			auto c2 = mFields.find(static_cast<EField>(col2))->second;
			auto c3 = mFields.find(static_cast<EField>(col3))->second;

			// neighbors on top
			c2->signal_bet_top.connect(sigc::mem_fun(c3, &Field::on_signal_bet_bottom));
			c1->signal_bet_top.connect(sigc::mem_fun(c2, &Field::on_signal_bet_bottom));

			// neighbors on bottom
			c3->signal_bet_bottom.connect(sigc::mem_fun(c2, &Field::on_signal_bet_top));
			c2->signal_bet_bottom.connect(sigc::mem_fun(c1, &Field::on_signal_bet_top));

			// neighbors to the right ( using +/- relative to current filed)
			if (mFields.count(static_cast<EField>(col1 + 3))) // count returns either 0 or 1, need to check on first street and last street
			{
				auto right1 = mFields.find(static_cast<EField>(col1 + 3))->second;
				c1->signal_bet_right.connect(sigc::mem_fun(right1, &Field::on_signal_bet_left));
			}
			if (mFields.count(static_cast<EField>(col2 + 3)))
			{
				auto right2 = mFields.find(static_cast<EField>(col2 + 3))->second;
				c2->signal_bet_right.connect(sigc::mem_fun(right2, &Field::on_signal_bet_left));
			}
			if (mFields.count(static_cast<EField>(col3 + 3)))
			{
				auto right3 = mFields.find(static_cast<EField>(col3 + 3))->second;
				c3->signal_bet_right.connect(sigc::mem_fun(right3, &Field::on_signal_bet_left));
			}

			// neighbors to the left
			if (mFields.count(static_cast<EField>(col1 - 3)))
			{
				auto left1 = mFields.find(static_cast<EField>(col1 - 3))->second;
				c1->signal_bet_left.connect(sigc::mem_fun(left1, &Field::on_signal_bet_right));
			}
			if (mFields.count(static_cast<EField>(col2 - 3)))
			{
				auto left2 = mFields.find(static_cast<EField>(col2 - 3))->second;
				c2->signal_bet_left.connect(sigc::mem_fun(left2, &Field::on_signal_bet_right));
			}
			if (mFields.count(static_cast<EField>(col3 - 3)))
			{
				auto left3 = mFields.find(static_cast<EField>(col3 - 3))->second;
				c3->signal_bet_left.connect(sigc::mem_fun(left3, &Field::on_signal_bet_right));
			}

			// neighbors on right top
			if (mFields.count(static_cast<EField>(col1 + 4)))
			{
				auto right_top = mFields.find(static_cast<EField>(col1 + 4))->second;
				c1->signal_bet_top_right.connect(sigc::mem_fun(right_top, &Field::on_signal_bet_bottom_left));
			}
			if (mFields.count(static_cast<EField>(col2 + 4)))
			{
				auto right_top = mFields.find(static_cast<EField>(col2 + 4))->second;
				c2->signal_bet_top_right.connect(sigc::mem_fun(right_top, &Field::on_signal_bet_bottom_left));
			}
			if (mFields.count(static_cast<EField>(col1 + 1)))
			{
				auto right_top = mFields.find(static_cast<EField>(col1 + 1))->second;
				c1->signal_bet_top_right.connect(sigc::mem_fun(right_top, &Field::on_signal_bet_bottom_right));
			}
			if (mFields.count(static_cast<EField>(col2 + 1)))
			{
				auto right_top = mFields.find(static_cast<EField>(col2 + 1))->second;
				c2->signal_bet_top_right.connect(sigc::mem_fun(right_top, &Field::on_signal_bet_bottom_right));
			}
			if (mFields.count(static_cast<EField>(col1 + 3)))
			{
				auto right_top = mFields.find(static_cast<EField>(col1 + 3))->second;
				c1->signal_bet_top_right.connect(sigc::mem_fun(right_top, &Field::on_signal_bet_top_left));
			}
			if (mFields.count(static_cast<EField>(col2 + 3)))
			{
				auto right_top = mFields.find(static_cast<EField>(col2 + 3))->second;
				c2->signal_bet_top_right.connect(sigc::mem_fun(right_top, &Field::on_signal_bet_top_left));
			}

			// neighbors on left top
			if (mFields.count(static_cast<EField>(col2 - 2)))
			{
				auto left_top = mFields.find(static_cast<EField>(col2 - 2))->second;
				if(left_top->get_index() != EField::Number0) // its already connected (this signal would be dead call)
					c2->signal_bet_top_left.connect(sigc::mem_fun(left_top, &Field::on_signal_bet_bottom_right));
			}
			if (mFields.count(static_cast<EField>(col1 - 2)))
			{
				auto left_top = mFields.find(static_cast<EField>(col1 - 2))->second;
				c1->signal_bet_top_left.connect(sigc::mem_fun(left_top, &Field::on_signal_bet_bottom_right));
			}
			if (mFields.count(static_cast<EField>(col2 + 1)))
			{
				auto left_top = mFields.find(static_cast<EField>(col2 + 1))->second;
				c2->signal_bet_top_left.connect(sigc::mem_fun(left_top, &Field::on_signal_bet_bottom_left));
			}
			if (mFields.count(static_cast<EField>(col1 + 1)))
			{
				auto left_top = mFields.find(static_cast<EField>(col1 + 1))->second;
				c1->signal_bet_top_left.connect(sigc::mem_fun(left_top, &Field::on_signal_bet_bottom_left));
			}

			if (mFields.count(static_cast<EField>(col2 - 3)))
			{
				auto left_top = mFields.find(static_cast<EField>(col2 - 3))->second;
				c2->signal_bet_top_left.connect(sigc::mem_fun(left_top, &Field::on_signal_bet_top_right));
			}
			if (mFields.count(static_cast<EField>(col1 - 3)))
			{
				auto left_top = mFields.find(static_cast<EField>(col1 - 3))->second;
				c1->signal_bet_top_left.connect(sigc::mem_fun(left_top, &Field::on_signal_bet_top_right));
			}

			// neighbors on bottom right
			if (mFields.count(static_cast<EField>(col3 + 2)))
			{
				auto bottom_right = mFields.find(static_cast<EField>(col3 + 2))->second;
				c3->signal_bet_bottom_right.connect(sigc::mem_fun(bottom_right, &Field::on_signal_bet_top_left));
			}
			if (mFields.count(static_cast<EField>(col2 + 2)))
			{
				auto bottom_right = mFields.find(static_cast<EField>(col2 + 2))->second;
				c2->signal_bet_bottom_right.connect(sigc::mem_fun(bottom_right, &Field::on_signal_bet_top_left));
			}
			if (mFields.count(static_cast<EField>(col3 - 1)))
			{
				auto bottom_right = mFields.find(static_cast<EField>(col3 - 1))->second;
				c3->signal_bet_bottom_right.connect(sigc::mem_fun(bottom_right, &Field::on_signal_bet_top_right));
			}
			if (mFields.count(static_cast<EField>(col2 - 1)))
			{
				auto bottom_right = mFields.find(static_cast<EField>(col2 - 1))->second;
				c2->signal_bet_bottom_right.connect(sigc::mem_fun(bottom_right, &Field::on_signal_bet_top_right));
			}
			if (mFields.count(static_cast<EField>(col3 + 3)))
			{
				auto bottom_right = mFields.find(static_cast<EField>(col3 + 3))->second;
				c3->signal_bet_bottom_right.connect(sigc::mem_fun(bottom_right, &Field::on_signal_bet_bottom_left));
			}
			if (mFields.count(static_cast<EField>(col2 + 3)))
			{
				auto bottom_right = mFields.find(static_cast<EField>(col2 + 3))->second;
				c2->signal_bet_bottom_right.connect(sigc::mem_fun(bottom_right, &Field::on_signal_bet_bottom_left));
			}
			if (mFields.count(static_cast<EField>(col1 + 3)))
			{
				auto bottom_right = mFields.find(static_cast<EField>(col1 + 3))->second;
				c1->signal_bet_bottom_right.connect(sigc::mem_fun(bottom_right, &Field::on_signal_bet_bottom_left));
			}

			// neighbors on left bottom
			if (mFields.count(static_cast<EField>(col3 - 1)))
			{
				auto left_bottom = mFields.find(static_cast<EField>(col3 - 1))->second;
				c3->signal_bet_bottom_left.connect(sigc::mem_fun(left_bottom, &Field::on_signal_bet_top_left));
			}
			if (mFields.count(static_cast<EField>(col2 - 1)))
			{
				auto left_bottom = mFields.find(static_cast<EField>(col2 - 1))->second;
				c2->signal_bet_bottom_left.connect(sigc::mem_fun(left_bottom, &Field::on_signal_bet_top_left));
			}
			if (mFields.count(static_cast<EField>(col3 - 4)))
			{
				auto left_bottom = mFields.find(static_cast<EField>(col3 - 4))->second;
				c3->signal_bet_bottom_left.connect(sigc::mem_fun(left_bottom, &Field::on_signal_bet_top_right));
			}
			if (mFields.count(static_cast<EField>(col2 - 4)))
			{
				auto left_bottom = mFields.find(static_cast<EField>(col2 - 4))->second;
				c2->signal_bet_bottom_left.connect(sigc::mem_fun(left_bottom, &Field::on_signal_bet_top_right));
			}
			if (mFields.count(static_cast<EField>(col3 - 3)))
			{
				auto left_bottom = mFields.find(static_cast<EField>(col3 - 3))->second;
				c3->signal_bet_bottom_left.connect(sigc::mem_fun(left_bottom, &Field::on_signal_bet_bottom_right));
			}
			if (mFields.count(static_cast<EField>(col2 - 3)))
			{
				auto left_bottom = mFields.find(static_cast<EField>(col2 - 3))->second;
				c2->signal_bet_bottom_left.connect(sigc::mem_fun(left_bottom, &Field::on_signal_bet_bottom_right));
			}
			if (mFields.count(static_cast<EField>(col1 - 3)))
			{
				auto left_bottom = mFields.find(static_cast<EField>(col1 - 3))->second;
				c1->signal_bet_bottom_left.connect(sigc::mem_fun(left_bottom, &Field::on_signal_bet_bottom_right));
			}
		} // for


		// attach column fields
		attach(*mFields.find(EField::Column3)->second, 13, 0, 1, 1);
		attach(*mFields.find(EField::Column2)->second, 13, 1, 1, 1);
		attach(*mFields.find(EField::Column1)->second, 13, 2, 1, 1);

		// attach dozens
		attach(*dozen1, 1, 3, 4, 1);
		attach(*dozen2, 5, 3, 4, 1);
		attach(*dozen3, 9, 3, 4, 1);

		// connect dozen1 for basket
		dozen1->signal_bet_basket.connect(sigc::mem_fun(number1, &Field::on_signal_bet_bottom_left));
		dozen1->signal_bet_basket.connect(sigc::mem_fun(zerro, &Field::on_signal_bet_bottom_right));

		// connect streets
		dozen1->signal_bet_street1.connect(sigc::mem_fun(number1, &Field::on_signal_bet_bottom));
		dozen1->signal_bet_street2.connect(sigc::mem_fun(number4, &Field::on_signal_bet_bottom));
		dozen1->signal_bet_street3.connect(sigc::mem_fun(number7, &Field::on_signal_bet_bottom));
		dozen1->signal_bet_street4.connect(sigc::mem_fun(number10, &Field::on_signal_bet_bottom));

		dozen2->signal_bet_street1.connect(sigc::mem_fun(number13, &Field::on_signal_bet_bottom));
		dozen2->signal_bet_street2.connect(sigc::mem_fun(number16, &Field::on_signal_bet_bottom));
		dozen2->signal_bet_street3.connect(sigc::mem_fun(number19, &Field::on_signal_bet_bottom));
		dozen2->signal_bet_street4.connect(sigc::mem_fun(number22, &Field::on_signal_bet_bottom));

		dozen3->signal_bet_street1.connect(sigc::mem_fun(number25, &Field::on_signal_bet_bottom));
		dozen3->signal_bet_street2.connect(sigc::mem_fun(number28, &Field::on_signal_bet_bottom));
		dozen3->signal_bet_street3.connect(sigc::mem_fun(number31, &Field::on_signal_bet_bottom));
		dozen3->signal_bet_street4.connect(sigc::mem_fun(number34, &Field::on_signal_bet_bottom));

		// connect lines for dozen1
		dozen1->signal_bet_line1.connect(sigc::mem_fun(number1, &Field::on_signal_bet_bottom_left));
		dozen1->signal_bet_line1.connect(sigc::mem_fun(zerro, &Field::on_signal_bet_bottom_right));
		dozen1->signal_bet_line1.connect(sigc::mem_fun(dummy1, &Field::on_signal_bet_top_right));

		dozen1->signal_bet_line2.connect(sigc::mem_fun(number1, &Field::on_signal_bet_bottom_right));
		dozen1->signal_bet_line2.connect(sigc::mem_fun(number4, &Field::on_signal_bet_bottom_left));

		dozen1->signal_bet_line3.connect(sigc::mem_fun(number4, &Field::on_signal_bet_bottom_right));
		dozen1->signal_bet_line3.connect(sigc::mem_fun(number7, &Field::on_signal_bet_bottom_left));

		dozen1->signal_bet_line4.connect(sigc::mem_fun(number7, &Field::on_signal_bet_bottom_right));
		dozen1->signal_bet_line4.connect(sigc::mem_fun(number10, &Field::on_signal_bet_bottom_left));

		dozen1->signal_bet_line5.connect(sigc::mem_fun(number10, &Field::on_signal_bet_bottom_right));
		dozen1->signal_bet_line5.connect(sigc::mem_fun(number13, &Field::on_signal_bet_bottom_left));
		dozen1->signal_bet_line5.connect(sigc::mem_fun(dozen2, &Field::on_signal_bet_top_left));

		// connect lines for dozen2
		dozen2->signal_bet_line1.connect(sigc::mem_fun(dozen1, &Field::on_signal_bet_top_right));
		dozen2->signal_bet_line1.connect(sigc::mem_fun(number10, &Field::on_signal_bet_bottom_right));
		dozen2->signal_bet_line1.connect(sigc::mem_fun(number13, &Field::on_signal_bet_bottom_left));

		dozen2->signal_bet_line2.connect(sigc::mem_fun(number13, &Field::on_signal_bet_bottom_right));
		dozen2->signal_bet_line2.connect(sigc::mem_fun(number16, &Field::on_signal_bet_bottom_left));

		dozen2->signal_bet_line3.connect(sigc::mem_fun(number16, &Field::on_signal_bet_bottom_right));
		dozen2->signal_bet_line3.connect(sigc::mem_fun(number19, &Field::on_signal_bet_bottom_left));

		dozen2->signal_bet_line4.connect(sigc::mem_fun(number19, &Field::on_signal_bet_bottom_right));
		dozen2->signal_bet_line4.connect(sigc::mem_fun(number22, &Field::on_signal_bet_bottom_left));

		dozen2->signal_bet_line5.connect(sigc::mem_fun(number22, &Field::on_signal_bet_bottom_right));
		dozen2->signal_bet_line5.connect(sigc::mem_fun(number25, &Field::on_signal_bet_bottom_left));
		dozen2->signal_bet_line5.connect(sigc::mem_fun(dozen3, &Field::on_signal_bet_top_left));

		// connect lines for dozen3
		dozen3->signal_bet_line1.connect(sigc::mem_fun(dozen2, &Field::on_signal_bet_top_right));
		dozen3->signal_bet_line1.connect(sigc::mem_fun(number22, &Field::on_signal_bet_bottom_right));
		dozen3->signal_bet_line1.connect(sigc::mem_fun(number25, &Field::on_signal_bet_bottom_left));

		dozen3->signal_bet_line2.connect(sigc::mem_fun(number25, &Field::on_signal_bet_bottom_right));
		dozen3->signal_bet_line2.connect(sigc::mem_fun(number28, &Field::on_signal_bet_bottom_left));

		dozen3->signal_bet_line3.connect(sigc::mem_fun(number28, &Field::on_signal_bet_bottom_right));
		dozen3->signal_bet_line3.connect(sigc::mem_fun(number31, &Field::on_signal_bet_bottom_left));

		dozen3->signal_bet_line4.connect(sigc::mem_fun(number31, &Field::on_signal_bet_bottom_right));
		dozen3->signal_bet_line4.connect(sigc::mem_fun(number34, &Field::on_signal_bet_bottom_left));

		// connect column1 to dozen1
		number1->signal_bet_bottom_left.connect(sigc::mem_fun(dummy1, &Field::on_signal_bet_top_right));
		number1->signal_bet_bottom_left.connect(sigc::mem_fun(dozen1, &Field::on_signal_bet_top_left));
		number1->signal_bet_bottom.connect(sigc::mem_fun(dozen1, &Field::on_signal_bet_top));
		number1->signal_bet_bottom_right.connect(sigc::mem_fun(dozen1, &Field::on_signal_bet_top_right));

		number4->signal_bet_bottom_left.connect(sigc::mem_fun(dozen1, &Field::on_signal_bet_top_left));
		number4->signal_bet_bottom.connect(sigc::mem_fun(dozen1, &Field::on_signal_bet_top));
		number4->signal_bet_bottom_right.connect(sigc::mem_fun(dozen1, &Field::on_signal_bet_top_right));

		number7->signal_bet_bottom_left.connect(sigc::mem_fun(dozen1, &Field::on_signal_bet_top_left));
		number7->signal_bet_bottom.connect(sigc::mem_fun(dozen1, &Field::on_signal_bet_top));
		number7->signal_bet_bottom_right.connect(sigc::mem_fun(dozen1, &Field::on_signal_bet_top_right));

		number10->signal_bet_bottom_left.connect(sigc::mem_fun(dozen1, &Field::on_signal_bet_top_left));
		number10->signal_bet_bottom.connect(sigc::mem_fun(dozen1, &Field::on_signal_bet_top));
		number10->signal_bet_bottom_right.connect(sigc::mem_fun(dozen1, &Field::on_signal_bet_top_right));
		number10->signal_bet_bottom_right.connect(sigc::mem_fun(dozen2, &Field::on_signal_bet_top_left)); // NOTE: exception another dozen

		// connect column1 to dozen2
		number13->signal_bet_bottom_left.connect(sigc::mem_fun(dozen2, &Field::on_signal_bet_top_left));
		number13->signal_bet_bottom.connect(sigc::mem_fun(dozen2, &Field::on_signal_bet_top));
		number13->signal_bet_bottom_right.connect(sigc::mem_fun(dozen2, &Field::on_signal_bet_top_right));
		number13->signal_bet_bottom_left.connect(sigc::mem_fun(dozen1, &Field::on_signal_bet_top_right)); // NOTE: exception another dozen

		number16->signal_bet_bottom_left.connect(sigc::mem_fun(dozen2, &Field::on_signal_bet_top_left));
		number16->signal_bet_bottom.connect(sigc::mem_fun(dozen2, &Field::on_signal_bet_top));
		number16->signal_bet_bottom_right.connect(sigc::mem_fun(dozen2, &Field::on_signal_bet_top_right));

		number19->signal_bet_bottom_left.connect(sigc::mem_fun(dozen2, &Field::on_signal_bet_top_left));
		number19->signal_bet_bottom.connect(sigc::mem_fun(dozen2, &Field::on_signal_bet_top));
		number19->signal_bet_bottom_right.connect(sigc::mem_fun(dozen2, &Field::on_signal_bet_top_right));

		number22->signal_bet_bottom_left.connect(sigc::mem_fun(dozen2, &Field::on_signal_bet_top_left));
		number22->signal_bet_bottom.connect(sigc::mem_fun(dozen2, &Field::on_signal_bet_top));
		number22->signal_bet_bottom_right.connect(sigc::mem_fun(dozen2, &Field::on_signal_bet_top_right));
		number22->signal_bet_bottom_right.connect(sigc::mem_fun(dozen3, &Field::on_signal_bet_top_left)); // NOTE: exception another dozen

		// connect column1 to dozen3
		number25->signal_bet_bottom_left.connect(sigc::mem_fun(dozen3, &Field::on_signal_bet_top_left));
		number25->signal_bet_bottom.connect(sigc::mem_fun(dozen3, &Field::on_signal_bet_top));
		number25->signal_bet_bottom_right.connect(sigc::mem_fun(dozen3, &Field::on_signal_bet_top_right));
		number25->signal_bet_bottom_left.connect(sigc::mem_fun(dozen2, &Field::on_signal_bet_top_right)); // NOTE: exception another dozen

		number28->signal_bet_bottom_left.connect(sigc::mem_fun(dozen3, &Field::on_signal_bet_top_left));
		number28->signal_bet_bottom.connect(sigc::mem_fun(dozen3, &Field::on_signal_bet_top));
		number28->signal_bet_bottom_right.connect(sigc::mem_fun(dozen3, &Field::on_signal_bet_top_right));

		number31->signal_bet_bottom_left.connect(sigc::mem_fun(dozen3, &Field::on_signal_bet_top_left));
		number31->signal_bet_bottom.connect(sigc::mem_fun(dozen3, &Field::on_signal_bet_top));
		number31->signal_bet_bottom_right.connect(sigc::mem_fun(dozen3, &Field::on_signal_bet_top_right));

		number34->signal_bet_bottom_left.connect(sigc::mem_fun(dozen3, &Field::on_signal_bet_top_left));
		number34->signal_bet_bottom.connect(sigc::mem_fun(dozen3, &Field::on_signal_bet_top));

		// dummy2 ( placed below column fields "2 to 1" )
		attach(*mFields.find(EField::Dummy2)->second, 13, 3, 1, 2);

		// low/high red/black high/low
		attach(*mFields.find(EField::Low)->second, 1, 4, 2, 1);
		attach(*mFields.find(EField::Even)->second, 3, 4, 2, 1);
		attach(*mFields.find(EField::Red)->second, 5, 4, 2, 1);
		attach(*mFields.find(EField::Black)->second, 7, 4, 2, 1);
		attach(*mFields.find(EField::Odd)->second, 9, 4, 2, 1);
		attach(*mFields.find(EField::High)->second, 11, 4, 2, 1);



		// set up table limits

		// single zero layout
		mMaxBets.insert(make_pair(EBet::StraightUp, 37));
		mMaxBets.insert(make_pair(EBet::Split, 60));
		mMaxBets.insert(make_pair(EBet::Street, 12));
		mMaxBets.insert(make_pair(EBet::Corner, 23));
		mMaxBets.insert(make_pair(EBet::Basket, 0));
		mMaxBets.insert(make_pair(EBet::Line, 11));
		mMaxBets.insert(make_pair(EBet::Column1, 1));
		mMaxBets.insert(make_pair(EBet::Column2, 1));
		mMaxBets.insert(make_pair(EBet::Column3, 1));
		mMaxBets.insert(make_pair(EBet::Dozen1, 1));
		mMaxBets.insert(make_pair(EBet::Dozen2, 1));
		mMaxBets.insert(make_pair(EBet::Dozen3, 1));
		mMaxBets.insert(make_pair(EBet::High, 1));
		mMaxBets.insert(make_pair(EBet::Low, 1));
		mMaxBets.insert(make_pair(EBet::Red, 1));
		mMaxBets.insert(make_pair(EBet::Black, 1));
		mMaxBets.insert(make_pair(EBet::Even, 1));
		mMaxBets.insert(make_pair(EBet::Odd, 1));

		mMaxiter = mMaxBets.begin();

		switch (mTableType)
		{
		case ETable::American:
			// modify maximum number of single EBet that can be placed on a ETable
			mMaxiter->second = 38;
			++mMaxiter;
			mMaxiter->second = 61;
			++mMaxiter;
			mMaxiter->second = 15;
			++mMaxiter;
			mMaxiter->second = 22;
			++mMaxiter;
			mMaxiter->second = 1;
			++mMaxiter;
			mMaxiter->second = 11;

			// blacklisted bets for this table
			mBlacklist.push_back(EBet::Jeu0);
			mBlacklist.push_back(EBet::OrphelinsEnPlen);
			mBlacklist.push_back(EBet::OrphelinsACheval);
			mBlacklist.push_back(EBet::TriesDuCylindre);
			mBlacklist.push_back(EBet::VoisinsDeZero);
			break;

		case ETable::NoZero:
			mMaxiter->second = 36;
			++mMaxiter;
			mMaxiter->second = 57;
			++mMaxiter;
			mMaxiter->second = 10;
			++mMaxiter;
			++mMaxiter;
			mMaxiter->second = 0;

			mBlacklist.push_back(EBet::Jeu0);
			mBlacklist.push_back(EBet::Basket);
			mBlacklist.push_back(EBet::Maximus0);
			mBlacklist.push_back(EBet::Maximus00);
			mBlacklist.push_back(EBet::VoisinsDeZero);
			mBlacklist.push_back(EBet::FinalesEnPlen0);
			mBlacklist.push_back(EBet::FinalesACheval01);
			break;
		case ETable::European:
		case ETable::French:
		case ETable::SingleImprisonment:
		case ETable::DoubleImprisonment:
		case ETable::TripleImprisonment:
		case ETable::InfininiteImprisonment:
		default: // single zero table
			mBlacklist.push_back(EBet::Basket);
			mBlacklist.push_back(EBet::Maximus00);
			break;
		}

		// calculate SUM of total bets
		for (mMaxiter = mMaxBets.begin(); mMaxiter != mMaxBets.end(); ++mMaxiter)
			mTotalBets += mMaxiter->second;

		// Insert initial miminums
		mMinimums.insert(make_pair(EMinimum::Inside, 1));
		mMinimums.insert(make_pair(EMinimum::Outside, 1));
		mMinimums.insert(make_pair(EMinimum::Table, 1));

		//Insert initial maximums
		mMaximums.insert(make_pair(EBet::StraightUp, 20));
		mMaximums.insert(make_pair(EBet::Split, 40));
		mMaximums.insert(make_pair(EBet::Street, 60));
		mMaximums.insert(make_pair(EBet::Corner, 80));
		mMaximums.insert(make_pair(EBet::Basket, 80));
		mMaximums.insert(make_pair(EBet::Line, 120));
		mMaximums.insert(make_pair(EBet::Column1, 200));
		mMaximums.insert(make_pair(EBet::Column2, 200));
		mMaximums.insert(make_pair(EBet::Column3, 200));
		mMaximums.insert(make_pair(EBet::Dozen1, 200));
		mMaximums.insert(make_pair(EBet::Dozen2, 200));
		mMaximums.insert(make_pair(EBet::Dozen3, 200));
		mMaximums.insert(make_pair(EBet::Red, 400));
		mMaximums.insert(make_pair(EBet::Black, 400));
		mMaximums.insert(make_pair(EBet::Even, 400));
		mMaximums.insert(make_pair(EBet::Odd, 400));
		mMaximums.insert(make_pair(EBet::High, 400));
		mMaximums.insert(make_pair(EBet::Low, 400));

		SetTableMax();
	}

	Table::~Table()
	{
		for (size_t i = 0; i <= mFields.size(); i++)
		{
			delete mFields.at(static_cast<EField>(i));
		}
	}

#ifdef _MSC_VER
#pragma endregion begin

#pragma region
#endif // _MSC_VER

	ETable Table::get_table_type()
	{
		return mTableType;
	}

	void Table::SetTableMax(const short& limit /*= 0*/)
	{
		if (limit > GetLimit(EBet::Red))
		{
			mTableMax = limit;
			return;
		}

		if (limit) // if limit is not 0
			limit > 0 ? throw error("CTable -> SetTableMax -> Table max smaler then even oney bet") : throw error("CTable -> SetMinimum -> Table limit too low");

		// if limit is zero it will be calculated according to maximum bets possible
		mTableMax = 0;
		mMaxiter = mMaxBets.begin();
		for (auto btMax = mMaximums.begin(); btMax != mMaximums.end(); ++mMaxiter, ++btMax)
			mTableMax += mMaxiter->second * btMax->second;
	}

	void Table::PrintProperties() const
	{
		using std::cout;
		using std::endl;

		cout << "Table properties" << endl;
		cout << "**************************" << endl << endl;
		cout << "Layout	";
		switch (mTableType)
		{
		case ETable::NoZero:
			cout << "	No zerro" << endl;
			break;
		case ETable::American:
			cout << "	American" << endl;
			break;
		case ETable::European:
			cout << "	European" << endl;
			break;
		case ETable::French:
			cout << "	French ";
			switch (mTableType)
			{
			case ETable::SingleImprisonment:
				cout << "single imprisonment" << endl;
				break;
			case ETable::DoubleImprisonment:
				cout << "double imprisonment" << endl;
				break;
			case ETable::TripleImprisonment:
				cout << "triple imprisonment" << endl;
				break;
			case ETable::InfininiteImprisonment:
				cout << "infinite imprisonment" << endl;
				break;
			default:
				cout << endl;
				break;
			} //single zero table
			cout << "Maximum bets    " << mTotalBets << endl;
			break;
		}
		cout << "Inside min.	" << mMinimums.at(EMinimum::Inside) << endl;
		cout << "Outside min.	" << mMinimums.at(EMinimum::Outside) << endl;
		cout << "Table min.	" << mMinimums.at(EMinimum::Table) << endl;
		cout << "Table max.	" << mTableMax << endl;
		cout << "StraightUp	" << mMaximums.at(EBet::StraightUp) << endl;
		cout << "Split		" << mMaximums.at(EBet::Split) << endl;
		cout << "Street		" << mMaximums.at(EBet::Street) << endl;
		cout << "Corner		" << mMaximums.at(EBet::Corner) << endl;
		cout << "Basket		" << mMaximums.at(EBet::Basket) << endl;
		cout << "Line		" << mMaximums.at(EBet::Line) << endl;
		cout << "Column/Dozen	" << mMaximums.at(EBet::Column1) << endl;
		cout << "EvenMoney	" << mMaximums.at(EBet::Red) << endl;
	}

#ifdef _MSC_VER
#pragma endregion methods
#endif // _MSC_VER

} // namespace roulette
