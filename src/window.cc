
#include "pch.hh"
#include "window.hh"
#include "sets.hh"

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


Window::Window() :
	mBackground("rgb(0, 102, 0)"),
	mTable(mBackground),
	mChipset(mBackground),
	mControlset(mBackground),
	mHistory(),
	mFrameHistory("History"),
	mFrameBets("Bets")
{
	// Window options
	set_title("roulette");
	set_size_request(500, 300);
	set_position(Gtk::WIN_POS_CENTER);

	if (boost::filesystem::exists("roulette.ico"))
	{
		refIcon = Gdk::Pixbuf::create_from_file("roulette.ico");
		set_icon(refIcon);
	}

	// packing
	add(mVBoxTop);
	mVBoxTop.pack_start(mHBoxArea);
	mVBoxTop.pack_start(mHboxControls);

	// history widnow
	mFrameHistory.add(mHistory);
	mHBoxArea.pack_start(mFrameHistory, Gtk::PACK_EXPAND_WIDGET);

	// Table
	mFrameBets.add(mTable);
	mHBoxArea.pack_start(mFrameBets, Gtk::PACK_EXPAND_WIDGET);

	// buttons
	mHboxControls.pack_end(mControlset, Gtk::PACK_SHRINK);

	// buttonbox properties
	mControlset.set_spacing(0);
	mControlset.set_border_width(0);
	mControlset.set_layout(Gtk::BUTTONBOX_END);

	// chipset
	mHboxControls.pack_end(mChipset, Gtk::PACK_EXPAND_WIDGET);

	mChipset.set_spacing(0);
	mChipset.set_border_width(0);
	//mChipset.set_layout(Gtk::BUTTONBOX_END);

	show_all();

	// signals
	mControlset.mBtnClose.signal_button_press_event().connect(sigc::mem_fun(*this, &Window::on_button_close));
	mControlset.mBtnSpin.signal_button_press_event().connect(sigc::mem_fun(*this, &Window::on_button_spin));
	mControlset.mBtnSpin50.signal_button_press_event().connect(sigc::mem_fun(*this, &Window::on_button_spin50));
}

bool Window::on_button_close(GdkEventButton* /*button_event*/)
{
	close();
	return true;
}

bool Window::on_button_spin(GdkEventButton* /*button_event*/)
{
	using namespace std;
	using namespace boost::random;


	static random_device rng;
	static uniform_smallint<> dist(0, 38);

	int result = dist(rng);
	string red, black, green, newline = "\n", tab = "\t";


	if (result == 0)
	{
		green.append(to_string(result) + tab);
	}
	else if (IsRed(result))
	{
		red.append(to_string(result) + tab);
	}
	else // black result :)
	{
		black.append(to_string(result) + tab);
	}

	green.append(newline);
	green.append(mHistory.refGreenBuffer->get_text());

	red.append(newline);
	red.append(mHistory.refRedBuffer->get_text());

	black.append(newline);
	black.append(mHistory.refBlackBuffer->get_text());

	mHistory.refGreenBuffer->set_text(green);
	mHistory.refRedBuffer->set_text(red);
	mHistory.refBlackBuffer->set_text(black);

	mHistory.apply_tags();

	return true;
}

bool Window::on_button_spin50(GdkEventButton* button_event)
{
	for (size_t i = 0; i < 50; i++)
	{
		on_button_spin(button_event);
	}

	return true;
}