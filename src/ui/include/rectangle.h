#ifndef _NATIVE_UI_RECTANGLE_H_
#define _NATIVE_UI_RECTANGLE_H_ 1

// Core Dependencies
#include "../../core/include/types.h"

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
			int32_t x;			///< Horizontal co-ordinate of the top-left corner.
			int32_t y;			///< Vertical co-ordinate of the top-left corner.
			int32_t width;		///< Width of the rectangle.
			int32_t height;		///< Height of the rectangle.
		};
	}
}

#endif // _NATIVE_UI_RECTANGLE_H_

