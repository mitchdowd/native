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

		_button1.setText("Button 1");
		_button2.setText("Button 2");
		_button2.setEnabled(false);
		
		// Checkboxes

		_check1.setText("Checkbox 1");
		_check1.setChecked(true);
		_checkLayout.addChild(_check1);

		_check2.setText("Checkbox 2");
		_checkLayout.addChild(_check2);
		
		_check3.setText("Checkbox 3");
		_check3.setEnabled(false);
		_checkLayout.addChild(_check3);

		_checkGroup.setText("CheckBoxes");
		_checkGroup.addChild(_checkLayout);

		_label.setText("Label");

		_radio1.setText("RadioButton 1");
		_radio1.check();

		_radio2.setText("RadioButton 2");

		_radio3.setText("RadioButton 3");
		_radio3.setEnabled(false);

		_input1.setText("InputComponent 1");

		_input2.setText("InputComponent 2");
		_input2.setEnabled(false);

		_progress1.setProgress(50);

		_area1.setText("TextArea 1");

		_layout.addChild(_button1);
		_layout.addChild(_button2);
		_layout.addChild(_checkGroup);
		_layout.addChild(_label);
		_layout.addChild(_radio1);
		_layout.addChild(_radio2);
		_layout.addChild(_radio3);
		_layout.addChild(_input1);
		_layout.addChild(_input2);
		_layout.addChild(_progress1);
		_layout.addChild(_checkGroup);
		_layout.addChild(_area1);
		
		addChild(_layout);
	}

private:
	Button _button1, _button2;
	Checkbox _check1, _check2, _check3;
	Label _label;
	RadioButton _radio1, _radio2, _radio3;
	InputComponent _input1, _input2;
	ProgressBar _progress1;
	TextArea _area1;
	GroupBox _checkGroup;
	VLayout _layout, _checkLayout;
};

// Entry Point
NATIVE_UI_APP(ComponentsApp)
