
#ifndef CHIP_HH
#define CHIP_HH 1

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
//	chip.hh
//
//	Declaration of Bet class
//
//	Chips are used as a drag source to be drawn on the table
// during construction their value is associated with dnd target entry
//
///</summary>

// roulette
#include "base_control.hh"

namespace roulette
{
	// forward declarations
	class Engine;
	enum class EChip : unsigned;

	class Chip final : 
		public BaseControl
	{
	public:
		// constructors
		Chip(Engine* p_engine, const EChip chip_value);

	protected:
		// Overrides from base_control
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

		// dnd
		void on_drag_begin(const Glib::RefPtr< Gdk::DragContext >& context) override;
		void on_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context,
			Gtk::SelectionData& selection_data, guint info, guint time) override;
		void on_drag_end(const Glib::RefPtr< Gdk::DragContext >& context) override;

	private:
		/// begin initializer list
		unsigned m_value;
		Engine* mp_engine;
		Glib::RefPtr<Gdk::Pixbuf> refIcon;
		/// end initializer list

		// deleted
		Chip(const Chip&) = delete;
		Chip(const Chip&&) = delete;
		Chip& operator=(const Chip&) = delete;
		Chip& operator=(const Chip&&) = delete;
	};

} // namespace roulette

#endif // ! CHIP_HH
