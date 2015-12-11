#pragma once
#include <gtkmm/gtkmm.h>


class HistoryWindow final
	: public Gtk::ScrolledWindow
{
// constructors
public:
	HistoryWindow();
	HistoryWindow(const HistoryWindow&) = delete;
	HistoryWindow(const HistoryWindow&&) = delete;
	HistoryWindow& operator=(const HistoryWindow&) = delete;
	HistoryWindow& operator=(const HistoryWindow&&) = delete;


/// declaration in order of initializer list
private:
	Glib::RefPtr<Gtk::TextBuffer::TagTable> mTagTable;

public:
	Glib::RefPtr<Gtk::TextBuffer> refRedBuffer, refBlackBuffer, refGreenBuffer;
	Gtk::TextView mViewRed, mViewBlack, mViewGreen;
	Glib::RefPtr<Gtk::TextBuffer::Tag> mTagRed, mTagBlack, mTagGreen;
/// end of initializer list

// methods
	void apply_tags();

private:
// other members
	Gtk::HBox mHBox;
};

