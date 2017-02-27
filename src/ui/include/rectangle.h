#ifndef _NATIVE_UI_RECTANGLE_H_
#define _NATIVE_UI_RECTANGLE_H_ 1

// Module Dependencies
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
				Sets the size of the Rectangle without changing its position.
				\param size The new size.
			 */
			void setSize(const Size& size) noexcept;

			/**
				Gets the size of the Rectangle, ignoring the position.
				\return The Rectangle's size.
			 */
			Size getSize() const noexcept;

			/**
				Scales the size and position of this Rectangle by the given factor.
				\param factor The amount to multiply values by.
				\return The resulting scaled Rectangle.
			 */
			Rectangle scale(float factor) const noexcept;
		};
	}
}

#endif // _NATIVE_UI_RECTANGLE_H_

