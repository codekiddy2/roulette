#pragma once

#include <gtkmm.h>
#include "chip.hh"

class Chipset final
	: public Gtk::HBox
{
public:
	Chipset();

private:
	Gtk::HBox mChips;
	Chip mChip1, mChip5, mChip25, mChip50, mChip100;
};

