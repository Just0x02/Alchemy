#ifndef __RANDOM_H__
#define __RANDOM_H__

#include "types.hpp"
#include "win_interop.hpp"

#include <cstdlib>
#include <ctime>
#include <cmath>

namespace alc::random
{
	/// @brief Seeds random with a very very very very technically pseudorandom number
	void seed() 
	{
		// gets current cpu clock cycle with some inline assembly in order to make the default random seed more... well... random.
		// define '__ALC__NO_INLINE_ASM' to disable this.
		const volatile u64 cpu_tick_cycle = alc::get_cpu_clock_cycle();
		std::srand(std::time(0) + clock() + cpu_tick_cycle);
	}


	/// @brief Returns a random floating point between 0.0f ~ 1.0f
	f32 randflt()
	{
		return (float) std::rand() / (float) RAND_MAX;
	}

	/// @brief Returns a random integer (inclusive).
	/// @param min Min. number
	/// @param max Max. number
	/// @return Returns a random integer between (& including) the two numbers given.
	i64 randint(i64 min, i64 max)
	{
		return (i64) std::floor(random::randflt() * (max - min + 1) + min);
	}
};

#endif // __RANDOM_H__