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
//	error.cc
//
//	Defines IErrorHandler interface class
//
// TODO: add more overloads
//	
///</summary>

// roulette
#include "pch.hh"
#include "error.hh"
#include "sets.hh"

namespace
{
	// used in print functions
	using std::cout;
	using std::endl;
	using std::to_string;
}

namespace roulette
{

	void IErrorHandler::error_handler(const error && ref)
	{
		print("Error thrown but not handled by " + m_derived_class + " class");
		print("ERROR: ", true);
		print(ref.what());
		throw(ref);
	}

	void IErrorHandler::print() noexcept
	{
		cout << endl;
	}

	void IErrorHandler::print(const std::string&& info, bool newline /*= false*/) noexcept
	{
		if (newline)
		{
			cout << endl;
			cout << "-> " << info;
			return;
		}
		cout << info;
	}

	void IErrorHandler::print(const int&& info, bool newline /*= false*/) noexcept
	{
		if (newline)
		{
			cout << endl;
			cout << "-> " << to_string(info);
			return;
		}
		cout << to_string(info);
	}

	void IErrorHandler::print(const unsigned int info, bool newline /*= false*/) noexcept
	{
		if (newline)
		{
			cout << endl;
			cout << "-> " << to_string(info);
			return;
		}
		cout << to_string(info);
	}

	void IErrorHandler::print(const unsigned long long&& info, bool newline /*= false*/) noexcept
	{
		if (newline)
		{
			cout << endl;
			cout << "-> " << to_string(info);
			return;
		}
		cout << to_string(info);
	}

	void IErrorHandler::print(const char* info, bool newline /*= false*/) noexcept
	{
		if (newline)
		{
			cout << endl;
			cout << "-> " << info;
			return;
		}
		cout << info;
	}

	void IErrorHandler::print(const unsigned char* info, bool newline /*= false*/) noexcept
	{
		if (newline)
		{
			cout << endl;
			cout << "-> " << info;
			return;
		}
		cout << info;
	}

	void IErrorHandler::print(EField& info, bool newline /*= false*/) noexcept
	{
		if (newline)
		{
			cout << endl;
			cout << "-> " << to_string(static_cast<unsigned>(info));
			return;
		}
		cout << to_string(static_cast<unsigned>(info));
	}

	void IErrorHandler::print(EBet info, bool newline /*= false*/) noexcept
	{
		if (newline)
		{
			cout << endl;
			cout << "-> " << to_string(static_cast<unsigned>(info));
			return;
		}
		cout << to_string(static_cast<unsigned>(info));
	}

} // namespace roulette
