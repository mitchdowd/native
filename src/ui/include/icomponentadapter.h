#ifndef _NATIVE_UI_ICOMPONENT_ADAPTER_H_
#define _NATIVE_UI_ICOMPONENT_ADAPTER_H_ 1

// External Dependencies
#include "../../core/include/string.h"

namespace native
{
	namespace ui
	{
		class IComponentAdapter
		{
		public:
			/** Virtual destructor. */
			virtual ~IComponentAdapter() {}

			/**
				Sets the component's text, for those that support text.
				\param text The text to set.
			 */
			virtual void setText(const String& text) = 0;
		};
	}
}

#endif // _NATIVE_UI_ICOMPONENT_ADAPTER_H_
