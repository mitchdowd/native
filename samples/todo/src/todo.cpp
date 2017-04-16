// Framework Dependencies
#include <native.h>

using namespace native;
using namespace native::ui;

class Label : public TextComponent
{
public:
	Label(const String& text) : TextComponent()
	{
		setText(text);
		setBackground(Color(0xFF, 0, 0));
	}

protected:
	virtual void onPaint(Canvas& canvas) override
	{
		TextComponent::onPaint(canvas);
		canvas.drawText(getText(), getFont());
	}
};

/**
	The main application creation class.
 */
class MyApp : public native::ui::App
{
public:
    MyApp() : _label1(L"Label 1"), _label2(L"Label 2")
    {
        setTitle("To-Do List");

		addChild(_layout);

		_label1.setMargin(20);

		_label1.setAlignment(Align::Bottom | Align::Right);
		_label2.setAlignment(Align::Center);

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
