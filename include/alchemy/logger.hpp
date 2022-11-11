#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "types.hpp"
#include "color.hpp"

#include <iostream>

namespace alc
{
	struct Logger
	{
		Color fore = Color::random();
		Color back = Color(0x0, 0x0, 0x0);

		const Logger *parent = NULL; // ref to parent if the parent's namespace needs to be fetched aswell
		string ns; // logger namespace

		Logger(string ns) : ns(ns) {};
		Logger(const Logger *parent, string ns) : parent(parent), ns(ns) 
		{
			this->fore = Color::lighten(parent->fore, 0.2f); // lighten it slightly
			this->back = parent->back;
		};

		const string get_prefix() const
		{
			string prefix = fore.as_ansii_fg() + "[" + this->ns + "]";

			if (this->parent != NULL)
				prefix = this->parent->get_prefix() + prefix;

			return prefix + " >> ";
		}

		void println()
		{
			std::cout << Color::reset() << std::endl;
		}

		template <typename T, typename... Types>
		void println(T curr_str, Types... args)
		{
			std::cout << this->get_prefix() << curr_str;
			this->_println_helper(args...);
		}

		template <typename T, typename... Types>
		void _println_helper(T curr_str, Types... args)
		{
			std::cout << curr_str;
			this->_println_helper(args...);
		}

		inline Logger make_child(string child_ns) const noexcept
		{
			return Logger(this, child_ns);
		}
	};
};


#endif // __LOGGER_H__