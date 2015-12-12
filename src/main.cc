
#include "pch.hh"
#include "window.hh"

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


int main(int argc, char* argv[])
{

	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create( argc, argv, "roulette.exe" );

	Window* p_window = new Window;

	if ( p_window )
	{
		return app->run( *p_window );
	}
	else
	{
		return 1;
	}
}
