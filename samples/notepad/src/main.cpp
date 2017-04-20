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

		_input.setAlignment(Align::Fill);

		addChild(_input);
	}

private:
	InputComponent _input;
};

// Entry Point
NATIVE_UI_APP(NotepadApp)
