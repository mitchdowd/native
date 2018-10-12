#ifndef _NATIVE_LINEAR_GRADIENT_BRUSH_H_
#define _NATIVE_LINEAR_GRADIENT_BRUSH_H_ 1

// Module Dependencies
#include "brush.h"
#include "point.h"

namespace native
{
	namespace ui
	{
		class LinearGradientBrush : public Brush
		{
		public:
			LinearGradientBrush(Point p0, Point p1, Color c0, Color c1);
		};
	}
}

#endif // _NATIVE_LINEAR_GRADIENT_BRUSH_H_

