// System Dependencies
#include <windows.h>
#include <gdiplus.h>

// Module Dependencies
#include "../include/pen.h"

namespace native
{
	namespace ui
	{
		Pen::Pen(const Color& color, float width) : _shared(nullptr), _thickness(width)
		{
			_shared->handle = new Gdiplus::Pen(Gdiplus::Color(color.alpha, color.red, color.green, color.blue), width);
		}

		Pen::PenHandle::~PenHandle()
		{
			delete (Gdiplus::Pen*) handle;
		}
	}
}

