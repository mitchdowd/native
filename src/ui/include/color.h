#ifndef _NATIVE_UI_COLOR_H_
#define _NATIVE_UI_COLOR_H_ 1

// External Dependencies
#include "../../core/include/types.h"

namespace native
{
	namespace ui
	{
		/**
			Color is a structure which defines a 32-bit, paintable color.
		 */
		class Color
		{
		public:
			// Public Properties
			byte_t red;				///< Red component of the color.
			byte_t green;			///< Green component of the color.
			byte_t blue;			///< Blue component of the color.
			byte_t alpha;			///< Opacity of the color.

			/**
				Creates a Color from its RGB components. It will have no
				transparency.
				\param r The red component.
				\param g The green component.
				\param b The blue component.
			 */
			Color(byte_t r, byte_t g, byte_t b) : red(r), green(g), blue(b), alpha(0xFF) {}
		};
	}
}

#endif // _NATIVE_UI_COLOR_H_

