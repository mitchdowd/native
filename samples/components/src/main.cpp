// Framework Dependencies
#include <native.h>

// Namespace Usage
using namespace native;
using namespace native::ui;

class ComponentsApp : public App
{
public:
	ComponentsApp()
	{
		setTitle("Components Sample");

		_button.setMargin(5);
		_button.setText("Button");
		
		_checkbox.setText("CheckBox");
		_checkbox.setMargins(50, 5, 5, 5);
		
		_label.setText("Label");
		_label.setMargins(85, 5, 5, 5);
		
		addChild(_button);
		addChild(_checkbox);
		addChild(_label);
	}

private:
	Button _button;
	Checkbox _checkbox;
	Label _label;
};

// Entry Point
NATIVE_UI_APP(ComponentsApp)
