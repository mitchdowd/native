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

		// Main text area setup.
		_input.setMargins(1, 0, 0, 0);
		_input.setFont(Font("Consolas", 14));
		_input.setBorder(Pen());
		_input.setAlignment(Align::Fill);
		_input.setScrollBars(true, true);

		addChild(_input);
		initMenus();
	}

	bool isContentModified() const
	{
		// TODO
		return true;
	}

private:
	// Helper Functions
	void initMenus()
	{
		// File Menu
		_file.setText("File");

		_new.setText("New");
		_new.connect(this, &NotepadApp::newFile);
		_file.add(_new);

		_open.setText("Open");
		_open.connect(this, &NotepadApp::openFile);
		_file.add(_open);

		_save.setText("Save");
		_save.connect(this, &NotepadApp::saveFile);
		_file.add(_save);

		_saveAs.setText("Save As...");
		_saveAs.connect(this, &NotepadApp::saveFileAs);
		_file.add(_saveAs);

		_file.addSeparator();

		_exit.setText("Exit");
		_exit.connect(&EventQueue::quit);
		_file.add(_exit);

		// Edit Menu
		_edit.setText("Edit");

		// Format Menu
		_format.setText("Format");

		// View Menu
		_view.setText("View");

		// Help Menu
		_help.setText("Help");

        _viewHelp.setText("View Help");
        _help.add(_viewHelp);

        _help.addSeparator();

        _about.setText("About");
        _about.connect([]() { Dialogs::messageBox(L"This is a demo replica of Microsoft's Notepad using the native C++ framework.", L"About Notepad"); });
        _help.add(_about);

		Menu& menuBar = getMenu();
		menuBar.add(_file);
		menuBar.add(_edit);
		menuBar.add(_format);
		menuBar.add(_view);
		menuBar.add(_help);
	}

	void newFile()
	{
        if (isContentModified()) {
            // TODO: Prompt to save.
        }

        _input.setText(L"");
	}

	void openFile()
	{
		// TODO
	}

	void saveFile()
	{
		// TODO
	}

	void saveFileAs()
	{
		// TODO
	}

	TextArea _input;
	Action _new, _open, _save, _saveAs, _exit; 	// File menu actions
	Action _viewHelp, _about;					// Help menu actions
	Menu _file, _edit, _format, _view, _help;
};

// Entry Point
NATIVE_UI_APP(NotepadApp)
