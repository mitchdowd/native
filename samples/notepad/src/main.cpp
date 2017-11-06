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
		_input.setScrollBars(true, true);

		addChild(_input);
		initMenus();
	}

private:
	// Helper Functions
	void initMenus()
	{
		// File Menu
		_file.setText("File");
        _file.add(_exit);

		_exit.setText("Exit");
		_exit.connect(&EventQueue::quit);

		// Edit Menu
		_edit.setText("Edit");

		// Format Menu
		_format.setText("Format");

		// View Menu
		_view.setText("View");

		// Help Menu
		_help.setText("Help");

		Menu& menuBar = getMenu();
		menuBar.add(_file);
		menuBar.add(_edit);
		menuBar.add(_format);
		menuBar.add(_view);
		menuBar.add(_help);
	}

	TextArea _input;
	Action _exit;
	Menu _file, _edit, _format, _view, _help;
};

// Entry Point
NATIVE_UI_APP(NotepadApp)
