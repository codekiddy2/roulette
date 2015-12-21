
#ifndef ERROR_HH
#define ERROR_HH 1

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
//	error.hh
//
//	
//	TODO wrap all not necesary by main into second namespace
//	TODO write comments
//	TODO reserve 0th enum and set start at 1
//	c++11 TODO-s:
//	forward declare enum class ans use short enumeration (not default int)
//	mark classes final
//	initialize sets in Sets namespace with <set> class
//	
///</summary>

#include <string>
#include <exception>

namespace roulette
{
	class error final :
		public std::exception
	{
	public:
		// constructors
		error(const char* description, short code = 0) throw() :
			m_description(description), m_code(code) { }

		error(const error& ref)
			: m_description(ref.m_description), m_code(ref.m_code) { }

		error(error&& ref)
			: m_description(ref.m_description), m_code(ref.m_code) { }

		error& operator=(const error& rhs)
		{
			if (this != &rhs)
			{
				return *this;
			}
		}

		error& operator=(error&&)
		{
			return *this;
		}

		// methods
		const char* what() const throw() override
		{
			return m_description;
		}

		short code() const throw()
		{
			return m_code;
		}

	private:
		// members
		const short m_code;
		const char* m_description;
	};

	// error handler interface
	class IErrorHandler
	{
	public:
		// costructors
		IErrorHandler(const std::string&& derived_class);

		// methods
		inline virtual void set_debug(bool debug);

	protected:
		// methods
		virtual void error_handler(const error&& ref);
		virtual void print(const std::string&& info, bool newline = false);
		virtual void print(const char* info, bool newline = false);
		virtual void print(const unsigned char* info, bool newline = false);
		virtual void print(const int&& info, bool newline = false);
		virtual void print(const unsigned int info, bool newline = false);
		virtual void print(const unsigned long long&& info, bool newline = false);

		// members
		bool m_debug = false;
		std::string m_derived_class;
	};


	void IErrorHandler::set_debug(bool debug)
	{
		m_debug = debug;
	}

} // namespace roulette

#endif // ERROR_H
