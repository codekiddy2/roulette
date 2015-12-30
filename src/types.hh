
#ifndef TYPES_HH
#define TYPES_HH 1

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

// std
#include <map>
#include <tuple>
#include <vector>
#include <memory>
#include <cstdint>

// gtkmm
#include <sigc++/signal.h>
#include <gdkmm/types.h> // Gdk::Point
#include <glibmm/refptr.h>
#include <gdkmm/pixbuf.h>
#include <pangomm/layout.h>
#include <gtkmm/targetentry.h>

namespace roulette
{
	// preffered integral types
	typedef std::uint_least8_t uint8;
	typedef std::uint_least16_t uint16; // used
	typedef std::uint_least32_t uint32; // used
	typedef std::uint_least64_t uint64;

	typedef std::int_least8_t int8;
	typedef std::int_least16_t int16;
	typedef std::int_least32_t int32;
	typedef std::int_least64_t int64;

	// forward declarations
	class Bet;
	class Field;
	enum class EBet : uint16;
	enum class EChip : uint16;
	enum class ETable : uint16;
	enum class EField : uint16;
	enum class ELayout : uint16;
	enum class EMinimum : uint16;

	// type declaring a pixbuf icon for a chip
	typedef Glib::RefPtr<Gdk::Pixbuf> type_chip_icon;

	// type declaring a pango layout (used by Field)
	typedef Glib::RefPtr<Pango::Layout> type_layout;

	// type declaring layout container
	typedef std::map<ELayout, type_layout> type_layout_container;

	// single type declaring a set of numbers in roulette
	// must be vector to preserve numbers order and avoid sorting
	typedef const std::vector<uint16> type_raw_set;

	// shared pointer to the const set is shared between objects
	typedef std::shared_ptr<type_raw_set> type_set;

	// type declaring drag and drop targets and sources
	typedef std::vector<Gtk::TargetEntry> type_dnd_targets;

	// type declaring a bet
	typedef std::shared_ptr<Bet> type_bet;

	// container type to store bets
	typedef std::vector<type_bet> type_bet_container;

	// type declaring a tuple which defines a chip
	typedef std::tuple<EChip, Gdk::Point, EBet> type_chip_tuple;

	// type declaring a final chip type
	typedef std::shared_ptr<type_chip_tuple> type_chip;

	// type declaring a container of chips
	typedef std::vector<type_chip> type_chip_container;

	// type declaring list of bet for table (used by Table)
	typedef std::vector<EBet> type_bet_list;

	// type declaring table fields (used by Table)
	typedef std::map<EField, Field*> type_fields;

	// type declaring table maximums (used by Table)
	typedef std::map<EBet, uint16> type_max_container;

	// type declaring table minimums (used by Table)
	typedef std::map<EMinimum, uint16> type_min_container;

	// type declaring an empty signal (used by Table)
	typedef sigc::signal0<void> type_signal;

	// type declaring a spin signal (used by Engine)
	typedef sigc::signal1<void, uint16> type_signal_spin;

	// type signaling a bet (used by Table and Engine)
	typedef sigc::signal1<void, type_bet> type_signal_bet;

	// type declaring chip drawing signal (used by Field)
	typedef sigc::signal2<void, const EField&, type_chip> type_signal_chip;

} // namespace roulette

#ifndef TU_TYPES_CC
    // Explicit instantiation declaration
    // typedef-name cannot be used in explicit instantiation.
	extern template class Glib::RefPtr<Gdk::Pixbuf>; // type_chip_icon
	extern template class Glib::RefPtr<Pango::Layout>; // type_layout

#ifndef _MSC_VER // HACK: No Explicit instantiation due to warning C4661
	extern template class std::map<roulette::ELayout, roulette::type_layout>; // type_layout_container
#endif

#ifndef __GNUC__ // HACK: g++ says "undefined reference"
	extern template class std::vector<roulette::uint16>; // type_raw_set
	extern template class std::shared_ptr<roulette::type_raw_set>; // type_set
#endif // __GNUC__

	extern template class std::vector<Gtk::TargetEntry>; // type_dnd_targets
	extern template class std::shared_ptr<roulette::Bet>; // type_bet
	extern template class std::vector<roulette::type_bet>; // type_bet_container

#if GDKMM_MINOR_VERSION != 18 // HACK: probably a bug in 3.0.18 with deleted copy asignment
	extern template class std::tuple<roulette::EChip, Gdk::Point, roulette::EBet>; // type_chip_tuple
#endif // GDKMM_MINOR_VERSION

	extern template class std::shared_ptr<roulette::type_chip_tuple>; // type_chip
	extern template class std::vector<roulette::type_chip>; // type_chip_container

	extern template class std::vector<roulette::EBet>; // type_bet_list
	extern template class std::map<roulette::EField, roulette::Field*>; // type_fields
	extern template class std::map<roulette::EBet, roulette::uint16>; // type_max_container
	extern template class std::map<roulette::EMinimum, roulette::uint16>; // type_min_container

	extern template class sigc::signal0<void>; // type_signal
	extern template class sigc::signal1<void, roulette::uint16>; // type_signal_spin
	extern template class sigc::signal1<void, roulette::type_bet>; // type_signal_bet
	extern template class sigc::signal2<void, const roulette::EField&, roulette::type_chip>; // type_signal_chip

#endif // !TU_TYPES_CC

#endif // !TYPES_HH
