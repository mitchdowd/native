#ifndef _NATIVE_UI_WEB_VIEW_H_
#define _NATIVE_UI_WEB_VIEW_H_ 1

// Module Dependencies
#include "component.h"

namespace native
{
	namespace ui
	{
		/**
			A WebView is a Component which displays rendered HTML within its
			content area.
		 */
		class WebView : public Component
		{
		public:
			/** Default constructor. */
			WebView();
		};
	}
}

#endif // _NATIVE_UI_WEB_VIEW_H_

