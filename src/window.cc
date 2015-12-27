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
		m_BtnRebet("Rebet"),
		m_Btn_x2("X2"),
		m_BtnSpin("Spin"),
		m_BtnClear("Clear"),
		m_BtnClose("Close"),
		mp_engine(new Engine),
		mp_table(new Table),
		m_infobar(mp_engine, mp_table),
		m_Chip1(mp_engine, EChip::Chip1),
		m_Chip5(mp_engine, EChip::Chip5),
		m_Chip25(mp_engine, EChip::Chip25),
		m_Chip50(mp_engine, EChip::Chip50),
		m_Chip100(mp_engine, EChip::Chip100),
		m_Eraser(mp_engine, EChip::Eraser)
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
		m_VBoxArea.pack_start(*mp_table, Gtk::PACK_EXPAND_WIDGET);
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
		m_Controlset.pack_end(m_BtnRebet, Gtk::PACK_SHRINK);
		m_Controlset.pack_end(m_BtnSpin, Gtk::PACK_SHRINK);
		m_Controlset.pack_end(m_Btn_x2, Gtk::PACK_SHRINK);
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
		m_Btn_x2.signal_button_press_event().connect(sigc::mem_fun(*this, &Window::on_button_x2));
		m_BtnClear.signal_button_press_event().connect(sigc::mem_fun(*this, &Window::on_button_clear));
		m_BtnRebet.signal_button_press_event().connect(sigc::mem_fun(*this, &Window::on_button_rebet));

		// signals connecting objects constructed by window
		/// in this order
		mp_engine->signal_spin.connect(sigc::mem_fun(m_history, &History::set_result));
		mp_engine->signal_rebet.connect(sigc::mem_fun(m_infobar, &InfoBar::on_update));

		/// in this order
		mp_table->signal_clear_all.connect(sigc::mem_fun(*mp_engine, &Engine::clear_all_bets));
		mp_table->signal_clear_all.connect(
			sigc::bind( // bind nullptr, InfoBar does not use this argument
				sigc::mem_fun(m_infobar, &InfoBar::on_update), nullptr));

		/// in this order
		mp_table->signal_bet.connect(sigc::mem_fun(*mp_engine, &Engine::place_bet));
		mp_table->signal_bet.connect(sigc::mem_fun(m_infobar, &InfoBar::on_update));

		// debug options
		mp_engine->set_debug(true);
		mp_table->set_debug(true);
		m_Chip1.set_debug(true);
		m_Chip5.set_debug(true);
		m_Chip25.set_debug(true);
		m_Chip50.set_debug(true);
		//m_Chip100.set_debug(true);
		m_Eraser.set_debug(true);
	}

	roulette::Window::~Window()
	{
		delete mp_engine;
		delete mp_table;
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
		m_BtnRebet.set_sensitive(true);
		mp_engine->spin(mp_table->get_table_type());
		mp_table->signal_clear_all.emit();
		return true;
	}

	// sping 50 times
	bool Window::on_button_x2(GdkEventButton* /*button_event*/)
	{
		if (mp_engine->double_bets(mp_table))
		{
			Gtk::MessageDialog dialog(*this, "Information");
			dialog.set_secondary_text("Limit exceeded");
			dialog.set_position(Gtk::WIN_POS_CENTER);
			dialog.run();
			return false;
		}
		else
		{
			m_infobar.on_update(nullptr);
			return true;
		}
	}

	// clear all chips from the table
	bool Window::on_button_clear(GdkEventButton* /*button_event*/)
	{
		mp_table->signal_clear_all.emit();
		return true;
	}

	bool Window::on_button_rebet(GdkEventButton* /*button_event*/)
	{
		m_BtnRebet.set_sensitive(false);
		if (mp_engine->get_current_bet() > mp_engine->get_bankroll())
		{
			Gtk::MessageDialog dialog(*this, "Information");
			dialog.set_secondary_text("Not enough bankroll to rebet");
			dialog.set_position(Gtk::WIN_POS_CENTER);
			dialog.run();
			return false;
		}
		mp_table->signal_rebet.emit();
		mp_engine->rebet();
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
