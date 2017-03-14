// System Dependencies
#include <windows.h>
#include <gdiplus.h>
#include <versionhelpers.h>

// External Dependencies
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

		Font::FontHandle::~FontHandle()
		{
			delete (Gdiplus::Font*) handle;
		}
	}
}

