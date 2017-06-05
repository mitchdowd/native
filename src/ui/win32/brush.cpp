// System Dependencies
#include <windows.h>
#include <gdiplus.h>

// Module Dependencies
#include "../include/brush.h"
#include "../include/canvas.h"

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
			Gdiplus::Brush* brush = new Gdiplus::SolidBrush(Gdiplus::Color(color.alpha, color.red, color.green, color.blue));

			if (brush->GetLastStatus() != Gdiplus::Ok)
			{
				delete brush;
				throw GraphicsException("Brush::Brush");
			}

			_shared->handle = brush;
		}

		Color Brush::getPrimaryColor() const
		{
			Gdiplus::Color gdiColor;

			switch (((Gdiplus::Brush*) getHandle())->GetType())
			{
			case Gdiplus::BrushType::BrushTypeSolidColor:
				((Gdiplus::SolidBrush*) getHandle())->GetColor(&gdiColor);
				return Color::fromArgb(gdiColor.GetValue());

			default:
				throw InvalidStateException("Brush not in a supported state to determine its primary color");
			}
		}
	}
}

