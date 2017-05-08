// External Dependencies
#include "../../../lib/jnipp/jnipp.h"

// Module Dependencies
#include "componentadapterproperties.h"
#include "../include/componentadapter.h"
#include "../include/webview.h"

namespace native
{
	namespace ui
	{
		WebView::WebView() : Component(new WebViewAdapter(this))
		{
            setAlignment(Align::Fill);
		}

		void WebView::navigate(const String& url)
		{
            WebViewAdapter* adapter = (WebViewAdapter*) getAdapter();

			adapter->navigate(url);
		}

        void WebView::goBack()
        {
            WebViewAdapter* adapter = (WebViewAdapter*) getAdapter();

			adapter->goBack();
        }

        void WebView::goForward()
        {
            WebViewAdapter* adapter = (WebViewAdapter*) getAdapter();

			adapter->goForward();
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

		void WebViewAdapter::navigate(const String& url)
		{
			((jni::Object*) getHandle())->call<void>("loadUrl", url.toArray());
		}

		void WebViewAdapter::goBack()
		{
			((jni::Object*) getHandle())->call<void>("goBack");
		}

		void WebViewAdapter::goForward()
		{
			((jni::Object*) getHandle())->call<void>("goForward");
		}
	}
}

