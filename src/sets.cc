
#include "pch.hh"
#include "sets.hh"

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

bool IsRed(const int number)
{
	switch (number)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 9:
	case 12:
	case 14:
	case 16:
	case 18:
	case 19:
	case 21:
	case 23:
	case 25:
	case 27:
	case 30:
	case 32:
	case 34:
	case 36:
		return true;
	default:
		return false;
	}
}
