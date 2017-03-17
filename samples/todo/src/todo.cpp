// Framework Dependencies
#include <native.h>

using namespace native::ui;

class Label : public Component
{
public:
	Label() : Component()
	{
		setAlignment(Align::Fill);
	}

protected:
	virtual void onPaint(Canvas& canvas) override
	{
		canvas.drawText("The quick brown fox jumps over the lazy dog.", Font("Sans serif", 16));
	}
};

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
		_inner.addChild(_label);
		_btn.setMargin(20);

		_btn.setAlignment(Align::Center);

		_btn.onClicked.connect([&]() { 
			Dialogs::messageBox(this, "Button clicked.", "Alert"); 
		});

		_label.setBackground(Color(255, 0, 0));
    }

private:
	// Instance Variables
	LayoutComponent _child, _inner;
	Button _btn;
	Label _label;
};

// Entry Point
NATIVE_UI_APP(MyApp)
