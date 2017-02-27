// External Dependencies
#include "../../../core/include/math.h"

// Module Dependencies
#include "../../include/point.h"

namespace native
{
	namespace ui
	{
		Point::Point(coord_t x, coord_t y) noexcept : x(x), y(y)
		{
		}

		void Point::set(coord_t x, coord_t y) noexcept
		{
			this->x = x;
			this->y = y;
		}

		coord_t Point::distanceFrom(Point other) noexcept
		{
			return Math::squareRoot((Math::abs(x - other.x) * Math::abs(x - other.x)) + (Math::abs(y - other.y) * Math::abs(y - other.y)));
		}
	}
}

