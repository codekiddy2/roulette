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
// TODO: make print_properties print into a widget
//
///</summary>

// roulette
#include "pch.hh"
#include "pragmas.hh"
#include "table.hh"
#include "field.hh"
#include "sets.hh"

namespace
{
	using std::get; // to extract type_chip_tuple
	using std::make_pair; // to make EField Field pair
}

namespace roulette
{

#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER


	Table::Table(const ETable table_type) :
		IErrorHandler("Table"),
		m_tabletype(table_type),
		m_tablemax(0),
		m_totalbets(0)
	{
		set_column_homogeneous(true);
		set_row_homogeneous(true);

		// create fields
		EField temp;
		for (uint64 i = 0; i < static_cast<uint64>(EField::Dummy3); i++)
		{
			temp = static_cast<EField>(i);
			m_fields.insert(make_pair(temp, new Field(temp, this)));
		}
		// TODO: check if any signals are connected more than once,
		//ex: debug output how many times handlers get called per chip placed (should be twice at most - drawing and bet signal)

		// get dozens and their neighbors on top (column1) (will be used later, forward declaration.
		auto zerro = m_fields.find(EField::Number0)->second;
		auto number1 = m_fields.find(EField::Number1)->second;
		auto number2 = m_fields.find(EField::Number2)->second;
		auto number3 = m_fields.find(EField::Number3)->second;
		auto dozen1 = m_fields.find(EField::Dozen1)->second;
		auto dozen2 = m_fields.find(EField::Dozen2)->second;
		auto dozen3 = m_fields.find(EField::Dozen3)->second;
		auto number4 = m_fields.find(EField::Number4)->second;
		auto number7 = m_fields.find(EField::Number7)->second;
		auto number10 = m_fields.find(EField::Number10)->second;
		auto number13 = m_fields.find(EField::Number13)->second;
		auto number16 = m_fields.find(EField::Number16)->second;
		auto number19 = m_fields.find(EField::Number19)->second;
		auto number22 = m_fields.find(EField::Number22)->second;
		auto number25 = m_fields.find(EField::Number25)->second;
		auto number28 = m_fields.find(EField::Number28)->second;
		auto number31 = m_fields.find(EField::Number31)->second;
		auto number34 = m_fields.find(EField::Number34)->second;
		auto dummy1 = m_fields.find(EField::Dummy1)->second;

		// begin attaching beinning from zero and connect signals by the way
		attach(*zerro, 0, 0, 1, 3);

		// neighbors to the left
		number1->signal_bet_left.connect(sigc::mem_fun(zerro, &Field::on_signal_bet_right));
		number2->signal_bet_left.connect(sigc::mem_fun(zerro, &Field::on_signal_bet_right));
		// number3 will be connected in for loop below

		// signal emited to zero - NOTE: zero does chips drawing for number3 when signal from numbe2 is received
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
		attach(*m_fields.find(EField::Dummy1)->second, 0, 3, 1, 2);
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
			attach(*m_fields.find(static_cast<EField>(col3))->second, col, 0, 1, 1); // on roulette table this is: Field, street number, column number, size, size
			attach(*m_fields.find(static_cast<EField>(col2))->second, col, 1, 1, 1);
			attach(*m_fields.find(static_cast<EField>(col1))->second, col, 2, 1, 1);

			// begin connecting signals...
			// get numbers (Fields): 1, 2, 3 from current street ...
			auto c1 = m_fields.find(static_cast<EField>(col1))->second;
			auto c2 = m_fields.find(static_cast<EField>(col2))->second;
			auto c3 = m_fields.find(static_cast<EField>(col3))->second;

			// neighbors on top
			c2->signal_bet_top.connect(sigc::mem_fun(c3, &Field::on_signal_bet_bottom));
			c1->signal_bet_top.connect(sigc::mem_fun(c2, &Field::on_signal_bet_bottom));

			// neighbors on bottom
			c3->signal_bet_bottom.connect(sigc::mem_fun(c2, &Field::on_signal_bet_top));
			c2->signal_bet_bottom.connect(sigc::mem_fun(c1, &Field::on_signal_bet_top));

			// neighbors to the right ( using +/- relative to current filed)
			if (m_fields.count(static_cast<EField>(col1 + 3))) // count returns either 0 or 1, need to check on first street and last street
			{
				auto right1 = m_fields.find(static_cast<EField>(col1 + 3))->second;
				c1->signal_bet_right.connect(sigc::mem_fun(right1, &Field::on_signal_bet_left));
			}
			if (m_fields.count(static_cast<EField>(col2 + 3)))
			{
				auto right2 = m_fields.find(static_cast<EField>(col2 + 3))->second;
				c2->signal_bet_right.connect(sigc::mem_fun(right2, &Field::on_signal_bet_left));
			}
			if (m_fields.count(static_cast<EField>(col3 + 3)))
			{
				auto right3 = m_fields.find(static_cast<EField>(col3 + 3))->second;
				c3->signal_bet_right.connect(sigc::mem_fun(right3, &Field::on_signal_bet_left));
			}

			// neighbors to the left
			if (m_fields.count(static_cast<EField>(col1 - 3)))
			{
				auto left1 = m_fields.find(static_cast<EField>(col1 - 3))->second;
				c1->signal_bet_left.connect(sigc::mem_fun(left1, &Field::on_signal_bet_right));
			}
			if (m_fields.count(static_cast<EField>(col2 - 3)))
			{
				auto left2 = m_fields.find(static_cast<EField>(col2 - 3))->second;
				c2->signal_bet_left.connect(sigc::mem_fun(left2, &Field::on_signal_bet_right));
			}
			if (m_fields.count(static_cast<EField>(col3 - 3)))
			{
				auto left3 = m_fields.find(static_cast<EField>(col3 - 3))->second;
				c3->signal_bet_left.connect(sigc::mem_fun(left3, &Field::on_signal_bet_right));
			}

			// neighbors on right top
			if (m_fields.count(static_cast<EField>(col1 + 4)))
			{
				auto right_top = m_fields.find(static_cast<EField>(col1 + 4))->second;
				c1->signal_bet_top_right.connect(sigc::mem_fun(right_top, &Field::on_signal_bet_bottom_left));
			}
			if (m_fields.count(static_cast<EField>(col2 + 4)))
			{
				auto right_top = m_fields.find(static_cast<EField>(col2 + 4))->second;
				c2->signal_bet_top_right.connect(sigc::mem_fun(right_top, &Field::on_signal_bet_bottom_left));
			}
			if (m_fields.count(static_cast<EField>(col1 + 1)))
			{
				auto right_top = m_fields.find(static_cast<EField>(col1 + 1))->second;
				c1->signal_bet_top_right.connect(sigc::mem_fun(right_top, &Field::on_signal_bet_bottom_right));
			}
			if (m_fields.count(static_cast<EField>(col2 + 1)))
			{
				auto right_top = m_fields.find(static_cast<EField>(col2 + 1))->second;
				c2->signal_bet_top_right.connect(sigc::mem_fun(right_top, &Field::on_signal_bet_bottom_right));
			}
			if (m_fields.count(static_cast<EField>(col1 + 3)))
			{
				auto right_top = m_fields.find(static_cast<EField>(col1 + 3))->second;
				c1->signal_bet_top_right.connect(sigc::mem_fun(right_top, &Field::on_signal_bet_top_left));
			}
			if (m_fields.count(static_cast<EField>(col2 + 3)))
			{
				auto right_top = m_fields.find(static_cast<EField>(col2 + 3))->second;
				c2->signal_bet_top_right.connect(sigc::mem_fun(right_top, &Field::on_signal_bet_top_left));
			}

			// neighbors on left top
			if (m_fields.count(static_cast<EField>(col2 - 2)))
			{
				auto left_top = m_fields.find(static_cast<EField>(col2 - 2))->second;
				if(left_top->get_index() != EField::Number0) // its already connected (this signal would be dead call)
					c2->signal_bet_top_left.connect(sigc::mem_fun(left_top, &Field::on_signal_bet_bottom_right));
			}
			if (m_fields.count(static_cast<EField>(col1 - 2)))
			{
				auto left_top = m_fields.find(static_cast<EField>(col1 - 2))->second;
				c1->signal_bet_top_left.connect(sigc::mem_fun(left_top, &Field::on_signal_bet_bottom_right));
			}
			if (m_fields.count(static_cast<EField>(col2 + 1)))
			{
				auto left_top = m_fields.find(static_cast<EField>(col2 + 1))->second;
				c2->signal_bet_top_left.connect(sigc::mem_fun(left_top, &Field::on_signal_bet_bottom_left));
			}
			if (m_fields.count(static_cast<EField>(col1 + 1)))
			{
				auto left_top = m_fields.find(static_cast<EField>(col1 + 1))->second;
				c1->signal_bet_top_left.connect(sigc::mem_fun(left_top, &Field::on_signal_bet_bottom_left));
			}

			if (m_fields.count(static_cast<EField>(col2 - 3)))
			{
				auto left_top = m_fields.find(static_cast<EField>(col2 - 3))->second;
				c2->signal_bet_top_left.connect(sigc::mem_fun(left_top, &Field::on_signal_bet_top_right));
			}
			if (m_fields.count(static_cast<EField>(col1 - 3)))
			{
				auto left_top = m_fields.find(static_cast<EField>(col1 - 3))->second;
				c1->signal_bet_top_left.connect(sigc::mem_fun(left_top, &Field::on_signal_bet_top_right));
			}

			// neighbors on bottom right
			if (m_fields.count(static_cast<EField>(col3 + 2)))
			{
				auto bottom_right = m_fields.find(static_cast<EField>(col3 + 2))->second;
				c3->signal_bet_bottom_right.connect(sigc::mem_fun(bottom_right, &Field::on_signal_bet_top_left));
			}
			if (m_fields.count(static_cast<EField>(col2 + 2)))
			{
				auto bottom_right = m_fields.find(static_cast<EField>(col2 + 2))->second;
				c2->signal_bet_bottom_right.connect(sigc::mem_fun(bottom_right, &Field::on_signal_bet_top_left));
			}
			if (m_fields.count(static_cast<EField>(col3 - 1)))
			{
				auto bottom_right = m_fields.find(static_cast<EField>(col3 - 1))->second;
				c3->signal_bet_bottom_right.connect(sigc::mem_fun(bottom_right, &Field::on_signal_bet_top_right));
			}
			if (m_fields.count(static_cast<EField>(col2 - 1)))
			{
				auto bottom_right = m_fields.find(static_cast<EField>(col2 - 1))->second;
				c2->signal_bet_bottom_right.connect(sigc::mem_fun(bottom_right, &Field::on_signal_bet_top_right));
			}
			if (m_fields.count(static_cast<EField>(col3 + 3)))
			{
				auto bottom_right = m_fields.find(static_cast<EField>(col3 + 3))->second;
				c3->signal_bet_bottom_right.connect(sigc::mem_fun(bottom_right, &Field::on_signal_bet_bottom_left));
			}
			if (m_fields.count(static_cast<EField>(col2 + 3)))
			{
				auto bottom_right = m_fields.find(static_cast<EField>(col2 + 3))->second;
				c2->signal_bet_bottom_right.connect(sigc::mem_fun(bottom_right, &Field::on_signal_bet_bottom_left));
			}
			if (m_fields.count(static_cast<EField>(col1 + 3)))
			{
				auto bottom_right = m_fields.find(static_cast<EField>(col1 + 3))->second;
				c1->signal_bet_bottom_right.connect(sigc::mem_fun(bottom_right, &Field::on_signal_bet_bottom_left));
			}

			// neighbors on left bottom
			if (m_fields.count(static_cast<EField>(col3 - 1)))
			{
				auto left_bottom = m_fields.find(static_cast<EField>(col3 - 1))->second;
				c3->signal_bet_bottom_left.connect(sigc::mem_fun(left_bottom, &Field::on_signal_bet_top_left));
			}
			if (m_fields.count(static_cast<EField>(col2 - 1)))
			{
				auto left_bottom = m_fields.find(static_cast<EField>(col2 - 1))->second;
				c2->signal_bet_bottom_left.connect(sigc::mem_fun(left_bottom, &Field::on_signal_bet_top_left));
			}
			if (m_fields.count(static_cast<EField>(col3 - 4)))
			{
				auto left_bottom = m_fields.find(static_cast<EField>(col3 - 4))->second;
				c3->signal_bet_bottom_left.connect(sigc::mem_fun(left_bottom, &Field::on_signal_bet_top_right));
			}
			if (m_fields.count(static_cast<EField>(col2 - 4)))
			{
				auto left_bottom = m_fields.find(static_cast<EField>(col2 - 4))->second;
				c2->signal_bet_bottom_left.connect(sigc::mem_fun(left_bottom, &Field::on_signal_bet_top_right));
			}
			if (m_fields.count(static_cast<EField>(col3 - 3)))
			{
				auto left_bottom = m_fields.find(static_cast<EField>(col3 - 3))->second;
				c3->signal_bet_bottom_left.connect(sigc::mem_fun(left_bottom, &Field::on_signal_bet_bottom_right));
			}
			if (m_fields.count(static_cast<EField>(col2 - 3)))
			{
				auto left_bottom = m_fields.find(static_cast<EField>(col2 - 3))->second;
				c2->signal_bet_bottom_left.connect(sigc::mem_fun(left_bottom, &Field::on_signal_bet_bottom_right));
			}
			if (m_fields.count(static_cast<EField>(col1 - 3)))
			{
				auto left_bottom = m_fields.find(static_cast<EField>(col1 - 3))->second;
				c1->signal_bet_bottom_left.connect(sigc::mem_fun(left_bottom, &Field::on_signal_bet_bottom_right));
			}
		} // for


