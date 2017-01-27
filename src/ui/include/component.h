#ifndef _NATIVE_UI_COMPONENT_H_
#define _NATIVE_UI_COMPONENT_H_ 1

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

			// Instance Variables
			IComponentAdapter* _adapter;
			LayoutComponent*   _parent;
		};
	}
}

#endif // _NATIVE_UI_COMPONENT_H_

