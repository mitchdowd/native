#ifndef _NATIVE_UI_COMPONENT_H_
#define _NATIVE_UI_COMPONENT_H_ 1

// External Dependencies
#include "../../core/include/exception.h"

// Module Dependencies
#include "brush.h"
#include "canvas.h"
#include "icomponentadapter.h"
#include "inputevent.h"
#include "pen.h"

namespace native
{
	namespace ui
	{
		// Forward Declarations
		class ComponentAdapter;
		class LayoutComponent;

		/**
			Margins to place around a Component.
		 */
		struct Margins {
			Margins(coord_t top, coord_t right, coord_t bottom, coord_t left)
                : top(top)
                , right(right)
                , bottom(bottom)
                , left(left) {}

			coord_t top;
			coord_t right;
			coord_t bottom;
			coord_t left;
		};

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
				Sets the size of the Component without changing its position.
				\param size The size to set.
			 */
			void setSize(const Size& size) { setSize(size.width, size.height); }
			void setSize(coord_t width, coord_t height);

			/**
				Gets the current area, relative to the parent Component.
				\return The current Area.
			 */
			Rectangle getArea() const noexcept { return _area; }

			/**
				Gets the geometric size of this Component.
				\return The Component's size.
			 */
			Size getSize() const noexcept { return _area.getSize(); }

			/**
				Gets the preferred size of this Component based upon its current
				contents. This should be overridden by inherited types in order
				to properly reflect the desired Component behavior.
				\return The preferred size.
			 */
			virtual Size getPreferredSize() const { return Size(0, 0); }

			/**
				Override to set a minimum size which the Component requires to
				be displayed properly.
				\return The minimum size.
			 */
			virtual Size getMinimumSize() const { return Size(0, 0); }

			/**
				Allocates a given area to the Rectangle. This area includes the
				margins, borders and any alignment values, which may result in
				a smaller subset of the area finally being set.
				\param area The area to allocate.
			 */
			virtual void allocateArea(const Rectangle& area);

			/**
				Gets the usable portion of this Component's area, relative to
				the Component's top-left corner. For many Components this will
				simply be the size of the Component, located at the origin, but
				things such as borders will shrink the usable content area.
				\return The content area.
			 */
			Rectangle getContentArea() const;
			
			/**
				Sets the alignment of this Component within its allocated area.
				Different types of Component have a different default Alignment.
				\param alignment A set of `Alignment` flags to set.
			 */
			void setAlignment(Flags<Alignment> alignment) { _alignment = alignment; }

			/**
				Gets the current Alignment flags for this Component.
				\return The current Alignment.
			 */
			Flags<Alignment> getAlignment() const { return _alignment; }

			/**
				Sets the margins to reserve around the Component when allocating
				area to it.
				\param margins The margins to set.
			 */
			void setMargins(const Margins& margins) { _margins = margins; }
			void setMargins(coord_t top, coord_t right, coord_t bottom, coord_t left) { setMargins({ top, right, bottom, left }); }

			/**
				Sets the same margin on all 4 sides of this Component.
				\param margin The margin to set.
			 */
			void setMargin(coord_t margin) { setMargins({ margin, margin, margin, margin }); }

			/**
				Gets the currently-set margins on this Component.
				\return The current margins.
			 */
			Margins& getMargins() noexcept { return _margins; }
			const Margins& getMargins() const noexcept { return _margins; }

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
				Set the Pen to draw this Component's border.
				\param pen The Pen for drawing the border.
			 */
			void setBorder(const Pen& pen);

			/**
				Gets the Pen currently used to draw this Component's border.
				\return The Pen for drawing the border.
			 */
			Pen getBorder() const { return _border; }

			/**
				Executes the given Function asynchronously by posting it as an
				event on the UI thread's message queue.
				\param func The Function to execute.
			 */
			void invokeAsync(const Function<void>& func);

			/**
				Gets this Component's adapter, if it has one.
				\return The adapter this Component was created with.
			 */
			IComponentAdapter* getAdapter() const noexcept { return _adapter; }

		protected:
			/**
				Called by onInput() when a press and release sequence indicates
				a normal click action. This is like a "tap" on touch devices, or
				a "left click" with a mouse.
				\param event Details about the click which occurred.
			 */
			virtual void onClick(const InputEvent& event) {}

			/**
				Called by onInput() when a press and release sequence indicates
				a "context" click action. This is either a long press on touch
				devices, or a right click with a mouse.
				\param event Contains information on the long click.
			 */
			virtual void onContextClick(const InputEvent& event) {}

			/**
				Occurs when a pointing-type input device performs an action on
				this Component. By default, this will
				\param event Details on the input event.
			 */
            virtual void onInput(const InputEvent& event);

			/**
				This is where the painting of the Component occurs. Override to
				do your own custom painting. By default, this paints the background
				on the entire Component's content area.
				\param canvas The Canvas with which to paint.
			 */
			virtual void onPaint(Canvas& canvas);

			/**
				Called when the geometric size of the Component changes. This is
				where child Components have their positions adjusted to fit into
				the new dimensions.
				\param size The new size.
			 */
			virtual void onSize(const Size& size);

			/** For internal use only. */
			virtual void setParentAdapter(IComponentAdapter* parent);

			/**
				For internal use only in triggering the repaint sequence.
				\param canvas The canvas to paint with.
			 */
			virtual void dispatchPaintEvent(Canvas& canvas);

			/**
				For internal use only in sending input events.
			    \event Native input event information.
			 */
            virtual void dispatchInputEvent(const InputEvent& event);

			/**
				Draws the border for this Component.
				\param canvas The canvas to draw with.
			 */
			void drawBorder(Canvas& canvas);

		private:
			// Class Friendships
			friend class ComponentAdapter;
			friend class LayoutComponent;

			// Private Types
			enum Visibility { Inherit, Show, Hide };

			// Instance Variables
			IComponentAdapter* _adapter;
			LayoutComponent*   _parent;
			Visibility		   _visibility;
			Rectangle		   _area;
			Brush              _background;
			Pen                _border;
			Flags<Alignment>   _alignment;
			Margins            _margins;
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

