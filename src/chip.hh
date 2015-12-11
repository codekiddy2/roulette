#pragma once
#include <gtkmm.h>
#include <string>

class Chip final
	: public Gtk::Widget
{
public:
	Chip(std::string icon);

protected:

	//Overrides:
	Gtk::SizeRequestMode get_request_mode_vfunc() const override;
	void get_preferred_width_vfunc(int& minimum_width, int& natural_width) const override;
	void get_preferred_height_for_width_vfunc(int width, int& minimum_height, int& natural_height) const  override;
	void get_preferred_height_vfunc(int& minimum_height, int& natural_height) const override;
	void get_preferred_width_for_height_vfunc(int height, int& minimum_width, int& natural_width) const override;
	void on_size_allocate(Gtk::Allocation& allocation) override;
	void on_map() override;
	void on_unmap() override;
	void on_realize() override;
	void on_unrealize() override;
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

	Glib::RefPtr<Gdk::Window> m_refGdkWindow;

private:
	Gdk::Color mBackground;
	Glib::RefPtr<Gdk::Pixbuf> refIcon;

	/// begin initializer list
	std::string mName;
	/// end initializer list
};
