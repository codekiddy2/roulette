#pragma once
#include <gtkmm/gtkmm.h>
#include "field.hpp"
#include <vector>


class Table final :
	public Gtk::Box
{
public:
	Table();
	~Table();

private:
	Gtk::Grid mGrid;
	std::vector<Field*> mFields;
};