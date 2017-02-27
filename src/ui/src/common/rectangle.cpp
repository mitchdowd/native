// Module Dependencies
#include "../../include/rectangle.h"

namespace native
{
	namespace ui
	{
		Rectangle::Rectangle() noexcept : x(0), y(0), width(0), height(0)
		{
		}

		Rectangle::Rectangle(coord_t x, coord_t y, coord_t width, coord_t height) noexcept
			: x(x), y(y), width(width), height(height)
		{
		}

		Rectangle::Rectangle(const Size& size) noexcept : x(0), y(0), width(size.width), height(size.height)
		{
		}

		void Rectangle::setSize(const Size& size) noexcept
		{
			width  = size.width;
			height = size.height;
		}

		Size Rectangle::getSize() const noexcept
		{
			return Size(width, height);
		}

		Rectangle Rectangle::scale(float factor) const noexcept
		{
			return Rectangle(coord_t(x * factor), coord_t(y * factor), coord_t(width * factor), coord_t(height * factor));
		}
	}
}

