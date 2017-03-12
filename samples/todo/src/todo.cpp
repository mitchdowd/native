// Framework Dependencies
#include <native.h>

using namespace native::ui;

/**
	The main application creation class.
 */
class MyApp : public native::ui::App
{
public:
    MyApp()
    {
        setTitle("To-Do List");

		setBackground(Color(0x49, 0x4B, 0x54));

		addChild(_child);

		_child.setMargin(20);
		_child.setBackground(Color(0x42, 0x44, 0x4C));

		_child.addChild(_inner);

		_inner.setMargin(20);
		_inner.setBackground(Color(0x49, 0x4B, 0x54));

		_btn.setText("Click me!");
		_inner.addChild(_btn);
		_btn.setMargin(20);

		_btn.onClicked.connect([&]() { 
			Dialogs::messageBox(this, "Button clicked.", "Alert"); 
		});
    }

private:
	// Instance Variables
	LayoutComponent _child, _inner;
	Button _btn;
};

// Entry Point
NATIVE_UI_APP(MyApp)
