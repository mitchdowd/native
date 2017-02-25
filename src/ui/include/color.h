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
			byte_t red;
			byte_t green;
			byte_t blue;
			byte_t alpha;
		};
	}
}

#endif // _NATIVE_UI_COLOR_H_

