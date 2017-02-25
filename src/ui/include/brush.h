#ifndef _NATIVE_UI_BRUSH_H_
#define _NATIVE_UI_BRUSH_H_ 1

// Module Dependencies
#include "color.h"

namespace native
{
	namespace ui
	{
		/**
			A Brush is used to fill paint a region.
		 */
		class Brush
		{
		public:
			/** Gets a default Brush. */
			Brush();

			/**
				Creates a Brush which is a solid single color.
				\param color The color of the brush.
			 */
			Brush(const Color& color);

			/** Destructor. */
			~Brush();
		};
	}
}

#endif // _NATIVE_UI_BRUSH_H_

