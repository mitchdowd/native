// Module Dependencies
#include "componentadapterproperties.h"
#include "../include/componentadapter.h"
#include "../include/webview.h"

namespace native
{
	namespace ui
	{
		WebView::WebView() : Component()
		{
            throw NotImplementedException();
		}

		void WebView::navigate(const String& url)
		{
			throw NotImplementedException();
		}

        void WebView::goBack()
        {
            throw NotImplementedException();
        }

        void WebView::goForward()
        {
            throw NotImplementedException();
        }

        void WebView::onSize(const Size& size)
        {
            Component::onSize(size);
        }

        /*
            WebViewAdapter Functions
         */

        WebViewAdapter::WebViewAdapter(WebView* view) : ComponentAdapter({ view, "libnative/ui/WebView" }), _browser(nullptr)
        {
        }

        WebViewAdapter::~WebViewAdapter()
        {

        }
	}
}

