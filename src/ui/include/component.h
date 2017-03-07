#ifndef _NATIVE_UI_COMPONENT_H_
#define _NATIVE_UI_COMPONENT_H_ 1

// External Dependencies
#include "../../core/include/exception.h"
#include "../../core/include/flags.h"

// Module Dependencies
#include "brush.h"
#include "canvas.h"
#include "icomponentadapter.h"

namespace native
{
	namespace ui
	{
		// Forward Declarations
		class ComponentAdapter;
		class LayoutComponent;

		/** Maskable alignments. */
		ENUM_FLAGS(Alignment)
		{
			None = 0,

			// Horizontal Alignments
			Left    = 1,
			Right   = 2,
			HCenter = 4,
			HFill   = 8,

			// Vertical Alignments
			Top     = 16,
			Bottom  = 32,
			VCenter = 64,
			VFill   = 128,

			// Combinations
			Fill       = HFill   | VFill,
			Center     = HCenter | VCenter,
			Horizontal = Left | Right  | HCenter | HFill,
			Vertical   = Top  | Bottom | VCenter | VFill
		};

		/** Shorthand for `Alignment`. */
		typedef Alignment Align;

		/**
			Margins to place around a Component.
		 */
		struct Margins {
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
				Gets the current area, relative to the parent Component.
				\return The current Area.
			 */
			Rectangle getArea() const { return _area; }

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
				Gets this Component's adapter, if it has one.
				\return The adapter this Component was created with.
			 */
			IComponentAdapter* getAdapter() const noexcept { return _adapter; }

		protected:
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

