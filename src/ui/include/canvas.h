#ifndef _NATIVE_UI_CANVAS_H_
#define _NATIVE_UI_CANVAS_H_ 1

// Local Dependencies
#include "brush.h"
#include "rectangle.h"

namespace native
{
	namespace ui
	{
		// Forward Declarations
		class Component;

		/**
			The Canvas encapsulates a paintable medium (such as a Component),
			allowing that object to be drawn upon using the various Canvas functions.
		 */
		class Canvas
		{
		public:
			/**
				Creates a Canvas which draws within the confines of the specified
				Component.
				\param component The Component to draw within.
			 */
			Canvas(Component& component);

			/** Destructor. */
			~Canvas();

			/**
				Fills the specified Rectangle with the given Brush.
				\param area The area to fill.
				\param brush The Brush to paint the area with.
			 */
			void fillRectangle(const Rectangle& area, const Brush& brush);

			/**
				Gets the system resource handle for this Canvas.
				\return System resource handle.
			 */
			handle_t getHandle() const noexcept { return _handle; }

		private:
			// Instance Variables
			handle_t _handle;
		};
	}
}

#endif // _NATIVE_UI_CANVAS_H_

