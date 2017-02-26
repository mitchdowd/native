// System Dependencies
#include <windows.h>
#include <gdiplus.h>

// External Dependencies
#include "../../../core/include/spinlock.h"

// Local Dependencies
#include "../../include/canvas.h"
#include "../../include/component.h"

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

		Canvas::Canvas(Component& component)
		{
			throw NotImplementedException();
		}

		Canvas::~Canvas()
		{
			// TODO
		}

		void Canvas::fillRectangle(const Rectangle& area, const Brush& brush)
		{
			throw NotImplementedException();
		}
	}
}

