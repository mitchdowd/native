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

		setBackground(native::ui::Color(0xFF, 0, 0));
    }
};

// Entry Point
NATIVE_UI_APP(App)
