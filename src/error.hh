
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
// error class is a customized class to throw error description
// errors are thrown trough IErrorHandler interface class which
// is inherited by all other classes.
// if the derived class does not override error_handler() the base
// class will throw and tell us which object throwed the error.
// this is possible since base class takes derived class name into
// constructor as parameter
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

		// set debugging option for derived class
		inline virtual void set_debug(bool debug);

	protected:
		// methods
		// error handler to throw and handle errors
		virtual void error_handler(const error&& ref);

		// a set of overrides for debugging output
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