		// attach column fields
		attach(*m_fields.find(EField::Column3)->second, 13, 0, 1, 1);
		attach(*m_fields.find(EField::Column2)->second, 13, 1, 1, 1);
		attach(*m_fields.find(EField::Column1)->second, 13, 2, 1, 1);

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
		attach(*m_fields.find(EField::Dummy2)->second, 13, 3, 1, 2);

		// low/high red/black high/low
		attach(*m_fields.find(EField::Low)->second, 1, 4, 2, 1);
		attach(*m_fields.find(EField::Even)->second, 3, 4, 2, 1);
		attach(*m_fields.find(EField::Red)->second, 5, 4, 2, 1);
		attach(*m_fields.find(EField::Black)->second, 7, 4, 2, 1);
		attach(*m_fields.find(EField::Odd)->second, 9, 4, 2, 1);
		attach(*m_fields.find(EField::High)->second, 11, 4, 2, 1);



		// set up table limits

		// single zero layout
		m_maxbets.insert(make_pair(EBet::StraightUp, 37));
		m_maxbets.insert(make_pair(EBet::Split, 60));
		m_maxbets.insert(make_pair(EBet::Street, 12));
		m_maxbets.insert(make_pair(EBet::Corner, 23));
		m_maxbets.insert(make_pair(EBet::Basket, 0));
		m_maxbets.insert(make_pair(EBet::Line, 11));
		m_maxbets.insert(make_pair(EBet::Column1, 1));
		m_maxbets.insert(make_pair(EBet::Column2, 1));
		m_maxbets.insert(make_pair(EBet::Column3, 1));
		m_maxbets.insert(make_pair(EBet::Dozen1, 1));
		m_maxbets.insert(make_pair(EBet::Dozen2, 1));
		m_maxbets.insert(make_pair(EBet::Dozen3, 1));
		m_maxbets.insert(make_pair(EBet::High, 1));
		m_maxbets.insert(make_pair(EBet::Low, 1));
		m_maxbets.insert(make_pair(EBet::Red, 1));
		m_maxbets.insert(make_pair(EBet::Black, 1));
		m_maxbets.insert(make_pair(EBet::Even, 1));
		m_maxbets.insert(make_pair(EBet::Odd, 1));

