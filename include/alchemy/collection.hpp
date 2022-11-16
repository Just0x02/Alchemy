// #ifndef __COLLECTION_H__
// #define __COLLECTION_H__

// #include "types.hpp"
// #include <cstdlib>

// namespace alc
// {
// 	template <typename T>
// 	struct Collection
// 	{
// 		T *members;
// 		usize size;

// 		void resize(usize new_size)
// 		{
// 			this->size = new_size;
// 			this->members = (T *) realloc(this->members, this->size);
// 		}

// 		void remove(usize index)
// 		{

// 		}

// 		void add(T new_member)
// 		{
			
// 		}

// 		T &at(usize index)
// 		{
// 			return *this->get(index);
// 		}

// 		T *get(usize index)
// 		{
// 			return this->begin() + index;
// 		}

// 		auto begin()
// 		{
// 			return this->members;
// 		}

// 		auto end()
// 		{
// 			return this->members + this->size;
// 		}
// 	};
// };

// #endif // __COLLECTION_H__