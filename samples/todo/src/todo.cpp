// Framework Dependencies
#include <native.h>

/**
	The main application creation class.
 */
class App : public native::ui::App
{
public:
    App()
    {
        setTitle("To-Do List");

		setBackground(native::ui::Color(0, 0xFF, 0));

		addChild(_child);

		_child.setMargins({ 20, 20, 20, 20 });
		_child.setBackground(native::ui::Color(0xFF, 0, 0));
    }

private:
	// Instance Variables
	LayoutComponent _child;
};

// Entry Point
NATIVE_UI_APP(App)
