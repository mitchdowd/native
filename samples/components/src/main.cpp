// Framework Dependencies
#include <native.h>

// Namespace Usage
using namespace native;
using namespace native::ui;

class ComponentsApp : public App
{
public:
	ComponentsApp()
	{
		// Set up the main window.
		setTitle("Components Sample");
	}

private:
};

// Entry Point
NATIVE_UI_APP(ComponentsApp)
