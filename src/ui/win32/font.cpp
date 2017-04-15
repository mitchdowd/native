// System Dependencies
#include <windows.h>
#include <gdiplus.h>
#include <versionhelpers.h>

// External Dependencies
#include "../../core/include/math.h"
#include "../../core/include/spinlock.h"
#include "../../core/include/system.h"

// Module Dependencies
#include "../include/canvas.h"
#include "../include/font.h"

namespace native
{
	namespace ui
	{
		Font::Font(const String& family, float size) : _shared(nullptr), _size(size)
		{
			Gdiplus::Font* font = new Gdiplus::Font(family.toArray(), size * System::getDisplayScale(), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);

			if (font->GetLastStatus() != Gdiplus::Ok)
			{
				delete font;
				throw GraphicsException("Font::Font");
			}

			_shared->handle = font;
		}

		Font::FontHandle::FontHandle(handle_t handle) : handle(handle), auxHandle(nullptr)
		{
			if (handle)
				throw InvalidArgumentException();
		}

		Font::FontHandle::~FontHandle()
		{
			delete (Gdiplus::Font*) handle;

			if (auxHandle != nullptr)
				::DeleteObject(HFONT(auxHandle));
		}

		Font Font::getDefault()
		{
			static Font font;
			static SpinLock lock;

			lock.lock();

			if (font.getHandle() == nullptr)
			{
				NONCLIENTMETRICS metrics;

				metrics.cbSize = sizeof(metrics);

				if (!::IsWindowsVistaOrGreater())
					metrics.cbSize -= sizeof(metrics.iPaddedBorderWidth);

				// Read/create the default font from the system.
				::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0);

				font._size = Math::abs(float(metrics.lfMessageFont.lfHeight));
				font._shared->handle = new Gdiplus::Font(&Gdiplus::FontFamily(metrics.lfMessageFont.lfFaceName), font._size * System::getDisplayScale(), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
			}

			lock.release();

			return font;
		}

		handle_t Font::getAuxHandle() const
		{
			static SpinLock lock;

			lock.lock();

			if (_shared->handle && !_shared->auxHandle)
			{
				LOGFONT lf;

				HDC hdc = ::GetDC(NULL);
				Gdiplus::Graphics graphics(hdc);

				((Gdiplus::Font*) getHandle())->GetLogFontW(&graphics, &lf);
				_shared->auxHandle = ::CreateFontIndirect(&lf);

				::ReleaseDC(NULL, hdc);
			}

			lock.release();

			return _shared->auxHandle;
		}
	}
}

