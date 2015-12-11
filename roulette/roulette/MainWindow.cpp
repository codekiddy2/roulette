// MainWindow.cpp
// MainWindow class definition

#include "stdafx.h"
#include "MainWindow.h"
#include "NumberSets.hpp"

#include <boost/filesystem.hpp>



MainWindow::MainWindow() :
	mBtnClose("Close"),
	mBtnSpin("Spin"),
	mBtnSpin50("Spin 50x"),
	mFrameHistory("History"),
	mFrameBets("Bets")
{
	// MainWindow options
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
	mFrameHistory.add(mHistoryWindow);
	mHBoxArea.pack_start(mFrameHistory, Gtk::PACK_EXPAND_WIDGET);

	// Table
	mFrameBets.add(mTable);
	mHBoxArea.pack_start(mFrameBets, Gtk::PACK_EXPAND_WIDGET);

	// buttons
	mHboxControls.pack_end(mBtnBox, Gtk::PACK_SHRINK);
	mBtnBox.pack_end(mBtnClose, Gtk::PACK_SHRINK);
	mBtnBox.pack_end(mBtnSpin, Gtk::PACK_SHRINK);
	mBtnBox.pack_end(mBtnSpin50, Gtk::PACK_SHRINK);

	// buttonbox properties
	mBtnBox.set_spacing(5);
	mBtnBox.set_border_width(5);
	mBtnBox.set_layout(Gtk::BUTTONBOX_END);

	// chipset
	mHboxControls.pack_end(mChipset, Gtk::PACK_EXPAND_WIDGET);

	show_all();

	// signals
	mBtnClose.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_close));
	mBtnSpin.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_spin));
	mBtnSpin50.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_spin50));
}

void MainWindow::on_button_close()
{
	close();
}

void MainWindow::on_button_spin()
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
	green.append(mHistoryWindow.refGreenBuffer->get_text());

	red.append(newline);
	red.append(mHistoryWindow.refRedBuffer->get_text());

	black.append(newline);
	black.append(mHistoryWindow.refBlackBuffer->get_text());

	mHistoryWindow.refGreenBuffer->set_text(green);
	mHistoryWindow.refRedBuffer->set_text(red);
	mHistoryWindow.refBlackBuffer->set_text(black);

	mHistoryWindow.apply_tags();
}

void MainWindow::on_button_spin50()
{
	for (size_t i = 0; i < 50; i++)
	{
		on_button_spin();
	}
}