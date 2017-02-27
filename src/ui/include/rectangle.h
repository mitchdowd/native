#ifndef _NATIVE_UI_RECTANGLE_H_
#define _NATIVE_UI_RECTANGLE_H_ 1

// Module Dependencies
#include "point.h"
#include "size.h"

namespace native
{
	namespace ui
	{
		/**
			Describes a rectangle in 2-dimensional space.
		 */
		class Rectangle
		{
		public:
			// Instance Variables
			coord_t x;			///< Horizontal co-ordinate of the top-left corner.
			coord_t y;			///< Vertical co-ordinate of the top-left corner.
			coord_t width;		///< Width of the rectangle.
			coord_t height;		///< Height of the rectangle.

			/**
				Default constructor. Creates an empty Rectangle.
			 */
			Rectangle() noexcept;

			/**
				Creates a Rectangle with the given position and dimensions.
				\param x The x-position of the left edge.
				\param y The y-position of the top edge.
				\param width The width.
				\param height The height.
			 */
			Rectangle(coord_t x, coord_t y, coord_t width, coord_t height) noexcept;

			/**
				Creates a Rectangle of the given size, positioned at the origin.
				\param size The size to set.
			 */
			Rectangle(const Size& size) noexcept;
			
			/**
				Creates a Rectangle with the given size and position.
				\param position The position of the top-left
			 */
			Rectangle(const Point& position, const Size& size) noexcept;

			/**
				Sets the full set of values for the Rectangle.
				\param x The x-position of the left edge.
				\param y The y-position of the top edge.
				\param width The width.
				\param height The height.
			 */
			void set(coord_t x, coord_t y, coord_t width, coord_t height) noexcept;

			/**
				Sets the size of the Rectangle without changing its position.
				\param size The new size.
			 */
			void setSize(const Size& size) noexcept;

			/**
				Ensures that the Rectangle's width and height will fit into the given
				Size value.
				\param minimumSize The Size to pass in as a minimum size.
			 */
			void ensureSize(const Size& minimumSize) noexcept;

			/**
				Gets the size of the Rectangle, ignoring the position.
				\return The Rectangle's size.
			 */
			Size getSize() const noexcept;

			/**
				Sets the co-ordinates of the top-left corner of this Rectangle.
				\param position The new position.
			 */
			void setPosition(const Point& position) noexcept;

			/**
				Gets the Point at the top-left corner of this Rectangle.
				\return The top-left corner.
			 */
			Point getTopLeft() const noexcept { return Point(x, y); }

			/**
				Gets the Point at the top-right corner of this Rectangle.
				\return The top-right corner.
			 */
			Point getTopRight() const noexcept { return Point(x + width, y); }

			/**
				Gets the Point at the bottom-left corner of this Rectangle.
				\return The bottom-left corner.
			 */
			Point getBottomLeft() const noexcept { return Point(x, y + height); }

			/**
				Gets the Point at the bottom-right corner of this Rectangle.
				\return The bottom-right corner.
			 */
			Point getBottomRight() const noexcept { return Point(x + width, y + height); }

			/**
				Creates a Rectangle whose position is offset by the given width and height.
				\param x The amount to offset by in the horizontal direction.
				\param y The amount to offset by in the vertical direction.
			 */
			Rectangle offset(coord_t x, coord_t y) const noexcept;
			Rectangle offset(const Size& size) const noexcept { return offset(size.width, size.height); }
			Rectangle offset(const Point& point) const noexcept { return offset(point.x, point.y); }

			/**
				Gets the current position of the top-left corner of this Rectangle.
				\return The current position.
			 */
			Point getPosition() const noexcept;

			/**
				Tells whether the given point resides within the Rectangle.
				\param point The Point with co-ordinates to check.
			 */
			bool containsPoint(const Point& point) const noexcept;
			bool containsPoint(coord_t x, coord_t y) const noexcept;

			/**
				Deflates the rectangle by the given amount, moving each edge inwards.
				\param amount The amount to deflate by.
				\return This Rectangle.
			 */
			Rectangle deflate(int amount) const noexcept { return deflate(amount, amount); }
			Rectangle deflate(float amount) const noexcept { return deflate(amount, amount); }

			/**
				Gets a deflated copy of this Rectangle, deflated by the given amounts.
				This moves the edges inward on the horizontal and vertical axes.
				\param hamount The amount to move the left/right sides in.
				\param vamount The amount to move the top/bottom sides in.
				\return The Rectangle created.
			 */
			Rectangle deflate(int hamount, int vamount) const noexcept;
			Rectangle deflate(float hamount, float vamount) const noexcept;

			/**
				Inflates the Rectangle by the given amount, moving each edge outwards.
				\param amount The amount of inflate by.
				\return This Rectangle.
			 */
			Rectangle inflate(int amount) const noexcept { return deflate(-amount); }
			Rectangle inflate(float amount) const noexcept { return deflate(-amount); }

			/**
				Gets an inflated copy of this Rectangle, inflated by the given amounts.
				This moves the edges outward on the horizontal and vertical axes.
				\param hamount The amount to move the left/right sides out.
				\param vamount The amount to move the top/bottom sides out.
				\return The Rectangle created.
			 */
			Rectangle inflate(int hamount, int vamount) const noexcept { return deflate(-hamount, -vamount); }
			Rectangle inflate(float hamount, float vamount) const noexcept { return deflate(-hamount, -vamount); }

			/**
				Scales the size and position of this Rectangle by the given factor.
				\param factor The amount to multiply values by.
				\return The resulting scaled Rectangle.
			 */
			Rectangle scale(float factor) const noexcept;

			/**
				Compares the two Rectangles. They are equal if both size and
				positions are the same for both.
				\param other The Rectangle to compare with.
				\return `true` if equal, `false` otherwise.
			 */
			bool operator==(const Rectangle& other) const;

			/**
				Compares the two Rectangles. They are equal if both size and
				positions are the same for both.
				\param other The Rectangle to compare with.
				\return `false` if equal, `true` otherwise.
			 */
			bool operator!=(const Rectangle& other) const { return !operator==(other); }
		};
	}
}

#endif // _NATIVE_UI_RECTANGLE_H_

