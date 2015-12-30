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
#include "pragmas.hh"
#define TU_TYPES_CC
#include "types.hh"

	// Explicit instantiation definition
	// typedef-name cannot be used in explicit instantiation.
	template class Glib::RefPtr<Gdk::Pixbuf>; // type_chip_icon
	template class Glib::RefPtr<Pango::Layout>; // type_layout

#ifndef _MSC_VER // HACK: No Explicit instantiation due to warning C4661
	template class std::map<roulette::ELayout, roulette::type_layout>; // type_layout_container
#endif // _MSC_VER

#ifndef __GNUC__ // HACK: g++ says "undefined reference"
	template class std::vector<roulette::uint16>; // type_raw_set
	template class std::shared_ptr<roulette::type_raw_set>; // type_set
#endif // __GNUC__

	template class std::vector<Gtk::TargetEntry>; // type_dnd_targets
	template class std::shared_ptr<roulette::Bet>; // type_bet
	template class std::vector<roulette::type_bet>; // type_bet_container

#if GDKMM_MINOR_VERSION != 18 // HACK: probably a bug in 3.0.18 with deleted copy asignment
	template class std::tuple<roulette::EChip, Gdk::Point, roulette::EBet>; // type_chip_tuple
#endif // GDKMM_MINOR_VERSION

	template class std::shared_ptr<roulette::type_chip_tuple>; // type_chip
	template class std::vector<roulette::type_chip>; // type_chip_container

	template class std::vector<roulette::EBet>; // type_bet_list
	template class std::map<roulette::EField, roulette::Field*>; // type_fields
	template class std::map<roulette::EBet, roulette::uint16>; // type_max_container
	template class std::map<roulette::EMinimum, roulette::uint16>; // type_min_container

	template class sigc::signal0<void>; // type_signal
	template class sigc::signal1<void, roulette::uint16>; // type_signal_spin
	template class sigc::signal1<void, roulette::type_bet>; // type_signal_bet
	template class sigc::signal2<void, const roulette::EField&, roulette::type_chip>; // type_signal_chip
