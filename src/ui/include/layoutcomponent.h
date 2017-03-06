#ifndef _NATIVE_UI_LAYOUT_COMPONENT_H_
#define _NATIVE_UI_LAYOUT_COMPONENT_H_ 1

// External Dependencies
#include "../../core/include/list.h"

// Module Dependencies
#include "component.h"

namespace native
{
	namespace ui
	{
		/**
			A Component whose purpose is to contain other child Components.
		 */
		class LayoutComponent : public Component
		{
		public:
			/** Default constructor. */
			LayoutComponent() : Component() {}

			/**
				Creates a LayoutComponent with the given native adapter.
			 	\param adapter The adapter for this component.
			 */
			LayoutComponent(IComponentAdapter* adapter) : Component(adapter) {}

			/** Destructor. */
			~LayoutComponent();

			/**
				Adds a Component as a child component of this LayoutComponent.
			 	\param child The child to add.
			 */
			void addChild(Component* child) { insertChild(_children.getLength(), child); }
			void addChild(Component& child) { insertChild(_children.getLength(), &child); }

			/**
				Inserts a child Component at the given zero-based index in this
				Component's child list.
				\param index Zero-based index to insert to.
				\param child The child Component to insert.
			 */
			void insertChild(size_t index, Component* child);
			void insertChild(size_t index, Component& child) { insertChild(index, &child); }

			/**
				Gets a List of this Component's direct children.
			 	\return The List of child Components.
			 */
			const List<Component*>& getChildren() const noexcept { return _children; }

		protected:
			/**
				Called when the geometric size of the Component changes. This will
				allocate the entire content area to each child by default.
				\param size The new size.
			 */
			virtual void onSize(const Size& size) override;

			/** For internal use only. */
			virtual void setParentAdapter(IComponentAdapter* parent) override;

			/** For internal use only. */
			void removeChild(Component* child);

		private:
			// Class Friendships
			friend class Component;

			// Instance Variables
			List<Component*> _children;
		};
	}
}

#endif // _NATIVE_UI_LAYOUT_COMPONENT_H_

