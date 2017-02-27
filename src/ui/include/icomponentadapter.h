#ifndef _NATIVE_UI_ICOMPONENT_ADAPTER_H_
#define _NATIVE_UI_ICOMPONENT_ADAPTER_H_ 1

// External Dependencies
#include "../../core/include/string.h"

// Module Dependencies
#include "rectangle.h"

namespace native
{
	namespace ui
	{
		// Forward Declarations
		class Canvas;
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
			virtual ~IComponentAdapter() {}

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
				Sets the area occupied by this adapter, relative to its parent
				adapter (not necessarily the parent Component).
				\param area The area to set.
			 */
			virtual void setArea(const Rectangle& area) = 0;

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
				Paints the component however the system usually would.
				\param canvas The Canvas to paint with.
			 */
			virtual void doPaint(Canvas& canvas) = 0;
		};
	}
}

#endif // _NATIVE_UI_ICOMPONENT_ADAPTER_H_