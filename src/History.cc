
#include "pch.hh"
#include "history.hh"

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


History::History() :
	mTagTable(Gtk::TextTagTable::create()),
	refRedBuffer(Gtk::TextBuffer::create(mTagTable)),
	refBlackBuffer(Gtk::TextBuffer::create(mTagTable)),
	refGreenBuffer(Gtk::TextBuffer::create(mTagTable)),
	mViewRed(refRedBuffer),
	mViewBlack(refBlackBuffer),
	mViewGreen(refGreenBuffer),
	mTagBlack(Gtk::TextBuffer::Tag::create()),
	mTagRed(Gtk::TextBuffer::Tag::create()),
	mTagGreen(Gtk::TextBuffer::Tag::create())
{
	// window properties
	//set_size_request(100, 0);
	set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);

	// packing
	add(mHBox);

	mHBox.pack_start(mViewRed, Gtk::PACK_EXPAND_WIDGET);
	mHBox.pack_start(mViewGreen, Gtk::PACK_EXPAND_WIDGET);
	mHBox.pack_start(mViewBlack, Gtk::PACK_EXPAND_WIDGET);

	mTagTable->add(mTagBlack);
	mTagTable->add(mTagRed);
	mTagTable->add(mTagGreen);

	// set up tag table for coloring
	mTagBlack->property_foreground() = "Gold";
	mTagRed->property_foreground() = "Red";
	mTagGreen->property_foreground() = "Green";

	// prevent history modification
	mViewBlack.set_sensitive(false);
	mViewRed.set_sensitive(false);
	mViewGreen.set_sensitive(false);

	// set background color
	mViewBlack.override_background_color(Gdk::RGBA("Black"));
	mViewRed.override_background_color(Gdk::RGBA("Black"));
	mViewGreen.override_background_color(Gdk::RGBA("Black"));
}

void History::apply_tags()
{
	refRedBuffer->apply_tag(
		mTagRed,
		refRedBuffer->begin(),
		refRedBuffer->end());

	refBlackBuffer->apply_tag(
		mTagBlack,
		refBlackBuffer->begin(),
		refBlackBuffer->end());

	refGreenBuffer->apply_tag(
		mTagGreen,
		refGreenBuffer->begin(),
		refGreenBuffer->end());
}

