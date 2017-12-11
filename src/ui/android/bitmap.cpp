// External Dependencies
#include "../../../lib/jnipp/jnipp.h"

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
			delete (jni::Object*) handle;
		}
	}
}

