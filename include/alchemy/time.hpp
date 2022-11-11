#ifndef __TIME_H__
#define __TIME_H__

#include "types.hpp"
#include <chrono>
#include <cmath>
#include <sstream>

namespace alc
{
	// I swear to god if I have to duration cast in another project just to get the timing of a function imma return to monkey and smash my computer
	// making a function to just get the time and be done with it
	u64 get_time_ms()
	{
		std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now().time_since_epoch());
		return (u64) ms.count();
	}

	u64 get_time_ns()
	{
		std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::system_clock::now().time_since_epoch());
		return (u64) ns.count();
	}

	// the cpp stl definetly has one of these classes but whoever made them decided they needed to have like 50+ features that no one cares about
	struct Timer
	{
		u64 start = 0UL, end = 0UL;

		void begin()
		{
			this->start = alc::get_time_ns();
			this->end   = 0UL;
		}

		void stop()
		{
			this->end = alc::get_time_ns();
		}

		u64 time_taken()
		{
			return this->end - this->start;
		}

		operator string()
		{
			std::stringstream ss;

			string time_type = "NS";
			u64 taken = this->time_taken();

			if (taken >= 10000)
			{
				taken /= 10000;
				time_type = "MS";
			}

			ss << taken << time_type;

			return ss.str();
		}
	};
};

#endif // __TIME_H__