		m_maxiter = m_maxbets.begin();

		switch (m_tabletype)
		{
		case ETable::American:
			// modify maximum number of single EBet that can be placed on a ETable
			m_maxiter->second = 38;
			++m_maxiter;
			m_maxiter->second = 61;
			++m_maxiter;
			m_maxiter->second = 15;
			++m_maxiter;
			m_maxiter->second = 22;
			++m_maxiter;
			m_maxiter->second = 1;
			++m_maxiter;
			m_maxiter->second = 11;

			// blacklisted bets for this table
			m_blacklist.push_back(EBet::Jeu0);
			m_blacklist.push_back(EBet::OrphelinsEnPlen);
			m_blacklist.push_back(EBet::OrphelinsACheval);
			m_blacklist.push_back(EBet::TriesDuCylindre);
			m_blacklist.push_back(EBet::VoisinsDeZero);
			break;

		case ETable::NoZero:
			m_maxiter->second = 36;
			++m_maxiter;
			m_maxiter->second = 57;
			++m_maxiter;
			m_maxiter->second = 10;
			++m_maxiter;
			++m_maxiter;
			m_maxiter->second = 0;

			m_blacklist.push_back(EBet::Jeu0);
			m_blacklist.push_back(EBet::Basket);
			m_blacklist.push_back(EBet::Maximus0);
			m_blacklist.push_back(EBet::Maximus00);
			m_blacklist.push_back(EBet::VoisinsDeZero);
			m_blacklist.push_back(EBet::FinalesEnPlen0);
			m_blacklist.push_back(EBet::FinalesACheval01);
			break;
		case ETable::European:
		case ETable::French:
		case ETable::SingleImprisonment:
		case ETable::DoubleImprisonment:
		case ETable::TripleImprisonment:
		case ETable::InfininiteImprisonment:
		default: // single zero table
			m_blacklist.push_back(EBet::Basket);
			m_blacklist.push_back(EBet::Maximus00);
			break;
		}

