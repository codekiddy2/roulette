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
//	history.cc
//
//	Definition of History class
//
///</summary>

#include "pch.hh"
#include "history.hh"
#include "main.hh"

namespace
{
	using std::string; // used in ctor and set_result
	using std::to_string; // used in set_result
}

namespace roulette
{
	History::History() :
		IErrorHandler("History"),
		mTagTable(Gtk::TextTagTable::create()),
		refRedBuffer(Gtk::TextBuffer::create(mTagTable)),
		refBlackBuffer(Gtk::TextBuffer::create(mTagTable)),
		refGreenBuffer(Gtk::TextBuffer::create(mTagTable)),
		mViewRed(refRedBuffer),
		mViewBlack(refBlackBuffer),
		mViewGreen(refGreenBuffer),
		mTagRed(Gtk::TextBuffer::Tag::create()),
		mTagBlack(Gtk::TextBuffer::Tag::create()),
		mTagGreen(Gtk::TextBuffer::Tag::create())
	{
		// window properties
		set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);

		// packing
		add(mHBox);

		mHBox.pack_start(mViewRed, Gtk::PACK_EXPAND_WIDGET);
		mHBox.pack_start(mViewGreen, Gtk::PACK_EXPAND_WIDGET);
		mHBox.pack_start(mViewBlack, Gtk::PACK_EXPAND_WIDGET);

		mTagTable->add(mTagRed);
		mTagTable->add(mTagGreen);
		mTagTable->add(mTagBlack);

		// set up tag table for coloring
		mTagRed->property_foreground() = "Red";
		mTagGreen->property_foreground() = "Green";
		mTagBlack->property_foreground() = "Gold";

		mTagRed->property_background() = "Black";
		mTagGreen->property_background() = "Black";
		mTagBlack->property_background() = "Black";

		// prevent history modification
		mViewBlack.set_sensitive(false);
		mViewRed.set_sensitive(false);
		mViewGreen.set_sensitive(false);

		// initial buffer to prevent alignment of numbers
		// and also to color up the text buffers
		string newline = "\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t\n\t";
		refRedBuffer->set_text(newline);
		refGreenBuffer->set_text(newline);
		refBlackBuffer->set_text(newline);
		
		apply_tags();
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

	void History::set_result(uint16 result)
	{
		string red_output, black_output, green_output;
		string single_space = " ", triple_space = "   ", newline = "\n", tab = "\t";

		// format result to be properly aligned with past results
		if (result == 0)
		{
			green_output.append(triple_space + to_string(result) + tab + newline);
			green_output.append(refGreenBuffer->get_text());

			red_output.append(tab + newline);
			red_output.append(refRedBuffer->get_text());

			black_output.append(tab + newline);
			black_output.append(refBlackBuffer->get_text());
		}
		else if (is_red(result))
		{
			red_output.append(triple_space + to_string(result) + tab + newline);
			red_output.append(refRedBuffer->get_text());

			green_output.append(tab + newline);
			green_output.append(refGreenBuffer->get_text());

			black_output.append(tab + newline);
			black_output.append(refBlackBuffer->get_text());
		}
		else // black result :)
		{
			black_output.append(single_space + to_string(result) + tab + newline);
			black_output.append(refBlackBuffer->get_text());

			green_output.append(tab + newline);
			green_output.append(refGreenBuffer->get_text());

			red_output.append(tab + newline);
			red_output.append(refRedBuffer->get_text());
		}

		// set text
		refGreenBuffer->set_text(green_output);
		refRedBuffer->set_text(red_output);
		refBlackBuffer->set_text(black_output);

		// apply colors
		apply_tags();
	}

} // namespace roulette
