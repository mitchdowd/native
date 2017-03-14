#ifndef _NATIVE_UI_FONT_H_
#define _NATIVE_UI_FONT_H_ 1

// External Dependencies
#include "../../core/include/shared.h"

namespace native
{
	namespace ui
	{
		/**
			Describes a Font which can be used to draw text.
		 */
		class Font
		{
		public:
			/** Create an invalid Font handle. */
			Font() : _shared(nullptr) {}

			/**
				Gets the system resource handle.
				\return The system resource handle.
			*/
			handle_t getHandle() const noexcept { return _shared->handle; }

		private:
			/** Self-destroying Font handle. */
			struct FontHandle
			{
				// Lifecycle Functions
				FontHandle(handle_t handle) : handle(handle) {}
				~FontHandle();

				// Instance Varaibles
				handle_t handle;
			};

			// Instance Variables
			Shared<FontHandle> _shared;

		};
	}
}

#endif // _NATIVE_UI_FONT_H_

