// Framework Dependencies
#include <native.h>

// Namespace Usage
using namespace native;
using namespace native::ui;

class WebViewApp : public App
{
public:
	WebViewApp()
	{
		setTitle("WebView Sample");

		_webView.navigate("github.com");

		addChild(_webView);
	}

private:
	WebView _webView;
};

// Entry Point
NATIVE_UI_APP(WebViewApp)
