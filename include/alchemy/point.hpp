#ifndef __POINT_H__
#define __POINT_H__

#include "types.hpp"
#include "mathutils.hpp"

#include <sstream>
#include <cmath>

namespace alc
{
	// who doesn't want a templated point class?
	template <typename T>
	struct Point
	{
		T x, y;

		Point(T x, T y) : x(x), y(y) {};
		Point() : x(0), y(0) {};

		inline f64 distance_to(Point<T> other)
		{
			return math::distance(this->x, other.x, this->y, other.y);
		}

		inline void zero()
		{
			this->x = 0;
			this->y = 0;
		}

		inline u64 length() const noexcept
		{
			return this->x + this->y;
		}

		inline void set(T x, T y)
		{
			this->x = x;
			this->y = y;
		}

		inline Point<T> clone()
		{
			return Point<T>(this->x, this->y);
		}

		inline Point<T> operator +(const Point<T> &other)
		{
			Point<T> res;

			res.x = this->x + other.x;
			res.y = this->y + other.y;

			return res;
		}

		inline Point<T>& operator +=(const Point<T> &other)
		{
			this->x += other.x;
			this->y += other.y;
			return *this;
		}

		template <typename PT>
		friend bool operator<(const Point<PT> &lhs, const Point<PT> &rhs)
		{
			return lhs.length() < rhs.length();
		}

		template <typename PT>
		friend bool operator>(const Point<PT> &lhs, const Point<PT> &rhs)
		{
			return lhs.length() > rhs.length();
		}

		template <typename PT>
		friend bool operator<=(const Point<PT> &lhs, const Point<PT> &rhs)
		{
			return lhs.length() <= rhs.length();
		}

		template <typename PT>
		friend bool operator>=(const Point<PT> &lhs, const Point<PT> &rhs)
		{
			return lhs.length() >= rhs.length();
		}

		template <typename PT>
		friend bool operator==(const Point<PT> &lhs, const Point<PT> &rhs)
		{
			return lhs.length() == rhs.length();
		}

		operator string()
		{
			std::stringstream ss;

			ss << "Point(" << +this->x << ", " << +this->y << ")";

			return ss.str();
		}

		template <typename PT>
		static Point<PT> ZERO()
		{
			return Point<PT>(0, 0);
		}

		template <typename _T, typename _A, typename _B>
		static Point<_T> lerp(Point<_A> a, Point<_B> b, f32 t)
		{
			f64 x_lerped = math::f64_lerp(a.x, b.x, t);
			f64 y_lerped = math::f64_lerp(a.y, b.y, t);

			return Point<_T>(x_lerped, y_lerped);
		}

		template <typename _T, typename _A, typename _B>
		static Point<_T> midpoint(Point<_A> a, Point<_B> b)
		{
			return Point::lerp(a, b, 0.5f);
		}
	};

	typedef Point<i64> iPoint;
	typedef Point<u64> uPoint;
	typedef Point<f64> fPoint;
};


#endif // __POINT_H__