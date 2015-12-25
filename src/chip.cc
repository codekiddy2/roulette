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
//	chip.cc
//
//	Definition of Chip class
//
///</summary>

#include "pch.hh"
#include "chip.hh"
#include "main.hh"
#include "engine.hh"

namespace roulette
{
	using std::cerr;
	using std::endl;
	using std::cout;
	using std::string;

#ifdef _MSC_VER
#pragma region begin
#endif // _MSC_VER


	Chip::Chip(Engine* p_engine, const EChip chip_value) :
		BaseControl("Chip"),
		m_value(static_cast<unsigned>(chip_value)),
		mp_engine(p_engine),
		refIcon(get_pixbuf(chip_value))
	{
		set_has_window(true);
		set_events(Gdk::EventMask::BUTTON_PRESS_MASK); // TODO: implement chip behaviour for other masks

		// Make this Chip a drag source
		std::vector<Gtk::TargetEntry> this_source;
		Gtk::TargetEntry entry(std::to_string(m_value),
			Gtk::TargetFlags::TARGET_OTHER_WIDGET, static_cast<guint>(chip_value));

		dnd_targets.push_back(entry);
		this_source.push_back(entry);

		drag_source_set(this_source, Gdk::ModifierType::BUTTON1_MASK, Gdk::ACTION_COPY);
	}

#ifdef _MSC_VER
#pragma endregion

#pragma region dnd
#endif //_MSC_VER

	/*
	The source widget will emit these signals, in this order:

	drag_begin:
	Provides DragContext.

	drag_data_get:
	Provides info about the dragged data format, and a Gtk::SelectionData structure,
	in which you should put the requested data.

	drag_end:
	Provides DragContext.
	*/

	void Chip::on_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context)
	{
		if (m_debug)
		{
			print("INFO: drag begin");
			print("Source  Chip", true);
			print("seting up drag icon", true);
			print();
		}

		context->set_icon(refIcon, // the GdkPixbuf to use as the drag icon.
			refIcon->get_width() / 2, // the X offset within widget of the hotspot.
			refIcon->get_height() / 2); // the Y offset within widget of the hotspot.
	}


	void Chip::on_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& /*context*/,
		Gtk::SelectionData& selection_data, guint info, guint time)
	{
		selection_data.set(selection_data.get_target(), format, reinterpret_cast<const guint8*>(mp_engine), sizeof(Engine));

		if (m_debug)
		{
			print("INFO: providing drag info");
			print("Source: Chip", true);
			print("target: ", true);
			print(selection_data.get_target());
			print("pointer: ", true);
			print(selection_data.get_data());
			print("length: ", true);
			print(selection_data.get_length());
			print("format = ", true);
			print(static_cast<int>(format));
			print("info = ", true);
			print(static_cast<int>(info));
			print("time = ", true);
			print(static_cast<int>(time));
			print();

			if (selection_data.set_pixbuf(refIcon))
			{
				Glib::RefPtr<const Gdk::Pixbuf> temp = selection_data.get_pixbuf();
				print("pixbuf size = ", true);
				print(temp->get_byte_length());
				print();
			}
			else
			{
				print("WARNING: get_pixbuf() did not return a pixbuf");
				print("if targets include image = ", true);
				print(selection_data.targets_include_image(false));
				print();
			}
		}
	}


	void Chip::on_drag_end(const Glib::RefPtr<Gdk::DragContext>& context)
	{
		if (m_debug)
		{
			print("INFO: drag ended");
			print("Source: Chip", true);
			print();
		}

		// TODO: implement on_drag_end functionality
		return Gtk::Widget::on_drag_end(context);
	}


#ifdef _MSC_VER
#pragma endregion

#pragma region drawing
#endif // _MSC_VER

	// Draw on the supplied Cairo::Context.
	bool Chip::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
	{
		Gtk::Allocation allocation = get_allocation();

		// paint the background
		Gdk::Cairo::set_source_rgba(cr, Color::get_background_color());
		cr->paint();

		// draw chip in the middle
		Gdk::Cairo::set_source_pixbuf(cr, refIcon,
			allocation.get_width() * 0.5 - (refIcon->get_width() / 2),
			allocation.get_height() * 0.5 - (refIcon->get_height() / 2));

		cr->paint();

		return true;
	}

#ifdef _MSC_VER
#pragma endregion
#endif // _MSC_VER

} // namespace roulette
