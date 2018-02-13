// External Dependencies
#include "../../core/include/math.h"

// Module Dependencies
#include "../include/size.h"

namespace native
{
	namespace ui
	{
		Size::Size() noexcept : width(0), height(0)
		{
		}

		Size::Size(coord_t width, coord_t height) noexcept : width(width), height(height)
		{
		}

		void Size::set(coord_t width, coord_t height) noexcept
		{
			this->width = width;
			this->height = height;
		}

		Size Size::combine(const Size& other) const noexcept
		{
			return { Math::max(width, other.width), Math::max(height, other.height) };
		}
	}
}

