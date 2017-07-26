// Framework Dependencies
#include <native.h>

// Namespace Usage
using namespace native;
using namespace native::ui;

class NotepadApp : public App
{
public:
	NotepadApp()
	{
		setTitle("Notepad Sample");
		setBackground(Color(0xF0, 0xF0, 0xF0));

		_input.setMargins(2, 0, 0, 0);
		_input.setFont(Font("Consolas", 14));
		_input.setBorder(Pen());
		_input.setAlignment(Align::Fill);

		addChild(_input);
	}

private:
	TextArea _input;
};

// Entry Point
NATIVE_UI_APP(NotepadApp)
