#ifndef _NATIVE_UI_COMPONENT_H_
#define _NATIVE_UI_COMPONENT_H_ 1

// External Dependencies
#include "../../core/include/exception.h"

// Module Dependencies
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
				Gets this Component's adapter, if it has one.
				\return The adapter this Component was created with.
			 */
			IComponentAdapter* getAdapter() const noexcept { return _adapter; }

		protected:
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

