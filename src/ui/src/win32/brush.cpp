// System Dependencies
#include <windows.h>
#include <gdiplus.h>

// External Dependencies
#include "../../../core/include/exception.h"

// Module Dependencies
#include "../../include/brush.h"

namespace native
{
	namespace ui
	{
		Brush::BrushHandle::~BrushHandle()
		{
			delete (Gdiplus::Brush*) handle;
		}

		Brush::Brush(const Color& color) : _shared(nullptr)
		{
			_shared->handle = new Gdiplus::SolidBrush(Gdiplus::Color(color.alpha, color.red, color.green, color.blue));
		}
	}
}

