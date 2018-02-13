// System Dependencies
#include <Windows.h>
#include <gdiplus.h>

// Library Dependencies
#include "../include/bitmap.h"

namespace native
{
	namespace ui
	{
		Bitmap::BitmapHandle::BitmapHandle(handle_t handle) : handle(handle)
		{
		}

		Bitmap::BitmapHandle::~BitmapHandle()
		{
			delete (Gdiplus::Bitmap*) handle;
		}
	}
}

