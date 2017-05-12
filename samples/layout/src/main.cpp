// Framework Dependencies
#include <native.h>

// Namespace Usage
using namespace native;
using namespace native::ui;

class Marker : public Component
{
public:
	Marker()
	{
		setBorder(Color(0x99, 0, 0, 0));
		setMargin(1);
	}

	virtual Size getPreferredSize() const override 
	{
		return Size(80, 30);
	}
};

class NotepadApp : public App
{
public:
	NotepadApp()
	{
		// Set up the main window.
		setTitle("Layout Sample");

		addChild(_vertical);

		_vertical.addChild(_top);
		_vertical.addChild(_bottom);

		_top.addChild(_child1);
		_top.addChild(_child2);
		_top.addChild(_child3);

		_bottom.addChild(_child4);

		_child1.setAlignment(Align::HFill | Align::Top);
		_child2.setAlignment(Align::HFill | Align::VCenter);
		_child3.setAlignment(Align::HFill | Align::Bottom);
		_child4.setAlignment(Align::Center);

		_vertical.setOrientation(Vertical);
	}

private:
	LinearLayout _vertical, _top, _bottom;
	Marker _child1, _child2, _child3, _child4;
};

// Entry Point
NATIVE_UI_APP(NotepadApp)
