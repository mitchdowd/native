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
		setBackground(Color(255, 255, 255));

		addChild(_layout);

		_label1.setAlignment(Align::Fill);
		_label2.setAlignment(Align::Fill);

		_layout.addChild(_label1);
		_layout.addChild(_label2);

		_layout.setOrientation(Vertical);
    }

private:
	// Instance Variables
	LinearLayout _layout;
	Label _label1, _label2;

};

// Entry Point
NATIVE_UI_APP(MyApp)
