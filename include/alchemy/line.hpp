#ifndef __LINE_H__
#define __LINE_H__

#include "point.hpp"
#include "mathutils.hpp"

namespace alc
{
	template <typename T>
	struct Line
	{
		Point<T> start, end;

		Line(Point<T> line_start, Point<T> line_end) : start(line_start), end(line_end) {};

		inline f64 length() const
		{
			return this->start.distance_to(this->end);
		}

		inline f64 slope() const
		{
			return (this->end.y - this->start.y) / (this->end.x - this->start.y);
		}

		inline math::Angle angle() const
		{
			return math::angle_to(this->start.x, this->end.x, this->start.y, this->end.y);
		}

		inline Point<T> midpoint() const
		{
			return Point::midpoint(this->start, this->end);
		}

		inline Line &transform(Point<T> offset)
		{
			this->start += offset;
			this->end   += offset;

			return *this;
		}

		inline Line &transform(T off_x, T off_y)
		{
			Point<T> offsetter(off_x, off_y);
			return this->transform(offsetter);
		}

		inline Line clone()
		{
			return Line<T>(this->start, this->end);
		}

		inline Line &copy_from(const Line &other)
		{
			this->start = other.start;
			this->end   = other.end;

			return *this;
		}
	};

	typedef Line<i64> iLine;
	typedef Line<u64> uLine;
	typedef Line<f64> fLine;
};

#endif // __LINE_H__