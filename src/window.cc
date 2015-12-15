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
//	window.cc
//
//	Definition of Window class
//
//	TODO: add description
//
///</summary>

#include "pch.hh"
#include "window.hh"
#include "sets.hh"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using namespace roulette;

Window::Window(Glib::RefPtr<Gdk::Pixbuf> refIcon) :
	mHistory(new History),
	mEngine(mHistory),
	mFrameHistory("History"),
	mFrameBets("Bets")
{
	// Window options
	int width = 500;
	int height = 300;

	set_title("roulette");
	set_size_request(width, height);
	set_position(Gtk::WIN_POS_CENTER);
	set_icon(refIcon);

	// begin packing
	add(mHBoxTop);
	Gdk::RGBA background("rgb(0, 102, 0)"); // green

	// PACKING from left to right
	mHBoxTop.pack_start(mFrameHistory, Gtk::PACK_SHRINK); // history widnow
	mFrameHistory.add(*mHistory);
	mFrameHistory.set_size_request(width / 5, 0);
	mHBoxTop.pack_start(mVBoxArea, Gtk::PACK_EXPAND_WIDGET);

	// PACKING from top to bottom
	mVBoxArea.pack_start(mFrameBets, Gtk::PACK_EXPAND_WIDGET); // Table
	mFrameBets.add(mTable);
	mVBoxArea.pack_start(mHBoxControls, Gtk::PACK_SHRINK);
	mHBoxControls.override_background_color(background); // TODO: temporary background color
	
	// PACKING from right to left
	mHBoxControls.pack_end(mControlset, Gtk::PACK_SHRINK); // Controlset
	Control::set_background_color(background);
	mHBoxControls.pack_end(mChipset, Gtk::PACK_SHRINK); // chipset
	Chip::set_background_color(background);
	
	// Controlset properties
	mControlset.set_spacing(0);
	mControlset.set_border_width(0);
	//mControlset.set_layout(Gtk::BUTTONBOX_END);

	// Chipset properties
	mChipset.set_spacing(0);
	mChipset.set_border_width(0);

	show_all();

	// temp
	mTable.PrintProperties();

	// signals
	mControlset.mBtnClose.signal_button_press_event().connect(sigc::mem_fun(*this, &Window::on_button_close));
	mControlset.mBtnSpin.signal_button_press_event().connect(sigc::mem_fun(*this, &Window::on_button_spin));
	mControlset.mBtnSpin50.signal_button_press_event().connect(sigc::mem_fun(*this, &Window::on_button_spin50));
	mControlset.mBtnClear.signal_button_press_event().connect(sigc::mem_fun(*this, &Window::on_button_clear));
}

Window::~Window()
{
	delete mHistory;
}

bool Window::on_button_close(GdkEventButton* /*button_event*/)
{
	close();
	return true;
}

bool Window::on_button_spin(GdkEventButton* /*button_event*/)
{

	mEngine.spin(mTable.get_table_type());
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

bool Window::on_button_clear(GdkEventButton* /*button_event*/)
{
	mTable.signal_clear.emit();
	return true;
}
