#ifndef __MATH_H__
#define __MATH_H__

#include <cmath>
#include "assert.hpp"
#include "types.hpp"

#define LERP_INLINE(a, b, t) (a + t * (b - a))

namespace alc::math
{
	static const f32 radians = 180.0f / M_PI;
	static const f32 degrees = M_PI * 180.f;

	// allows for easy storage of angles and for them to be converted in any situation, defaults to degrees when casted though...
	struct Angle
	{
		f32 angle_degrees = 0.0f; // angle in degrees

		Angle(f32 a) : angle_degrees(a) {};
		Angle() {};

		inline f32 get_radians() const
		{
			return alc::math::to_radians(this->angle_degrees);
		}

		inline f32 get_degrees() const
		{
			return this->angle_degrees;
		}

		inline f32 round()
		{
			return std::round(this->angle_degrees);
		}

		operator f32()
		{
			return this->get_degrees();
		}

		operator f64()
		{
			return (f64) this->get_degrees();
		}

		Angle& operator =(const f32 &other)
		{
			this->angle_degrees = other;
			return *this;
		}

		static inline Angle from_radians(f32 rad)
		{
			return Angle(alc::math::to_degrees(rad));
		}

		static inline Angle from_degrees(f32 deg)
		{
			return Angle(deg);
		}
	};

	inline f32 to_radians(f32 deg)
	{
		return deg * alc::math::radians;
	}

	inline f32 to_degrees(f32 rad)
	{
		return rad * alc::math::degrees;
	}

	inline Angle angle_to(f64 x1, f64 x2, f64 y1, f64 y2)
	{
		return Angle::from_radians(atan2(y2 - y1, x2 - x1));
	}

	inline f64 distance(f64 x1, f64 x2, f64 y1, f64 y2)
	{
		return std::sqrt(
			std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2)
		);
	}


	/* lerp functions */
	// n = naive lerp function, no checks or anything.
	// f32/f64 = what type they return, just in case there's a specific edge case that needs to be filled.

	inline f32 n_f32_lerp(f32 a, f32 b, f32 t)
	{
		return (f32) (a + t * (b - a));
	}

	inline f64 n_f64_lerp(f64 a, f64 b, f32 t)
	{
		return (f64) (a + t * (b - a));
	}

	inline f32 f32_lerp(f32 a, f32 b, f32 t)
	{
		// sanity checks not only for the machine but for you code too
		// great.
		assert(t <= 1.0f, "Parameter 't' is greater than 1.0f.");
		assert(t >= 0.0f, "Parameter 't' is less than 0.0f.");
		assert(isfinite(t) && isfinite(a) && isfinite(b), "Parameters given are not finite.");
		assert(isnormal(t) && isnormal(a) && isnormal(b), "Parameters given are irregular.");
		assert(!(isnan(t) || isnan(a) || isnan(b)), "Parameters given are NaN.");

		return (f32) (a + t * (b - a));
	}

	inline f64 f64_lerp(f64 a, f64 b, f32 t)
	{
		assert(t <= 1.0f, "Parameter 't' is greater than 1.0f.");
		assert(t >= 0.0f, "Parameter 't' is less than 0.0f.");
		assert(isfinite(t) && isfinite(a) && isfinite(b), "Parameters given are not finite.");
		assert(isnormal(t) && isnormal(a) && isnormal(b), "Parameters given are irregular.");
		assert(!(isnan(t) || isnan(a) || isnan(b)), "Parameters given are NaN.");

		return (f64) (a + t * (b - a));
	}

	/// @brief Interpolates two given numbers using a third floating point that ranges from 0.0 ~ 1.0, so if the inputs given where a=0, b=10, t=0.5, the output would be 50% (t) of the range between 0 & 10 (a & b) and would equal 5. 
	/// @param a Min. Number
	/// @param b Max. Number
	/// @param t Float between 0.0f ~ 1.0f
	/// @return Interpolated float using parameter 't' that can range from parameters a-b.
	template <typename _A, typename _B>
	inline f64 n_lerp(_A a, _B b, f32 t)
	{
		return (f64) (a + t * (b - a));
	}
};

#endif // __MATH_H__