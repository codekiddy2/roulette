#pragma once
// MainWindow.h
// MainWindow class interface

#include <gtkmm/gtkmm.h>
#include "History.hpp"
#include "table.hpp"
#include "chipset.hh"

class MainWindow final :
	public Gtk::Window
{
public:
	// constructors
	MainWindow();
	MainWindow(const MainWindow&) = delete;
	MainWindow(const MainWindow&&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&&) = delete;

private:
	// members
	Gtk::VBox mVBoxTop;
	Gtk::HBox mHBoxArea, mHboxControls;
	Gtk::ButtonBox mBtnBox;
	Glib::RefPtr<Gdk::Pixbuf> refIcon;
	Table mTable;
	Chipset mChipset;

/// in order of initializer list
	Gtk::Button mBtnClose;
	Gtk::Button mBtnSpin;
	Gtk::Button mBtnSpin50;
	Gtk::Frame mFrameHistory, mFrameBets;
/// end of initializer list

	HistoryWindow mHistoryWindow;

	// methods
	void on_button_close();
	void on_button_spin();
	void on_button_spin50();
};

