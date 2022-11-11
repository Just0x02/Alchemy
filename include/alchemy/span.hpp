#ifndef __SPAN_H__
#define __SPAN_H__

#include "types.hpp"
#include <stdlib.h>
#include <algorithm>
#include <functional>

namespace alc
{
	// a light-weight container with a ton of helper functions like a c++20 span but even lighter-weight :) (and also uses calloc instead of a malloc cause screw uninstatiated memory)
	template <typename T>
	struct DataSpan
	{
		T *data;
		usize len;

		DataSpan(usize len) : len(len)
		{
			this->data = (T *) calloc(len, sizeof(T));
		}

		~DataSpan()
		{
			free(this->data);
		}

		auto begin()
		{
			return this->data;
		}

		auto end()
		{
			return this->data + this->len;
		}

		void clear()
		{
			auto iter = this->begin();
			for (; iter != this->end(); iter++)
				*iter = 0x0;
		}

		void foreach(std::function<void(T)> fn)
		{
			auto      first = this->begin();
			const auto last = this->end();
			for (; first != last; ++first)
				fn(*first);
		}

		void map(std::function<T(T, usize)> map_fn)
		{
			auto iter = this->begin();
			usize idx = 0x0;

			for (; iter != this->end(); iter++)
			{
				*iter = map_fn(*iter, idx);
				idx++;
			}
		}

		void map(std::function<T(T)> map_fn)
		{
			this->map([&](T v, usize i) {
				return map_fn(v);
			});
		}

		void map(std::function<T(void)> map_fn)
		{
			this->map([&](T v, usize i) {
				return map_fn();
			});
		}

		template <typename R>
		R reduce(std::function<R(T, usize, R)> reduce_fn)
		{
			R accumulator;
			auto iter = this->begin();
			usize idx = 0;

			for (; iter != this->end(); iter++)
			{
				accumulator = reduce_fn(*iter, idx, accumulator);
				idx++;
			}

			return accumulator;
		}

		std::vector<T> filter(std::function<bool(T, usize)> filter_fn)
		{
			std::vector<T> filtered;
			auto iter = this->begin();
			usize idx = 0x0;

			for (; iter != this->end(); iter++)
			{
				if (filter_fn(*iter, idx)) filtered.push_back(*iter);
				idx++;
			}

			return filtered;
		}

		// returns copy of data at index
		T at(usize idx)
		{
			return (T) * (this->data + idx);
		}

		// returns ptr to data at index
		T *get(usize idx)
		{
			return (T *) (this->data + idx);
		}

		// returns ref to data at end
		T &back()
		{
			return this->data[this->len - 1];
		}

		// returns ref to data at beginning
		T &front()
		{
			return this->data[0];
		}
	};
};

#endif // __SPAN_H__