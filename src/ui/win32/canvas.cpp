// System Dependencies
#include <windows.h>
#include <gdiplus.h>

// External Dependencies
#include "../../core/include/spinlock.h"
#include "../../core/include/system.h"

// Local Dependencies
#include "../include/canvas.h"
#include "../include/component.h"

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

		Canvas::Canvas(Component& component)
		{
			throw NotImplementedException();
		}

		Canvas::~Canvas()
		{
			if (_needsDelete)
			{
				delete (Gdiplus::Graphics*) _handle;
				::ReleaseDC(NULL, HDC(_auxHandle));
			}
		}

		void Canvas::fillRectangle(const Rectangle& area, const Brush& brush)
		{
			Gdiplus::Graphics* graphics = (Gdiplus::Graphics*) _handle;
			Gdiplus::Brush*    gdiBrush = (Gdiplus::Brush*) brush.getHandle();

			if (graphics->FillRectangle(gdiBrush, toGdiRect(area.scale(System::getDisplayScale()))) != Gdiplus::Ok)
				throw GraphicsException("Graphics::FillRectangle()");
		}
	}
}

