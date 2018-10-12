// Framework Dependencies
#include <native.h>

// Namespace Usage
using namespace native;
using namespace native::ui;

class DrawingApp : public App
{
public:
	DrawingApp()
	{
		// Set up the main window.
		setTitle("Drawing Sample");
		setSize(300, 300);
	}

protected:
	virtual void onPaint(Canvas& canvas) override
	{
		// This paints the background as usual.
		App::onPaint(canvas);

		// Information about the text to draw.
		Font font = Font::getDefault();
		String msg = L"Hello World!";
		Size msgSize = font.measureText(msg);

		// Information on the location to draw.
		Rectangle contentRect = getContentArea();
		Point msgPt = {
			(contentRect.width / 2) - (msgSize.width / 2),
			(contentRect.height / 2) - (msgSize.height / 2)
		};

		canvas.drawText(msg, font, msgPt);
		canvas.drawRectangle(Rectangle(msgPt, msgSize).inflate(20, 10), Color(255, 0, 0));
	}

private:
};

// Entry Point
NATIVE_UI_APP(DrawingApp)