		// calculate SUM of total bets
		for (m_maxiter = m_maxbets.begin(); m_maxiter != m_maxbets.end(); ++m_maxiter)
			m_totalbets += m_maxiter->second;

		// Insert initial miminums
		m_minimums.insert(make_pair(EMinimum::Inside, 1));
		m_minimums.insert(make_pair(EMinimum::Outside, 1));
		m_minimums.insert(make_pair(EMinimum::Table, 1));

		//Insert initial maximums
		m_maximums.insert(make_pair(EBet::StraightUp, 20));
		m_maximums.insert(make_pair(EBet::Split, 40));
		m_maximums.insert(make_pair(EBet::Street, 60));
		m_maximums.insert(make_pair(EBet::Corner, 80));
		m_maximums.insert(make_pair(EBet::Basket, 80));
		m_maximums.insert(make_pair(EBet::Line, 120));
		m_maximums.insert(make_pair(EBet::Column1, 200));
		m_maximums.insert(make_pair(EBet::Column2, 200));
		m_maximums.insert(make_pair(EBet::Column3, 200));
		m_maximums.insert(make_pair(EBet::Dozen1, 200));
		m_maximums.insert(make_pair(EBet::Dozen2, 200));
		m_maximums.insert(make_pair(EBet::Dozen3, 200));
		m_maximums.insert(make_pair(EBet::Red, 400));
		m_maximums.insert(make_pair(EBet::Black, 400));
		m_maximums.insert(make_pair(EBet::Even, 400));
		m_maximums.insert(make_pair(EBet::Odd, 400));
		m_maximums.insert(make_pair(EBet::High, 400));
		m_maximums.insert(make_pair(EBet::Low, 400));

