
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

// roulette
#include "types.hh"

// std
#include <string>
#include <exception>

namespace roulette
{
	class error final :
		public std::exception
	{
	public:
		// constructors
		inline error(const char* description, const uint16 code = 0) noexcept;
		inline error(const error& ref) noexcept;
		inline error(error&& ref) noexcept;
		inline error& operator=(const error& rhs) noexcept;
		inline error& operator=(error&&) noexcept;

		// methods
		inline const char* what() const noexcept override;
		inline uint16 code() const noexcept;

	private:
		// members
		const uint16 m_code;
		const char* m_description;
	};

	// error handler and debug interface
	class IErrorHandler
	{
	public:
		// set debugging option for derived class
		inline virtual void set_debug(bool debug) noexcept;

	protected:
		// costructors
		inline IErrorHandler(const std::string&& derived_class) noexcept;
		inline virtual ~IErrorHandler() noexcept = 0;

		// methods
		// error handler to throw and handle errors
		virtual void error_handler(const error&& ref);

		// a set of overrides for debugging output
		virtual void print() noexcept;
		virtual void print(const std::string&& info, bool newline = false) noexcept;
		virtual void print(const char* info, bool newline = false) noexcept;
		virtual void print(const unsigned char* info, bool newline = false) noexcept;
		virtual void print(const int&& info, bool newline = false) noexcept;
		virtual void print(const uint16 info, bool newline = false) noexcept;
		virtual void print(const uint64&& info, bool newline = false) noexcept;
		virtual void print(EField& info, bool newline = false) noexcept;
		virtual void print(EBet info, bool newline = false) noexcept;

		// members
		bool m_debug = false;
		std::string m_derived_class;

	private:
		// deleted
		IErrorHandler(const IErrorHandler&) = delete;
		IErrorHandler(const IErrorHandler&&) = delete;
		IErrorHandler& operator=(const IErrorHandler&) = delete;
		IErrorHandler& operator=(const IErrorHandler&&) = delete;
	};

#ifdef _MSC_VER
#pragma region
#endif // _MSC_VER

	IErrorHandler::IErrorHandler(const std::string && derived_class) noexcept :
	m_derived_class(derived_class)
	{ }

	IErrorHandler::~IErrorHandler()
	{ }

	void IErrorHandler::set_debug(bool debug) noexcept
	{
		m_debug = debug;
	}

	error::error(const char* description, const uint16 code) noexcept :
		m_description(description),
		m_code(code)
	{ }

	error::error(const error& ref)  noexcept :
		m_description(ref.m_description),
		m_code(ref.m_code)
	{ }

	error::error(error&& ref) noexcept :
		m_description(ref.m_description),
		m_code(ref.m_code)
	{ }

	error& error::operator=(const error& rhs) noexcept
	{
		if (this != &rhs)
		{
			return *this;
		}
	}

	error& error::operator=(error&&) noexcept
	{
		return *this;
	}

	const char* error::what() const noexcept
	{
		return m_description;
	}

	uint16 error::code() const noexcept
	{
		return m_code;
	}

#ifdef _MSC_VER
#pragma endregion inlines
#endif // _MSC_VER

} // namespace roulette

#endif // ERROR_H
