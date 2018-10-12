#ifndef _NATIVE_UI_CANVAS_H_
#define _NATIVE_UI_CANVAS_H_ 1

// External Dependencies
#include "../../core/include/exception.h"

// Local Dependencies
#include "brush.h"
#include "font.h"
#include "pen.h"
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
				Creates a Canvas from one or more system handles. Mostly used for
				internal purposes.
				\param handle The main system handle.
				\param auxHandle An optional secondary handle.
			 */
			Canvas(handle_t handle, handle_t auxHandle = nullptr);

			/** Destructor. */
			~Canvas();

			/**
				Draws a String of text using a given Font at a particular point.
				The Point corresponds to the top-left corner of the line of text.
				\param text The text to draw.
				\param font The Font to draw the text with.
				\param point The location to draw the text at.
			 */
			void drawText(const String& text, const Font& font, const Point& point = Point());

			/**
				Draws a Rectangle outline within the given rectangle. The outer
				edge of the drawn rectangle's line will sit on the specified
				Rectangle co-ordinates.
				\param rect The outer edge of the Rectangle to draw.
				\param pen The pen to draw the line with.
			 */
			void drawRectangle(const Rectangle& rect, const Pen& pen);

			/**
				Draws a Rectangle within the given area. The outer edge of
				the drawn rectangle's line will sit on the Rectangle 
				co-ordinates. The pen and brush provide the border and fill
				color respectively.
				\param rect The outer edge of the Rectangle to draw.
				\param pen The pen to draw the border with.
				\param brush The brush to fill the rectangle with.
			 */
			void drawRectangle(const Rectangle& rect, const Pen& pen, const Brush& brush);

			/**
				Fills the specified Rectangle with the given Brush.
				\param rect The rectangle to fill.
				\param brush The Brush to paint the area with.
			 */
			void fillRectangle(const Rectangle& rect, const Brush& brush);

			/**
				Offsets future drawing operations by the given amount.
				\param offset Distances to offset by.
			 */
			void offset(const Point& offset) { _offset.x += offset.x; _offset.y += offset.y; }

			/**
				Gets the system resource handle for this Canvas.
				\return System resource handle.
			 */
			handle_t getHandle() const noexcept { return _handle; }

			/**
				Gets the secondary system handle, if there is one.
				\return The secondary system handle.
			 */
			handle_t getAuxHandle() const noexcept { return _auxHandle; }

		private:
			// Instance Variables
			handle_t _handle;
			handle_t _auxHandle;
			Point    _offset;
		};

		/**
			An error occurred in a graphics/drawing operation.
		 */
		class GraphicsException : public Exception
		{
		public:
			/**
				Creates a GraphicsException with an error message.
				\param message Error message.
			 */
			GraphicsException(const char* message) : Exception(message) {}
		};
	}
}

#endif // _NATIVE_UI_CANVAS_H_

