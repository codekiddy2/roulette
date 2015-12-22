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
///</summary>

#include "pch.hh"
#include "sets.hh"
#include "window.hh"

namespace roulette
{
	// dummy control is used to fill the area at the bottom
	class Dummy :
		public BaseControl
	{
	public:
		// constructors
		Dummy();

	private:
		// overrides
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

		// deleted
		Dummy(const Dummy&) = delete;
		Dummy(const Dummy&&) = delete;
		Dummy& operator=(const Dummy&) = delete;
		Dummy& operator=(const Dummy&&) = delete;
	};

	Window::Window(Glib::RefPtr<Gdk::Pixbuf> refIcon) :
		IErrorHandler("Window"),
		m_Chip1(EChip::Chip1),
		m_Chip5(EChip::Chip5),
		m_Chip25(EChip::Chip25),
		m_Chip50(EChip::Chip50),
		m_Chip100(EChip::Chip100),
		m_Eraser(EChip::Eraser),
		m_BtnClose("Close"),
		m_BtnSpin("Spin"),
		m_BtnSpin50("Spin 50x"),
		m_BtnClear("Clear"),
		mp_engine(new Engine),
		m_infobar(mp_engine)
	{
		// Window options
		set_title("roulette");
		set_size_request(500, 300);
		set_position(Gtk::WIN_POS_CENTER);
		set_icon(refIcon);

		// begin packing
		add(m_HBoxTop);

		// PACKING from left to right
		m_HBoxTop.pack_start(m_history, Gtk::PACK_SHRINK);
		m_HBoxTop.pack_start(m_VBoxArea, Gtk::PACK_EXPAND_WIDGET);
		m_HBoxTop.show_all();

		// PACKING from top to bottom
		m_VBoxArea.pack_start(m_infobar, Gtk::PACK_SHRINK);
		m_VBoxArea.pack_start(m_table, Gtk::PACK_EXPAND_WIDGET);
		m_VBoxArea.pack_start(m_HBoxControls, Gtk::PACK_SHRINK);
		m_VBoxArea.show_all();

		// PACKING from right to left
		m_HBoxControls.pack_end(m_Controlset, Gtk::PACK_SHRINK); // Controlset
		m_HBoxControls.pack_end(m_Chipset, Gtk::PACK_SHRINK); // chipset
		Dummy* p_dummy = Gtk::manage(new Dummy);
		m_HBoxControls.add(*p_dummy);
		m_HBoxControls.show_all();

		// Controlset properties
		m_Controlset.set_spacing(0);
		m_Controlset.set_border_width(0);
		m_Controlset.pack_end(m_BtnClear, Gtk::PACK_SHRINK);
		m_Controlset.pack_end(m_BtnSpin, Gtk::PACK_SHRINK);
		m_Controlset.pack_end(m_BtnSpin50, Gtk::PACK_SHRINK);
		m_Controlset.pack_end(m_BtnClose, Gtk::PACK_SHRINK);
		m_Controlset.show_all();

		// Chipset properties
		m_Chipset.set_spacing(0);
		m_Chipset.set_border_width(0);
		m_Chipset.pack_end(m_Eraser, Gtk::PACK_SHRINK);
		m_Chipset.pack_end(m_Chip1, Gtk::PACK_SHRINK);
		m_Chipset.pack_end(m_Chip5, Gtk::PACK_SHRINK);
		m_Chipset.pack_end(m_Chip25, Gtk::PACK_SHRINK);
		m_Chipset.pack_end(m_Chip50, Gtk::PACK_SHRINK);
		m_Chipset.pack_end(m_Chip100, Gtk::PACK_SHRINK);
		m_Chipset.show_all();

		// signals for this window
		m_BtnClose.signal_button_press_event().connect(sigc::mem_fun(*this, &Window::on_button_close));
		m_BtnSpin.signal_button_press_event().connect(sigc::mem_fun(*this, &Window::on_button_spin));
		m_BtnSpin50.signal_button_press_event().connect(sigc::mem_fun(*this, &Window::on_button_spin50));
		m_BtnClear.signal_button_press_event().connect(sigc::mem_fun(*this, &Window::on_button_clear));

		// signals connecting objects constructed by window
		mp_engine->signal_spin.connect(sigc::mem_fun(m_history, &History::set_result));
		m_table.signal_clear_all.connect(sigc::mem_fun(*mp_engine, &Engine::clear_all_bets));
		m_table.signal_bet.connect(sigc::mem_fun(*mp_engine, &Engine::place_bet));
		m_table.signal_bet.connect(sigc::mem_fun(m_infobar, &InfoBar::on_signal_bet));

		// engine options
		mp_engine->set_debug(true);
	}

	roulette::Window::~Window()
	{
		delete mp_engine;
	}

	// close app
	bool Window::on_button_close(GdkEventButton* /*button_event*/)
	{
		close();
		return true;
	}

	// spin single number
	bool Window::on_button_spin(GdkEventButton* /*button_event*/)
	{
		mp_engine->spin(m_table.get_table_type());
		return true;
	}

	// sping 50 times
	bool Window::on_button_spin50(GdkEventButton* button_event)
	{
		for (size_t i = 0; i < 50; i++)
		{
			on_button_spin(button_event);
		}
		return true;
	}

	// clear all chips from the table
	bool Window::on_button_clear(GdkEventButton* /*button_event*/)
	{
		m_table.signal_clear_all.emit();
		return true;
	}

	Dummy::Dummy() :
		BaseControl("Dummy")
	{

	}

	// Draw on the supplied Cairo::Context.
	bool Dummy::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
	{
		// paint the background
		Gdk::Cairo::set_source_rgba(cr, Color::get_background_color());
		cr->paint();

		return true;
	}

} // namespace roulette
