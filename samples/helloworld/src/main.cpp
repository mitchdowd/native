// Framework Dependencies
#include <native.h>

// Namespace Usage
using namespace native;
using namespace native::ui;

class HelloWorldApp : public App
{
public:
	HelloWorldApp()
	{
		// Set up the main window.
		setTitle("Hello World Sample");
		setSize(300, 300);

		// Set up the hello button.
		_helloBtn.setText("Say Hello");
		_helloBtn.setAlignment(Align::Center);
		_helloBtn.clicked.connect([]() {
			Alerts::messageBox("Hello World", "Alert");
		});

		addChild(_helloBtn);
	}

private:
	Button _helloBtn;
};

// Entry Point
NATIVE_UI_APP(HelloWorldApp)
