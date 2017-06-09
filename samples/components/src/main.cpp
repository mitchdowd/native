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

		_layout.setMargin(10);

		_button.setText("Button");
		
		_check1.setText("Checkbox 1");
		_check1.setChecked(true);

		_check2.setText("Checkbox 2");
		
		_check3.setText("Checkbox 3");
		_check3.setEnabled(false);
		
		_label.setText("Label");

		_radio1.setText("RadioButton 1");
		_radio1.check();

		_radio2.setText("RadioButton 2");

		_radio3.setText("RadioButton 3");
		_radio3.setEnabled(false);

		_layout.addChild(_button);
		_layout.addChild(_check1);
		_layout.addChild(_check2);
		_layout.addChild(_check3);
		_layout.addChild(_label);
		_layout.addChild(_radio1);
		_layout.addChild(_radio2);
		_layout.addChild(_radio3);

		addChild(_layout);
	}

private:
	Button _button;
	Checkbox _check1, _check2, _check3;
	Label _label;
	RadioButton _radio1, _radio2, _radio3;
	VLayout _layout;
};

// Entry Point
NATIVE_UI_APP(ComponentsApp)
