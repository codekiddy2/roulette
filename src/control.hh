
#ifndef CONTROL_HH
#define CONTROL_HH 1

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
//	control.hh
//
//	Declaration of Control class
//
//	Control is a customized button to be shown
// on main window
// it only overrides the on_draw method and
// handles a clicked signal
//
///</summary>

// roulette
#include "base_control.hh"

namespace roulette
{
	class Control final :
		public BaseControl
	{
	public:
		// constructors
		Control(const std::string&& name);

	private:
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

		// deleted
		Control(const Control&) = delete;
		Control(const Control&&) = delete;
		Control& operator=(const Control&) = delete;
		Control& operator=(const Control&&) = delete;
	};

} // namespace roulette

#endif // ! CONTROL_HH
