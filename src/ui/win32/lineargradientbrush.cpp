// System Dependencies
#include <windows.h>
#include <gdiplus.h>

// Module Dependencies
#include "../include/canvas.h"
#include "../include/lineargradientbrush.h"

namespace native
{
	namespace ui
	{
		static Gdiplus::Brush* CreateBrush(Point p0, Point p1, Color c0, Color c1)
		{
			Gdiplus::Brush* brush = new Gdiplus::LinearGradientBrush(
				Gdiplus::Point(p0.x, p0.y),
				Gdiplus::Point(p1.x, p1.y),
				Gdiplus::Color(c0.alpha, c0.red, c0.green, c0.blue),
				Gdiplus::Color(c1.alpha, c1.red, c1.green, c1.blue)
			);

			if (brush->GetLastStatus() != Gdiplus::Ok)
			{
				delete brush;
				throw GraphicsException("LinearGradientBrush::LinearGradientBrush");
			}

			return brush;
		}

		LinearGradientBrush::LinearGradientBrush(Point p0, Point p1, Color c0, Color c1) 
			: Brush(CreateBrush(p0, p1, c0, c1))
		{
		}
	}
}

