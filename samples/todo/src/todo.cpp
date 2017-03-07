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

		setBackground(native::ui::Color(0x49, 0x4B, 0x54));

		addChild(_child);

		_child.setMargin(20);
		_child.setBackground(native::ui::Color(0x42, 0x44, 0x4C));

		_child.addChild(_inner);

		_inner.setMargin(100);
		_inner.setBackground(native::ui::Color(0x49, 0x4B, 0x54));
    }

private:
	// Instance Variables
	LayoutComponent _child, _inner;
};

// Entry Point
NATIVE_UI_APP(App)
