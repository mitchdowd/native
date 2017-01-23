#ifndef _NATIVE_UI_COMPONENT_ADAPTER_PROPERTIES_H_
#define _NATIVE_UI_COMPONENT_ADAPTER_PROPERTIES_H_ 1

// External Dependencies
#include "../../../core/include/types.h"

namespace native
{
	namespace ui
	{
		/**
			Properties which can be used to define and create a win32 Window.
		 */
		struct ComponentAdapterProperties
		{
			const wchar_t*	className;	// The window class name, or null for default.
			uint32_t		style;		// The window style.
			uint32_t		exStyle;	// Extended window styles.
		};
	}
}

#endif // _NATIVE_UI_COMPONENT_ADAPTER_PROPERTIES_H_

