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
		if (event.action == InputEvent::Enter || event.action == InputEvent::Click)
		{
			_background = Color(0xC9, 0xC9, 0xC9);
			repaint();
		}
		else if (event.action == InputEvent::Leave)
		{
			_background = Color(0xFD, 0xFD, 0xFD);
			repaint();
		}
		else if (event.action == InputEvent::Press)
		{
			_background = Color(0xAD, 0xAD, 0xAD);
			repaint();
		}
	}

	virtual void onClick(const InputEvent& event) override
	{
		onInput(event);
	}

private:
	Brush _background;
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
