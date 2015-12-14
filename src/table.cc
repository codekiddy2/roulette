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
#include "table.hh"
#include "chipset.hh"
#include "field.hh"

using std::cerr;
using std::endl;
using std::cout;

Table::Table(const ETable table_type) :
	mTableType(table_type)
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

	// zero
	mFields.push_back(new Field(0, this));
	attach(*mFields.back(), 0, 0, 1, 3);

	// dummy
	mFields.push_back(new Field("", this));
	attach(*mFields.back(), 0, 3, 1, 2);

	// column 3
	for (int i = 3, col = 1; i <= 36; i += 3, ++col)
	{
		mFields.push_back(new Field(i, this));
		attach(*mFields.back(), col, 0, 1, 1);
	}

	mFields.push_back(new Field("2 to 1", this));
	attach(*mFields.back(), 13, 0, 1, 1);
	
	// column 2
	for (int i = 2, col = 1; i <= 35; i += 3, ++col)
	{
		mFields.push_back(new Field(i, this));
		attach(*mFields.back(), col, 1, 1, 1);
	}

	mFields.push_back(new Field("2 to 1", this));
	attach(*mFields.back(), 13, 1, 1, 1);

	// column 1
	for (int i = 1, col = 1; i <= 34; i += 3, ++col)
	{
		mFields.push_back(new Field(i, this));
		attach(*mFields.back(), col, 2, 1, 1);
	}

	mFields.push_back(new Field("2 to 1", this));
	attach(*mFields.back(), 13, 2, 1, 1);

	// dozens
	mFields.push_back(new Field("1st 12", this));
	attach(*mFields.back(), 1, 3, 4, 1);

	mFields.push_back(new Field("2nd 12", this));
	attach(*mFields.back(), 5, 3, 4, 1);

	mFields.push_back(new Field("3rd 12", this));
	attach(*mFields.back(), 9, 3, 4, 1);

	// dummy
	mFields.push_back(new Field("", this));
	attach(*mFields.back(), 13, 3, 1, 2);


	// low/high red/black high/low
	mFields.push_back(new Field("1 to 18", this));
	attach(*mFields.back(), 1, 4, 2, 1);

	mFields.push_back(new Field("EVEN", this));
	attach(*mFields.back(), 3, 4, 2, 1);

	mFields.push_back(new Field("RED", this));
	attach(*mFields.back(), 5, 4, 2, 1);

	mFields.push_back(new Field("BLACK", this));
	attach(*mFields.back(), 7, 4, 2, 1);

	mFields.push_back(new Field("ODD", this));
	attach(*mFields.back(), 9, 4, 2, 1);

	mFields.push_back(new Field("19 to 36", this));
	attach(*mFields.back(), 11, 4, 2, 1);
}

Table::~Table()
{
	for (size_t i = 0; i <= mFields.size(); i++)
	{
		delete mFields.at(i);
	}
}

ETable Table::get_table_type()
{
	return mTableType;
}
