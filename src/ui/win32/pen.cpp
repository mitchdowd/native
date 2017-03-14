// System Dependencies
#include <windows.h>
#include <gdiplus.h>

// Module Dependencies
#include "../include/canvas.h"
#include "../include/pen.h"

namespace native
{
	namespace ui
	{
		Pen::Pen(const Color& color, float width) : _shared(nullptr), _thickness(width)
		{
			Gdiplus::Pen* pen = new Gdiplus::Pen(Gdiplus::Color(color.alpha, color.red, color.green, color.blue), width);

			if (pen->GetLastStatus() != Gdiplus::Ok)
			{
				delete pen;
				throw GraphicsException("Pen::Pen");
			}

			_shared->handle = pen;
		}

		Pen::PenHandle::~PenHandle()
		{
			delete (Gdiplus::Pen*) handle;
		}
	}
}

