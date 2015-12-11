#include "stdafx.h"
#include "table.hpp"
#include "field.hpp"


Table::Table()
{
	add(mGrid);

	// zero
	mFields.push_back(new Field(0));
	mGrid.attach(*mFields.back(), 0, 0, 1, 3);

	// dummy
	mFields.push_back(new Field(""));
	mGrid.attach(*mFields.back(), 0, 3, 1, 2);

	// column 3
	for (int i = 3, col = 1; i <= 36; i += 3, ++col)
	{
		mFields.push_back(new Field(i));
		mGrid.attach(*mFields.back(), col, 0, 1, 1);
	}

	mFields.push_back(new Field("2 to 1"));
	mGrid.attach(*mFields.back(), 13, 0, 1, 1);
	
	// column 2
	for (int i = 2, col = 1; i <= 35; i += 3, ++col)
	{
		mFields.push_back(new Field(i));
		mGrid.attach(*mFields.back(), col, 1, 1, 1);
	}

	mFields.push_back(new Field("2 to 1"));
	mGrid.attach(*mFields.back(), 13, 1, 1, 1);

	// column 1
	for (int i = 1, col = 1; i <= 34; i += 3, ++col)
	{
		mFields.push_back(new Field(i));
		mGrid.attach(*mFields.back(), col, 2, 1, 1);
	}

	mFields.push_back(new Field("2 to 1"));
	mGrid.attach(*mFields.back(), 13, 2, 1, 1);

	// dozens
	mFields.push_back(new Field("1st 12"));
	mGrid.attach(*mFields.back(), 1, 3, 4, 1);

	mFields.push_back(new Field("2nd 12"));
	mGrid.attach(*mFields.back(), 5, 3, 4, 1);

	mFields.push_back(new Field("3rd 12"));
	mGrid.attach(*mFields.back(), 9, 3, 4, 1);

	// dummy
	mFields.push_back(new Field(""));
	mGrid.attach(*mFields.back(), 13, 3, 1, 2);


	// low/high red/black high/low
	mFields.push_back(new Field("1 to 18"));
	mGrid.attach(*mFields.back(), 1, 4, 2, 1);

	mFields.push_back(new Field("EVEN"));
	mGrid.attach(*mFields.back(), 3, 4, 2, 1);

	mFields.push_back(new Field("RED"));
	mGrid.attach(*mFields.back(), 5, 4, 2, 1);

	mFields.push_back(new Field("BLACK"));
	mGrid.attach(*mFields.back(), 7, 4, 2, 1);

	mFields.push_back(new Field("ODD"));
	mGrid.attach(*mFields.back(), 9, 4, 2, 1);

	mFields.push_back(new Field("19 to 36"));
	mGrid.attach(*mFields.back(), 11, 4, 2, 1);
}

Table::~Table()
{
	for (size_t i = 0; i <= mFields.size(); i++)
	{
		delete mFields.at(i);
	}
}