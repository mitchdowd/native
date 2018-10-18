// Framework Dependencies
#include <native.h>

// Namespace Usage
using namespace native;
using namespace native::ui;

class CustomButton : public TextComponent
{
public:
	CustomButton()
	{
		_background = Color(0xFD, 0xFD, 0xFD);
		_isHover = false;
	}

	virtual Size getPreferredSize() const override
	{
		return getFont().measureText(getText()).inflate(20, 10);
	}

protected:
	virtual void onPaint(Canvas& canvas) override
	{
		Rectangle area = getContentArea();
		String text = getText();
		Font font = getFont();

		canvas.drawRectangle(area, Color(0x99, 0x99, 0x99), _background);
		canvas.drawText(text, font, area, Align::Center);
	}

	virtual void onInput(const InputEvent& event) override
	{
		TextComponent::onInput(event);

		if (event.action == InputEvent::Motion && !_isHover)
		{
			_isHover = true;
			_background = Color(0x99, 0x99, 0x99);
			repaint();
		}
	}

private:
	Brush _background;
	bool _isHover;
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
