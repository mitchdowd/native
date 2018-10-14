// Framework Dependencies
#include <native.h>

// Namespace Usage
using namespace native;
using namespace native::ui;

class CustomButton : public TextComponent
{
public:

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

		auto background = LinearGradientBrush(
			area.getTopLeft(), area.getBottomLeft(),
			Color(0xFD, 0xFD, 0xFD), Color(0xE4, 0xE4, 0xE4)
		);

		canvas.drawRectangle(area, Color(0x99, 0x99, 0x99), background);
		canvas.drawText(text, font, area, Align::Center);
	}
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
