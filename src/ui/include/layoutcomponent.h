#ifndef _NATIVE_UI_LAYOUT_COMPONENT_H_
#define _NATIVE_UI_LAYOUT_COMPONENT_H_ 1

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
		protected:
			LayoutComponent(IComponentAdapter* adapter) : Component(adapter) {}
		};
	}
}

#endif // _NATIVE_UI_LAYOUT_COMPONENT_H_

