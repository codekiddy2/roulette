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
//	TODO: add description
//	
///</summary>

#include "pch.hh"
#include "error.hh"

#include <iostream>

namespace roulette
{
	using std::cout;
	using std::endl;

	IErrorHandler::IErrorHandler(const std::string && derived_class) :
		m_derived_class(derived_class)
	{
	}

	void IErrorHandler::error_handler(const error && ref)
	{
		print("Error thrown but not handled by " + m_derived_class + " class");
		print("ERROR: ", true);
		print(ref.what());
		throw(ref);
	}

	void IErrorHandler::print(const std::string&& info, bool newline /*= false*/)
	{
		if (newline)
		{
			cout << endl;
			cout << "-> " << info;
			return;
		}
		cout << info;
	}

	void IErrorHandler::print(const int&& info, bool newline /*= false*/)
	{
		if (newline)
		{
			cout << endl;
			cout << "-> " << std::to_string(info);
			return;
		}
		cout << std::to_string(info);
	}

	void IErrorHandler::print(const unsigned int info, bool newline /*= false*/)
	{
		if (newline)
		{
			cout << endl;
			cout << "-> " << std::to_string(info);
			return;
		}
		cout << std::to_string(info);
	}

	void IErrorHandler::print(const unsigned long long&& info, bool newline /*= false*/)
	{
		if (newline)
		{
			cout << endl;
			cout << "-> " << std::to_string(info);
			return;
		}
		cout << std::to_string(info);
	}

	void IErrorHandler::print(const char* info, bool newline /*= false*/)
	{
		if (newline)
		{
			cout << endl;
			cout << "-> " << info;
			return;
		}
		cout << info;
	}

	void IErrorHandler::print(const unsigned char* info, bool newline /*= false*/)
	{
		if (newline)
		{
			cout << endl;
			cout << "-> " << info;
			return;
		}
		cout << info;
	}

} // namespace
