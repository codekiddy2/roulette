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
// TODO: add description
///</summary>

#include "pch.hh"
#define TU_TYPES_CC
#include "types.hh"

namespace roulette
{
	// Explicit instantiation definition
	// typedef-name cannot be used in explicit instantiation.
	template std::shared_ptr<Bet>; // type_bet
	template Glib::RefPtr<Gdk::Pixbuf>; // type_chip_icon
	template std::vector<Gtk::TargetEntry>; // type_dnd_targets
	template std::vector<std::shared_ptr<Bet>>; // type_bet_container
	template std::tuple<EChip, Gdk::Point, EBet>; // type_chip_tuple
	template std::shared_ptr<std::tuple<EChip, Gdk::Point, EBet>>; // type_chip
	template std::vector<std::shared_ptr<std::tuple<EChip, Gdk::Point, EBet>>>; // type_chip_container

	template std::vector<EBet>; // type_bet_list
	template std::map<EField, Field*>; // type_fields
	template std::map<EBet, uint16>; // type_max_container
	template std::map<EMinimum, uint16>; // type_min_container
	template Glib::RefPtr<Pango::Layout>; // type_layout

	template sigc::signal0<void>; // type_signal
	template sigc::signal1<void, uint16>; // type_signal_spin
	template sigc::signal1<void, std::shared_ptr<Bet>>; // type_signal_bet
	template sigc::signal2<void, const EField&, std::shared_ptr<std::tuple<EChip, Gdk::Point, EBet>>>; // type_signal_chip

	template std::vector<uint16>; // type_raw_set
	template std::shared_ptr<std::vector<uint16>>; // type_set

} // namespace roulette
