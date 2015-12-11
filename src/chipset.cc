
#include "stdafx.h"

#include "chipset.hh"

Chipset::Chipset() :
	mChip1("chip1.ico"),
	mChip5("chip5.ico"),
	mChip25("chip25.ico"),
	mChip50("chip50.ico"),
	mChip100("chip100.ico")
{
	add(mChips);

	mChips.pack_end(mChip1);
	mChips.pack_end(mChip5);
	mChips.pack_end(mChip25);
	mChips.pack_end(mChip50);
	mChips.pack_end(mChip100);

	//show_all();
}
