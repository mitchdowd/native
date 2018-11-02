#ifndef _NATIVE_UI_POINT_H_
#define _NATIVE_UI_POINT_H_ 1

// External Modules
#include "../../core/include/types.h"

namespace native
{
	namespace ui
	{
		/**
			Represents a point location in 2-dimensional space.
		*/
		class Point
		{
		public:
			coord_t x;		///< The x co-ordinate.
			coord_t y;		///< The y co-ordinate.

			/**
				Creates a Point at the origin (0, 0).
			 */
			Point() noexcept : x(0), y(0) {}

			/**
				Creates a point at the given x,y co-ordinates.
				\param x The X (horizontal) position.
				\param y The Y (vertical) position.
			 */
			Point(coord_t x, coord_t y) noexcept;

			/**
				Sets the point values.
				\param x The x co-ordinate.
				\param y The y co-ordinate.
			 */
			void set(coord_t x, coord_t y) noexcept;

			/**
				Gives the distance between this point and another Point.
				\param other The Point to measure from.
				\return The distance, as a positive value.
			 */
			coord_t distanceFrom(Point other) noexcept;

			/**
				Gets a copy of this Point, with the +/- signs of the co-ordinates
				reversed.
				\return A negated copy of the Point.
			 */
			Point inverse() const { return { -x, -y }; }

			/**
				Offsets the point by the given amounts in x and y axes.
				\param xamount The horizontal amount to offset by.
				\param yamount The vertical amount to offset by.
				\return The offset point.
			 */
			Point offset(coord_t xamount, coord_t yamount) const { return { x + xamount, y + yamount }; }
			Point offset(const Point& amounts) const { return offset(amounts.x, amounts.y); }

			/**
			    Scales the point out, multiplying its co-ordinates by the given amount.
			    \param amount The amount to scale the point by.
			    \return The scaled out point.
			 */
			Point scale(float amount) const { return { coord_t(x * amount), coord_t(y * amount) }; }

			/**
				Compares two Points.
				\param other The Point to compare with.
				\return `true` if equal, `false` if not.
			 */
			bool operator==(const Point& other) const { return x == other.x && y == other.y; }

			/**
				Compares two Points.
				\param other The Point to compare with.
				\return `false` if equal, `true` if not.
			 */
			bool operator!=(const Point& other) const { return !operator==(other); }
		};
	}
}

#endif // _NATIVE_UI_POINT_H_

