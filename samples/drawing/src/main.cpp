// Framework Dependencies
#include <native.h>

// Namespace Usage
using namespace native;
using namespace native::ui;

class CustomButton : public Component
{
public:
	CustomButton()
	{
		_background = Color(0xFD, 0xFD, 0xFD);
		_isHover = false;
	}

	virtual Size getPreferredSize() const override
	{
		return Font::getDefault().measureText(getText()).inflate(20, 10);
	}

	void setText(const String& text) { _text = text; }
	String getText() const { return _text; }

protected:
	virtual void onPaint(Canvas& canvas) override
	{
		Rectangle area = getContentArea();
		String text = getText();
		Font font = Font::getDefault();

		canvas.drawRectangle(area, Color(0x99, 0x99, 0x99), _background);
		canvas.drawText(text, font, area, Align::Center);
	}

	virtual void onInput(const InputEvent& event) override
	{
		if (event.action == InputEvent::Motion && !_isHover)
		{
			_isHover = true;
			_background = Color(0xC9, 0xC9, 0xC9);
			repaint();
		}
	}

private:
	Brush _background;
	bool _isHover;
	String _text;
};

class DrawingApp : public App
{
public:
	DrawingApp()
	{
		// Set up the main window.
		setTitle("Drawing Sample");
		setSize(300, 300);

		
		_btn.setAlignment(Align::Center);
		_btn.setText("Hello World!");

		addChild(_btn);
	}

private:
	// Components
	CustomButton _btn;
};

// Entry Point
NATIVE_UI_APP(DrawingApp)
