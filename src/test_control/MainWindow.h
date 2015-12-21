#pragma once
// MainWindow.h
// MainWindow class interface

#include "control.hh"

#include <gtkmm\hvbox.h>
#include <gtkmm\window.h>
#include <gtkmm\button.h>
#include <gtkmm\buttonbox.h>


class MainWindow final :
	public Gtk::Window
{
public:
	// constructors
	MainWindow();
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;

private:
	// members
	Gtk::VBox m_vbox;
	Gtk::HBox m_hbox;
	Gtk::Button m_btn_close;
	Gtk::ButtonBox m_btn_box;

	roulette::Control m_control;

	// methods
	void on_button_close();
};

