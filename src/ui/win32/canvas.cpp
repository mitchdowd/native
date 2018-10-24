// System Dependencies
#include <Windows.h>
#include <gdiplus.h>

// External Dependencies
#include "../../core/include/spinlock.h"

// Local Dependencies
#include "../include/app.h"
#include "../include/canvas.h"
#include "../include/component.h"
#include "../include/componentadapter.h"

// External Libraries
#pragma comment(lib, "gdiplus.lib")

namespace native
{
	namespace ui
	{
		/** Calls some initialization functions needed by GDI+. */
		class GraphicsInitializer
		{
		public:
			GraphicsInitializer();
		};

		GraphicsInitializer::GraphicsInitializer()
		{
			static bool isRegistered = false;
			static SpinLock lock;
			static ULONG_PTR gdiPlusToken = 0;

			lock.lock();

			if (!isRegistered)
			{
				Gdiplus::GdiplusStartupInput gdiplusStartupInput = {};

				// Initialise the Gdi+ library.
				Gdiplus::GdiplusStartup(&gdiPlusToken, &gdiplusStartupInput, NULL);
				isRegistered = true;
			}

			lock.release();
		}

		// Static Constants
		static const GraphicsInitializer initializer;

		static Gdiplus::Rect toGdiRect(const Rectangle& rectangle)
		{
			return { rectangle.x, rectangle.y, rectangle.width, rectangle.height };
		}

		static Gdiplus::RectF toGdiRectF(const Rectangle& rectangle)
		{
			return { float(rectangle.x), float(rectangle.y), float(rectangle.width), float(rectangle.height) };
		}

		Canvas::Canvas(handle_t handle, handle_t auxHandle) : _handle(handle), _auxHandle(auxHandle)
		{
			if (auxHandle == nullptr)
				throw InvalidArgumentException();
		}

		Canvas::~Canvas()
		{
		}

		void Canvas::drawText(const String& text, const Font& font, const Point& point)
		{
			if (text.getLength() > 0)
			{
				Gdiplus::Graphics* graphics = (Gdiplus::Graphics*) _handle;

				Gdiplus::SolidBrush brush(Gdiplus::Color(0, 0, 0));	// TODO: Different colors?
				Gdiplus::PointF pt(float(_offset.x + point.x) * App::getDisplayScale(), float(_offset.y + point.y) * App::getDisplayScale());

				if (graphics->DrawString(text.toArray(), int(text.getLength()), (const Gdiplus::Font*) font.getHandle(), pt, Gdiplus::StringFormat::GenericDefault(), &brush) != Gdiplus::Ok)
					throw GraphicsException("Graphics::DrawString");
			}
		}

		void Canvas::drawText(const String& text, const Font& font, const Rectangle& area, Flags<Align> align)
		{
			if (text.getLength() > 0)
			{
				Gdiplus::Graphics* graphics = (Gdiplus::Graphics*) _handle;

				Gdiplus::SolidBrush brush(Gdiplus::Color(0, 0, 0));	// TODO: Different colors?
				Gdiplus::RectF rect = toGdiRectF(area.offset(_offset).scale(App::getDisplayScale()));
				Gdiplus::StringFormat format;

				// Parse out the horizontal alignment.
				switch (align.getData() & uint32_t(Align::Horizontal))
				{
				case int(Align::HCenter):
					format.SetAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
					break;

				case int(Align::Right):
					format.SetAlignment(Gdiplus::StringAlignment::StringAlignmentFar);
					break;

				case int(Align::Left):
				case int(Align::HFill):
				default:
					format.SetAlignment(Gdiplus::StringAlignment::StringAlignmentNear);
					break;
				}

				// Parse out the vertical alignment.
				switch (align.getData() & uint32_t(Align::Vertical))
				{
				case int(Align::VCenter):
					format.SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
					break;

				case int(Align::Bottom):
					format.SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentFar);
					break;

				case int(Align::Top):
				case int(Align::VFill):
				default:
					format.SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentNear);
					break;
				}

				if (graphics->DrawString(text.toArray(), int(text.getLength()), (const Gdiplus::Font*) font.getHandle(), rect, &format, &brush) != Gdiplus::Ok)
					throw GraphicsException("Graphics::DrawString");
			}
		}

		void Canvas::drawRectangle(const Rectangle& rect, const Pen& pen)
		{
			Gdiplus::Graphics* graphics = (Gdiplus::Graphics*) _handle;
			Gdiplus::Pen* gdiPen = (Gdiplus::Pen*) pen.getHandle();

			// Perform the draw operation.
			if (graphics->DrawRectangle(gdiPen, toGdiRect(rect.offset(_offset).deflate(pen.getThickness() / 2).scale(App::getDisplayScale()))) != Gdiplus::Ok)
				throw GraphicsException("Graphics::DrawRectangle()");
		}

		void Canvas::drawRectangle(const Rectangle& rect, const Pen& pen, const Brush& brush)
		{
			fillRectangle(rect.deflate(pen.getThickness()), brush);
			drawRectangle(rect, pen);
		}

		void Canvas::fillRectangle(const Rectangle& rect, const Brush& brush)
		{
			Gdiplus::Graphics* graphics = (Gdiplus::Graphics*) _handle;
			Gdiplus::Brush*    gdiBrush = (Gdiplus::Brush*) brush.getHandle();

			if (graphics->FillRectangle(gdiBrush, toGdiRect(rect.offset(_offset).scale(App::getDisplayScale()))) != Gdiplus::Ok)
				throw GraphicsException("Graphics::FillRectangle()");
		}
	}
}

