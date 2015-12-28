
#ifndef FIELD_HH
#define FIELD_HH 1

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
//	field.hh
//
//	Declaration of Field class
//
// Table is composed of fields, majority of the logic is made
// by fields, table just adds them together and connects signals
//
///</summary>

// roulette
#include "error.hh"
#include "main.hh"

// gtkmm
#include <gtkmm/widget.h>
#include <gtkmm/selectiondata.h>
#include <glibmm/refptr.h>
#include <pangomm/layout.h>
#include <pangomm/fontdescription.h>
#include <gdkmm/rgba.h>
#include <gdkmm/dragcontext.h>
#include <gdkmm/window.h>
#include <gdkmm/rectangle.h> // Gtk::Allocation
#include <cairomm/refptr.h>
#include <cairomm/context.h>
#include <gdkmm/event.h> // GdkEventButton
#include <gtkmm/tooltip.h>

namespace roulette
{

#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER

	// forward declarations
	class Table;

	class Field final : 
		public Gtk::Widget,
		public IErrorHandler
	{
	public:
		// constructors
		Field(EField field_index, Table* p_table);

		// signals emited by number fields only
		type_signal_chip signal_bet_top;
		type_signal_chip signal_bet_bottom;
		type_signal_chip signal_bet_left;
		type_signal_chip signal_bet_right;
		type_signal_chip signal_bet_top_right;
		type_signal_chip signal_bet_top_left;
		type_signal_chip signal_bet_bottom_right;
		type_signal_chip signal_bet_bottom_left;

		// sinals emited by zero and dozens to number fields
		type_signal_chip signal_bet_split1;
		type_signal_chip signal_bet_split2;
		type_signal_chip signal_bet_split3;

		type_signal_chip signal_bet_street1; // used by dozens and zero only
		type_signal_chip signal_bet_street2; // used by dozens and zero only
		type_signal_chip signal_bet_street3; // used by dozens only
		type_signal_chip signal_bet_street4; // used by dozens only

		type_signal_chip signal_bet_basket; // used by zero and dozen1 only
		
		// signals used by dozens only
		type_signal_chip signal_bet_line1; // used by dozen2 and dozen 3 only
		type_signal_chip signal_bet_line2;
		type_signal_chip signal_bet_line3;
		type_signal_chip signal_bet_line4;
		type_signal_chip signal_bet_line5; // not used by dozen1 and dozen2 only

		// methods
		void on_signal_rebet();
		inline const EField get_index() const noexcept;
		inline void on_signal_spin(uint16 result) noexcept;

		// signal handlers
		void on_signal_bet_bottom(const EField& sender, type_chip chip);
		void on_signal_bet_top(const EField& sender, type_chip chip);
		void on_signal_bet_left(const EField& sender, type_chip chip);
		void on_signal_bet_right(const EField& sender, type_chip chip);
		void on_signal_bet_top_right(const EField& sender, type_chip chip);
		void on_signal_bet_top_left(const EField& sender, type_chip chip);
		void on_signal_bet_bottom_right(const EField& sender, type_chip chip);
		void on_signal_bet_bottom_left(const EField& sender, type_chip chip);

	protected:
		// overrides:
		Gtk::SizeRequestMode get_request_mode_vfunc() const override;
		void get_preferred_width_vfunc(int& minimum_width, int& natural_width) const override;
		void get_preferred_height_for_width_vfunc(int width, int& minimum_height, int& natural_height) const override;
		void get_preferred_height_vfunc(int& minimum_height, int& natural_height) const override;
		void get_preferred_width_for_height_vfunc(int height, int& minimum_width, int& natural_width) const override;
		void on_size_allocate(Gtk::Allocation& allocation) override;
		void on_map() override;
		void on_unmap() override;
		void on_realize() override;
		void on_unrealize() override;
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

		// dnd overrides
		bool on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint time) override;
		bool on_drag_drop(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint time) override;
		void on_drag_leave(const Glib::RefPtr<Gdk::DragContext>& context, guint time) override;
		void on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
			int x, int y, const Gtk::SelectionData& selection_data, guint info, guint time) override;

		// members
		Glib::RefPtr<Gdk::Window> refGdkWindow;

	private:
		// methods
		void clear_all();
		void clear(Gdk::Point& chip_point);
		void calculate_points(type_chip chip, bool emit = true);
		bool on_clicked(GdkEventButton* button_event);
		void assign_apperance(EField index);
		void draw_text(const Cairo::RefPtr<Cairo::Context>& cr, int field_width, int field_height);
		void place_chip(type_chip chip);
		bool on_query_tooltip(int x, int y, bool keyboard_tooltip, const Glib::RefPtr<Gtk::Tooltip>& tooltip);

		// members
		type_chip_container m_chips;
		type_chip_container m_chips_saved;
		Pango::FontDescription m_font;
		type_layout m_layout;

		/// begin initializer list
		Gdk::RGBA m_background;
		Table* mp_table;
		EField m_index;
		/// end initializer list
		
		// deleted
		Field(const Field&) = delete;
		Field(const Field&&) = delete;
		Field& operator=(const Field&) = delete;
		Field& operator=(const Field&&) = delete;
	};

#ifdef _MSC_VER
#pragma endregion begin

#pragma region
#endif // _MSC_VER

	const EField Field::get_index() const noexcept
	{
		return m_index;
	}

	void Field::on_signal_spin(uint16 /*result*/) noexcept
	{
		m_chips_saved = m_chips;
	}

#ifdef _MSC_VER
#pragma endregion inlines
#endif // _MSC_VER

} // namespace roulette

#endif // ! FIELD_HH