		// calculate table max (maximum amount of chips possible)
		m_tablemax = 0;
		m_maxiter = m_maxbets.begin();

		for (auto btMax = m_maximums.begin(); btMax != m_maximums.end(); ++m_maxiter, ++btMax)
		{
			m_tablemax += m_maxiter->second * btMax->second;
		}

		// standard limit is 50 times Straightup limit
		auto iter = m_maximums.find(EBet::StraightUp);
		if (iter != m_maximums.end())
		{
			m_tablelimit = iter->second * 50;
		}
		else error_handler(error("iterator out of range"));
	}

	Table::~Table()
	{
		for (auto pair : m_fields)
		{
			delete pair.second;
		}
	}

	bool Table::check_limits(type_chip_container& chips, type_chip& chip)
	{
		auto limit = m_maximums.find(get<2>(*chip));
		if (limit == m_maximums.end())
		{
			error_handler(error("limit for this bet type not defined"));
		}
		uint16 current_bet = static_cast<uint16>(get<0>(*chip));

		for (auto iter : chips)
		{
			// we need to compare points, since there are 4 splits or corners inside a field.
			if (get<1>(*iter).equal(get<1>(*chip)))
			{
				current_bet += static_cast<uint16>(get<0>(*iter));
			}
		}

		if (current_bet > limit->second)
		{
			get<2>(*chip) = EBet::LIMIT_EXCEEDED;

			Gtk::Window* top_window = dynamic_cast<Gtk::Window*>(get_toplevel());

			if (top_window->get_is_toplevel())
			{
				Gtk::MessageDialog dialog(*top_window, "Information");
				dialog.set_secondary_text("Limit reached for this bet");
				dialog.set_position(Gtk::WIN_POS_CENTER);
				dialog.run();
			} // if is_toplevel
			else error_handler(error("get_toplevel did not return a top level window"));
			return true;
		}
		return false;
	}

