#ifndef _NATIVE_UI_WEB_VIEW_H_
#define _NATIVE_UI_WEB_VIEW_H_ 1

// Module Dependencies
#include "component.h"

namespace native
{
	namespace ui
	{
		// Forward Declarations
		struct WebViewDetail;

		/**
			A WebView is a Component which displays rendered HTML within its
			content area.
		 */
		class WebView : public Component
		{
		public:
			/** Default constructor. */
			WebView();

			/* Destructor. */
			~WebView();

		protected:
			/** Updates the size of the WebView. */
			virtual void onSize(const Size& size) override;

		private:
			// Instance Variables
			WebViewDetail* _detail;
		};
	}
}

#endif // _NATIVE_UI_WEB_VIEW_H_

