// System Dependencies
#include <Windows.h>
#include <gdiplus.h>
#include <VersionHelpers.h>

// External Dependencies
#include "../../core/include/math.h"
#include "../../core/include/spinlock.h"

// Module Dependencies
#include "../include/app.h"
#include "../include/canvas.h"
#include "../include/font.h"

namespace native
{
	namespace ui
	{
		Font::Font(const String& family, float size) : _shared(nullptr), _size(size)
		{
			Gdiplus::Font* font = new Gdiplus::Font(family.toArray(), size * App::getDisplayScale(), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);

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

		Size Font::measureText(const String& text) const
		{
			if (text.getLength() == 0)
				return { 0, 0 };

			Gdiplus::Graphics graphics = HWND(NULL);
			Gdiplus::RectF rect;

			if (graphics.MeasureString(text.toArray(), int(text.getLength()), (Gdiplus::Font*) getHandle(), Gdiplus::PointF(0, 0), &rect) != Gdiplus::Ok)
				throw GraphicsException("Graphics::MeasureString() failed");

			return { coord_t(rect.Width / App::getDisplayScale()), coord_t(rect.Height / App::getDisplayScale()) };
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
				font._shared->handle = new Gdiplus::Font(&Gdiplus::FontFamily(metrics.lfMessageFont.lfFaceName), font._size * App::getDisplayScale(), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
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

