// System Dependencies
#include <windows.h>
#include <gdiplus.h>

// External Dependencies
#include "../../core/include/spinlock.h"
#include "../../core/include/system.h"

// Local Dependencies
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
				Gdiplus::GdiplusStartupInput gdiplusStartupInput = { 0 };

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
			return Gdiplus::Rect(rectangle.x, rectangle.y, rectangle.width, rectangle.height);
		}

		Canvas::Canvas(handle_t handle, handle_t auxHandle) : _handle(handle), _auxHandle(auxHandle), _needsDelete(false)
		{
			if (auxHandle == nullptr)
				throw InvalidArgumentException();
		}

		Canvas::Canvas(Component& component) : _handle(nullptr), _auxHandle(nullptr), _needsDelete(true)
		{
			Component* tmp = &component;

			while (!tmp->getAdapter())
				tmp = (Component*) tmp->getParent();

			if (tmp == nullptr)
				throw InvalidArgumentException();

			ComponentAdapter* adapter = (ComponentAdapter*) tmp->getAdapter();

			_auxHandle = ::GetDC(HWND(adapter->getHandle()));
			_handle = new Gdiplus::Graphics(HDC(_auxHandle));
		}

		Canvas::~Canvas()
		{
			if (_needsDelete)
			{
				delete (Gdiplus::Graphics*) _handle;
				::ReleaseDC(NULL, HDC(_auxHandle));
			}
		}

		void Canvas::drawText(const String& text, const Font& font, const Point& point)
		{
			Gdiplus::Graphics* graphics = (Gdiplus::Graphics*) _handle;

			Gdiplus::SolidBrush brush(Gdiplus::Color(0, 0, 0));	// TODO: Different colors?
			Gdiplus::PointF pt(float(_offset.x + point.x) * System::getDisplayScale(), float(_offset.y + point.y) * System::getDisplayScale());

			if (graphics->DrawString(text.toArray(), int(text.getLength()), (const Gdiplus::Font*) font.getHandle(), pt, Gdiplus::StringFormat::GenericDefault(), &brush) != Gdiplus::Ok)
				throw GraphicsException("Graphics::DrawString");
		}

		Size Canvas::measureText(const String& text, const Font& font) const
		{
			Gdiplus::Graphics* graphics = (Gdiplus::Graphics*) _handle;
			Gdiplus::RectF rect;

			if (graphics->MeasureString(text.toArray(), int(text.getLength()), (Gdiplus::Font*) font.getHandle(), Gdiplus::PointF(0, 0), &rect) != Gdiplus::Ok)
				throw GraphicsException("Graphics::MeasureString() failed");

			return Size(coord_t(rect.Width + 1), coord_t(rect.Height));
		}

		void Canvas::drawRectangle(const Rectangle& rect, const Pen& pen)
		{
			Gdiplus::Graphics* graphics = (Gdiplus::Graphics*) _handle;
			Gdiplus::Pen* gdiPen = (Gdiplus::Pen*) pen.getHandle();

			// Perform the draw operation.
			if (graphics->DrawRectangle(gdiPen, toGdiRect(rect.offset(_offset).deflate(pen.getThickness() / 2).scale(System::getDisplayScale()))) != Gdiplus::Ok)
				throw GraphicsException("Graphics::DrawRectangle()");
		}

		void Canvas::fillRectangle(const Rectangle& rect, const Brush& brush)
		{
			Gdiplus::Graphics* graphics = (Gdiplus::Graphics*) _handle;
			Gdiplus::Brush*    gdiBrush = (Gdiplus::Brush*) brush.getHandle();

			if (graphics->FillRectangle(gdiBrush, toGdiRect(rect.offset(_offset).scale(System::getDisplayScale()))) != Gdiplus::Ok)
				throw GraphicsException("Graphics::FillRectangle()");
		}
	}
}

