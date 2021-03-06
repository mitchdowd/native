#ifndef _NATIVE_UI_BRUSH_H_
#define _NATIVE_UI_BRUSH_H_ 1

// External Dependencies
#include "../../core/include/shared.h"

// Module Dependencies
#include "color.h"

namespace native
{
	namespace ui
	{
		/**
			A Brush is used to fill paint a region.
		 */
		class Brush
		{
		public:
			/** Create an invalid Brush handle. */
			Brush() : _shared(nullptr) {}

			/**
				Creates a Brush which is a solid single color.
				\param color The color of the brush.
			 */
			Brush(const Color& color);

			/**
				Gets the main (primary) color for this brush.
				\return The main color.
			 */
			Color getPrimaryColor() const;

			/**
				Gets the system resource handle.
				\return The system resource handle.
			 */
			handle_t getHandle() const noexcept { return _shared->handle; }

		protected:
			/**
				Creates a Brush with the given system handle. Good for subclasses
				to instantiate with their own logical brush.
				\param handle The system handle.
			 */
			Brush(handle_t handle) : _shared(handle) {}

		private:
			/** Self-destroying Brush handle. */
			struct BrushHandle
			{
				// Lifecycle Functions
				BrushHandle(handle_t handle) : handle(handle) {}
				~BrushHandle();

				// Instance Varaibles
				handle_t handle;
			};

			// Instance Variables
			Shared<BrushHandle> _shared;
		};
	}
}

#endif // _NATIVE_UI_BRUSH_H_

