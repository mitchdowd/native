#ifndef _NATIVE_UI_PEN_H_
#define _NATIVE_UI_PEN_H_ 1

// External Dependencies
#include "../../core/include/shared.h"

// Module Dependencies
#include "color.h"

namespace native
{
	namespace ui
	{
		/**
			A Pen is used to draw lines on a Canvas.
		 */
		class Pen
		{
		public:
			/** Create an invalid Pen handle. */
			Pen() : _shared(nullptr), _thickness(0) {}

			/**
				Creates a Pen which is a solid single color.
				\param color The color of the brush.
				\param width The width of the pen stroke.
			 */
			Pen(const Color& color, float width = 1.0f);

			/**
				Gets the Color of this Pen.
				\return The Pen's color.
			 */
			Color getColor() const noexcept { return _color; }

			/**
				Gets the thickness of the Pen's drawing line, in pixels.
				\return The Pen's thickness.
			 */
			float getThickness() const noexcept { return _thickness; }

			/**
				Gets the system resource handle.
				\return The system resource handle.
			 */
			handle_t getHandle() const noexcept { return _shared->handle; }

		private:
			/** Shared pen handle, allowing Pen to be passed by value. */
			struct PenHandle 
			{
				// Lifecycle Functions
				PenHandle(handle_t handle) : handle(handle) {}
				~PenHandle();

				// Instance Variables
				handle_t handle;
			};

			// Instance Variables
			Shared<PenHandle> _shared;
			float _thickness;
			Color _color;
		};
	}
}

#endif // _NATIVE_UI_PEN_H_

