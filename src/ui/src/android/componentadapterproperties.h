#ifndef _NATIVE_UI_COMPONENT_ADAPTER_PROPERTIES_H_
#define _NATIVE_UI_COMPONENT_ADAPTER_PROPERTIES_H_ 1

namespace native
{
	namespace ui
	{
		// Forward Declarations
		class Component;

		/**
			Any properties required to create different types of Android
			Views.
		 */
		struct ComponentAdapterProperties
		{
			Component*  component;

			const char* className;
		};
	}
}

#endif // _NATIVE_UI_COMPONENT_ADAPTER_PROPERTIES_H_