#ifdef _MSC_VER
#pragma endregion begin

#pragma region
#endif // _MSC_VER

	void Table::on_signal_spin(uint16 result)
	{
		for (auto iter : m_fields)
		{
			iter.second->on_signal_spin(result);
		}
	}

	void Table::set_debug(bool debug) noexcept
	{
		for (auto pair : m_fields)
		{
			pair.second->set_debug(debug);
		}
	}

	void Table::set_table_max(const uint32& limit /*= 0*/)
	{
		Gtk::Window* top_window = dynamic_cast<Gtk::Window*>(get_toplevel());

		if (top_window->get_is_toplevel())
		{
			Gtk::MessageDialog dialog(*top_window, "Table limit");
			dialog.set_position(Gtk::WIN_POS_CENTER);

			if (limit > m_tablemax)
			{
				dialog.set_secondary_text("Limit too high");
				dialog.run();
				return;
			}

			auto iter = m_maximums.find(EBet::Red);
			if (iter != m_maximums.end())
			{
				if (limit < iter->second)
				{
					dialog.set_secondary_text("Limit can't be smaller than even oney bet");
					dialog.run();
				}
			}
			else
			{
				m_tablelimit = limit;
			}
		} // if is_toplevel
		else
		{
			error_handler(error("ERROR: get_toplevel did not return a top level window"));
		}
	}

	uint16 Table::get_limit(const EBet& name)
	{
		if ((m_maxiter = m_maximums.find(name)) == m_maximums.end())
		{
			error_handler(error("Table -> get_limit -> iterator out of range"));
		}
		return m_maxiter->second;
	}

	uint16 Table::get_minimum(const EMinimum & minimum)
	{
		auto iter = m_minimums.find(minimum);

		if (iter == m_minimums.end())
		{
			error_handler(error("Table -> get_minimum -> minimum not found"));
		}
		return iter->second;
	}

	void Table::set_minimum(const EMinimum& name, const uint16& minimum)
	{
		if (minimum > 1)
      {
         m_minimums.find(name)->second = minimum;
      }
      else
      {
         error_handler(error("Table -> set_minimum -> Bet minimum less then 1"));
      }
	}

	void Table::set_maximum(const EBet& name, const uint16& limit)
	{
		if ((m_maxiter = m_maximums.find(name)) != m_maximums.end())
      {
         m_maxiter->second = limit;
      }
      else
      {
         error_handler(error("Table -> set_maximum -> Iterator out of range"));
      }
	}

#ifdef _MSC_VER
#pragma endregion methods
#endif // _MSC_VER

} // namespace roulette
