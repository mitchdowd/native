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

			/**
				Navigates the browser to the specified URL.
				\param url The URL to navigate to.
			 */
			void navigate(const String& url);

		protected:
			/** Updates the size of the WebView. */
			virtual void onSize(const Size& size) override;
		};
	}
}

#endif // _NATIVE_UI_WEB_VIEW_H_

