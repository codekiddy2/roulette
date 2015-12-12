#ifndef ENGINE_HH
#define ENGINE_HH

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

#include "sets.hh"

#include <boost/random.hpp>
#include <boost/random/random_device.hpp>

class History;

class Engine final
{
public:
	// constructors
	Engine(History* history);
	Engine(const Engine&) = delete;
	Engine(const Engine&&) = delete;
	Engine& operator=(const Engine&) = delete;
	Engine& operator=(const Engine&&) = delete;

	// methods
	void spin(const ETable table_type) const;

private:
	/// begin initializer list
	History* pHistory;
	/// end initializer list
	static boost::random::random_device rng;
};

#endif // !ENGINE_HH