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
    }
};

// Entry Point
NATIVE_UI_APP(App)
