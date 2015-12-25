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
//	main.cc
//
//	Defines the application entry point
// Defines common functions shared by most
// translation units
//
// TODO: pass values by reference in functions
//
///</summary>

// roulette
#include "pch.hh"
#include "main.hh"
#include "window.hh"

namespace roulette
{
	using std::find; // get_neighbor()
	using std::string; // load icons()
	using std::vector; // dnd_targets
	using boost::filesystem::exists; // load_icons()

	// chip pixbuf icons
	type_chip_icon icon1;
	type_chip_icon icon5;
	type_chip_icon icon25;
	type_chip_icon icon50;
	type_chip_icon icon100;
	type_chip_icon eraser;
	type_chip_icon app_icon;

	// load size x size version from the ico file
	static int chip_size = 32;

	const int format = 8;
	
	vector<Gtk::TargetEntry> dnd_targets;

	bool load_icons();

} // namespace

int main(int argc, char* argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "roulette.exe");

	if (roulette::load_icons())
	{
		roulette::Window* p_window = new roulette::Window(roulette::app_icon);

		if (p_window)
		{
			app->run(*p_window);
			delete p_window;
			return 0;
		}
		else return -1;
	}
	else return -2;
}

namespace roulette
{
	bool is_red(const unsigned number)
	{
		switch (number)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 9:
		case 12:
		case 14:
		case 16:
		case 18:
		case 19:
		case 21:
		case 23:
		case 25:
		case 27:
		case 30:
		case 32:
		case 34:
		case 36:
			return true;
		default:
			return false;
		}
	}

	bool is_black(const unsigned number)
	{
		if (is_green(number) || is_red(number))
			return false;
		else return(number && (number < 37));
	}

	bool is_green(const unsigned number)
	{
		if (number == 0 || number == 37)
			return true;
		else return false;
	}

	unsigned which_column(const unsigned number)
	{
		if (number % 3)
			return number % 3;
		else return 3;
	}

	unsigned which_column(EField field)
	{
		if (static_cast<unsigned>(field) % 3)
			return static_cast<unsigned>(field) % 3;
		else return 3;
	}

	unsigned which_dozen(const unsigned number)
	{
		if (number < 13)
			return 1;
		else if (number < 25)
			return 2;
		else return 3;
	}

	void set_chipsize(const int size)
	{
		chip_size = size;
	}

	int get_chipsize()
	{
		return chip_size;
	}

	bool load_icons()
	{
		bool success = true;
		string file_name = "Chip1.ico";
	
		exists(file_name) ? icon1 = Gdk::Pixbuf::create_from_file(file_name, chip_size, chip_size) : success = false;

		file_name = "Chip5.ico";
		exists(file_name) ? icon5 = Gdk::Pixbuf::create_from_file(file_name, chip_size, chip_size) : success = false;

		file_name = "Chip25.ico";
		exists(file_name) ? icon25 = Gdk::Pixbuf::create_from_file(file_name, chip_size, chip_size) : success = false;

		file_name = "Chip50.ico";
		exists(file_name) ? icon50 = Gdk::Pixbuf::create_from_file(file_name, chip_size, chip_size) : success = false;

		file_name = "Chip100.ico";
		exists(file_name) ? icon100 = Gdk::Pixbuf::create_from_file(file_name, chip_size, chip_size) : success = false;

		file_name = "eraser.ico";
		exists(file_name) ? eraser = Gdk::Pixbuf::create_from_file(file_name, chip_size, chip_size) : success = false;

		file_name = "roulette.ico";
		exists(file_name) ? app_icon = Gdk::Pixbuf::create_from_file(file_name, chip_size, chip_size) : success = false;

		return success;
	}

	type_chip_icon get_pixbuf(EChip ref)
	{
		switch (ref)
		{
		case EChip::Chip1:
			return icon1;
		case EChip::Chip5:
			return icon5;
		case EChip::Chip25:
			return icon25;
		case EChip::Chip50:
			return icon50;
		case EChip::Chip100:
			return icon100;
		case EChip::Eraser:
		default:
			return eraser;
		}
	}

	unsigned get_neighbor(const ETable table, const unsigned refNum, const unsigned position)
	{
		unsigned i = 0;
		static type_raw_set::const_iterator iter;

		switch (table)
		{
		case ETable::NoZero:
			iter = find(NoZeroWheel->begin(), NoZeroWheel->end(), refNum);
			while (i != position) // if i == position refNum is returned
			{ // if i != position then iterating.... position times
				if (position > 0) // positive position
				{
					++i;
					++iter;
					if (iter == NoZeroWheel->end())
						iter = NoZeroWheel->begin(); // return to begin and continue
				}
				else // negative position
				{
					if (iter == NoZeroWheel->begin() && i != position) //if begin is not what we want...
						iter = NoZeroWheel->end(); // then go to end
					--iter;
					--i;
				}
			}
			break;

		case ETable::American:
			iter = find(AmericanWheel->begin(), AmericanWheel->end(), refNum);
			while (i != position)
			{
				if (position > 0)
				{
					++i;
					++iter;
					if (iter == AmericanWheel->end())
						iter = AmericanWheel->begin();
				}
				else
				{
					if (iter == AmericanWheel->begin() && i != position)
						iter = AmericanWheel->end();
					--iter;
					--i;
				}
			}
			break;

		case ETable::French:
		case ETable::SingleImprisonment:
		case ETable::InfininiteImprisonment:
		case ETable::DoubleImprisonment:
		case ETable::TripleImprisonment:
		case ETable::European:
			iter = find(EuropeanWheel->begin(), EuropeanWheel->end(), refNum);
			while (i != position)
			{
				if (position > 0)
				{
					++i;
					++iter;
					if (iter == EuropeanWheel->end())
						iter = EuropeanWheel->begin();
				}
				else
				{
					if (iter == EuropeanWheel->begin() && i != position)
						iter = EuropeanWheel->end();
					--iter;
					--i;
				}
			}
			break;
		}
		return *iter;
	}

} // namespace roulette
