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

		_input.setMargins(1, 0, 0, 0);
		_input.setFont(Font("Consolas", 14));
		_input.setBorder(Pen());
		_input.setAlignment(Align::Fill);

		addChild(_input);
		initMenu();
	}

private:
	// Helper Functions
	void initMenu()
	{
		_exit.setText("Exit");
		_exit.connect(&EventQueue::quit);

		_file.setText("File");
		_file.add(_exit);

		getMenu().add(_file);
	}

	TextArea _input;
	Menu _file;
	Action _exit;
};

// Entry Point
NATIVE_UI_APP(NotepadApp)
