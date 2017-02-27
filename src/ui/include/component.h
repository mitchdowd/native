#ifndef _NATIVE_UI_COMPONENT_H_
#define _NATIVE_UI_COMPONENT_H_ 1

// External Dependencies
#include "../../core/include/exception.h"

// Module Dependencies
#include "brush.h"
#include "canvas.h"
#include "icomponentadapter.h"

namespace native
{
	namespace ui
	{
		// Forward Declarations
		class LayoutComponent;

		/**
			The base class for user interface elements.
		 */
		class Component
		{
		public:
			/** Default constructor. */
			Component();

			/** Destructor. */
			virtual ~Component();

			/**
				Creates a Component with a particular native component adatper.
				\param adapter The adapter, giving native Component behavior.
			 */
			Component(IComponentAdapter* adapter);

			/**
				Sets the parent Component for this Component. If a null parent
				is set, this becomes a top-level Component. Not all Component
				types can necessarily exist as a top-level Component.
				\param parent The new parent Component.
			 */
			void setParent(LayoutComponent* parent);
			void setParent(LayoutComponent& parent) { setParent(&parent); }

			/**
				Gets the currently-set parent for this Component.
			 	\return The Component's parent, or nullptr.
			 */
			LayoutComponent* getParent() const noexcept { return _parent; }

			/**
				Shows or hides the Component, according to the parameter. A
				Component is visible by default, but will be hidden if its
				parent is hidden. Top-level Components are the exception, and
				are hidden by default.
				\param visible Set `true` to show, `false` to hide.
			 */
			void setVisible(bool visible);

			/**
				Determines whether the Component is currently visible or not.
				\return true if visible, false if not.
			 */
			bool isVisible() const;

			/**
				Sets tha are used by this Component, relative to the top-left
				co-ordinates of its parent Component. This does not take things
				such as margins or alignment into account.
				\param area The new area to set.
			 */
			void setArea(const Rectangle& area);

			/**
				Gets the current area, relative to the parent Component.
				\return The current Area.
			 */
			Rectangle getArea() const { return _area; }

			/**
				Gets the usable portion of this Component's area, relative to
				the Component's top-left corner. For many Components this will
				simply be the size of the Component, located at the origin, but
				things such as borders will shrink the usable content area.
				\return The content area.
			 */
			Rectangle getContentArea() const;

			/**
				Sets the Brush used to paint this Component's background.
				\param background The background Brush.
			 */
			void setBackground(const Brush& background);

			/**
				Gets the Brush currently used to paint the background.
				\return The background brush.
			 */
			Brush getBackground() const;

			/**
				Gets this Component's adapter, if it has one.
				\return The adapter this Component was created with.
			 */
			IComponentAdapter* getAdapter() const noexcept { return _adapter; }

			/**
				For internal use only in triggering the repaint sequence.
				\param canvas The canvas to paint with.
			 */
			virtual void dispatchPaintEvent(Canvas& canvas);

			/**
				For internal use only. Updates the Rectangle's area in response
				to user input (e.g. Resizing a Window).
				\param area The new area.
			 */
			void updateArea(const Rectangle& area) { _area = area; }

		protected:
			/**
				This is where the painting of the Component occurs. Override to
				do your own custom painting. By default, this paints the background
				on the entire Component's content area.
				\param canvas The Canvas with which to paint.
			 */
			virtual void onPaint(Canvas& canvas);

			/** For internal use only. */
			virtual void setParentAdapter(IComponentAdapter* parent);

		private:
			// Class Friendships
			friend class LayoutComponent;

			// Private Types
			enum Visibility { Inherit, Show, Hide };

			// Instance Variables
			IComponentAdapter* _adapter;
			LayoutComponent*   _parent;
			Visibility		   _visibility;
			Rectangle		   _area;
			Brush              _background;
		};

		/**
			Thrown when a user interface operation fails.
		 */
		class UserInterfaceException : public Exception
		{
		public:
			UserInterfaceException(const char* message = "User interface error occurred") : Exception(message) {}
		};
	}
}

#endif // _NATIVE_UI_COMPONENT_H_

