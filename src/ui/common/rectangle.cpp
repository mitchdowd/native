// Module Dependencies
#include "../include/rectangle.h"

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


		Rectangle::Rectangle(const Point& position, const Size& size) noexcept
			: x(position.x), y(position.y), width(size.width), height(size.height)
		{
		}

		void Rectangle::set(coord_t x, coord_t y, coord_t width, coord_t height) noexcept
		{
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
		}

		void Rectangle::setSize(const Size& size) noexcept
		{
			width = size.width;
			height = size.height;
		}

		void Rectangle::ensureSize(const Size& minimumSize) noexcept
		{
			if (width < minimumSize.width)
				width = minimumSize.width;
			if (height < minimumSize.height)
				height = minimumSize.height;
		}

		Size Rectangle::getSize() const noexcept
		{
			return Size(width, height);
		}

		void Rectangle::setPosition(const Point& position) noexcept
		{
			x = position.x;
			y = position.y;
		}

		Rectangle Rectangle::offset(coord_t x_, coord_t y_) const noexcept
		{
			return Rectangle(x + x_, y + y_, width, height);
		}

		bool Rectangle::containsPoint(const Point& point) const noexcept
		{
			return point.x >= x && point.x < x + width && point.y >= y && point.y < y + height;
		}

		bool Rectangle::containsPoint(coord_t x, coord_t y) const noexcept
		{
			return x >= this->x && x < this->x + width && y >= this->y && y < this->y + height;
		}

		Rectangle Rectangle::deflate(int hamount, int vamount) const noexcept
		{
			return Rectangle(x + hamount, y + vamount, width - (2 * hamount), height - (2 * vamount));
		}

		Rectangle Rectangle::deflate(float hamount, float vamount) const noexcept
		{
			return Rectangle(x + coord_t(hamount), y + coord_t(vamount), width - coord_t(2 * hamount), height - coord_t(2 * vamount));
		}

		Rectangle Rectangle::scale(float factor) const noexcept
		{
			return Rectangle(coord_t(x * factor), coord_t(y * factor), coord_t(width * factor), coord_t(height * factor));
		}

		bool Rectangle::operator==(const Rectangle& other) const
		{
			return x == other.x 
				&& y == other.y 
				&& width == other.width 
				&& height == other.height;
		}

		coord_t Rectangle::operator[](Orientation orientation) const noexcept
		{
			return orientation == Horizontal ? width : height;
		}

		coord_t& Rectangle::operator[](Orientation orientation) noexcept
		{
			return orientation == Horizontal ? width : height;
		}
	}
}

