#ifndef _NATIVE_UI_BITMAP_H_
#define _NATIVE_UI_BITMAP_H_ 1

// External Dependencies
#include "../../core/include/shared.h"

namespace native
{
	namespace ui
	{
		/**
			Bitmap is an off-screen image representation. Bitmap is implemented as
			an underlying platform construct, allowing it to work well directly with
			the system's display drivers.
		 */
		class Bitmap
		{
		public:
			/** Create an invalid Bitmap handle. */
			Bitmap() : _shared(nullptr) {}

			/**
				Gets the system resource handle.
				\return The system resource handle.
			*/
			handle_t getHandle() const noexcept { return _shared->handle; }

		private:
			/** Self-destroying Bitmap handle. */
			struct BitmapHandle
			{
				BitmapHandle(handle_t handle);
				~BitmapHandle();

				handle_t handle;
			};

			// Instance Variables
			Shared<BitmapHandle> _shared;
		};
	}
}

#endif // _NATIVE_UI_BITMAP_H_

