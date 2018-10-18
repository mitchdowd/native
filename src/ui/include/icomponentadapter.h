#ifndef _NATIVE_UI_ICOMPONENT_ADAPTER_H_
#define _NATIVE_UI_ICOMPONENT_ADAPTER_H_ 1

// External Dependencies
#include "../../core/include/function.h"
#include "../../core/include/string.h"

// Module Dependencies
#include "rectangle.h"

namespace native
{
	namespace ui
	{
		// Forward Declarations
		class Canvas;
		class Font;
		struct InputEvent;
		struct ComponentEvent;

		/**
			A pure virtual interface for interacting with native UI components.
			An adapter gets attached to a Component, giving the Component native
			functionality.
		 */
		class IComponentAdapter
		{
		public:
			/** Virtual destructor. */
			virtual ~IComponentAdapter() = default;

			/**
				Sets the native parent of this native component. The parent should
				be of the same concrete type as this instance (i.e. Don't mix native
				components with mock components, etc).
				\param parent The parent component adapter.
			 */
			virtual void setParent(IComponentAdapter* parent) = 0;

			/**
				Shows or hides the Component, according to the parameter.
				\param visible Set `true` to show, `false` to hide.
			*/
			virtual void setVisible(bool visible) = 0;

			/**
				Determines whether the Component is currently visible or not.
				\return true if visible, false if not.
			 */
			virtual bool isVisible() const = 0;

			/**
				Enables or disables the Component.
				\param enable true to enable, false to disable.
			 */
			virtual void setEnabled(bool enable) = 0;

			/**
				Sets the area occupied by this adapter, relative to its parent
				adapter (not necessarily the parent Component).
				\param area The area to set.
			 */
			virtual void setArea(const Rectangle& area) = 0;

			/**
				Gets the total area of the Component relative to its parent
				adapter (not necessarily the parent Component).
				\return The Component's area.
			 */
			virtual Rectangle getArea() const = 0;

			/**
				Gets the content area of the Component, relative to its non-content
				area.
				\return The content area.
			 */
			virtual Rectangle getContentArea() const = 0;

			/**
				Sets the component's text, for those that support text.
				\param text The text to set.
			 */
			virtual void setText(const String& text) = 0;

			/**
				Sets the Font this component will draw its text with.
				\param font The Font to draw text with.
			 */
			virtual void setFont(const Font& font) = 0;

			/**
				For retrieving the system handle, if there is one.
				\return The system resource handle.
			 */
			virtual handle_t getHandle() const noexcept = 0;

			/**
				Invalidates the painted area, causing it to be scheduled to be
				repainted.
				\param area The area to invalidate.
			 */
			virtual void invalidate(const Rectangle& area) = 0;

			/**
				Performs default processing of an input event.
				\param event The event to process.
			 */
			virtual void doInput(const InputEvent& event) = 0;


			/**
				Paints the component however the system usually would.
				\param canvas The Canvas to paint with.
			 */
			virtual void doPaint(Canvas& canvas) = 0;

			/**
				Adds the given Function to the message queue to be called during
				the main UI event loop.
				\param func The Function to add to the message queue.
			 */
			virtual void invokeAsync(const Function<void>& func) = 0;
		};
	}
}

#endif // _NATIVE_UI_ICOMPONENT_ADAPTER_H_
