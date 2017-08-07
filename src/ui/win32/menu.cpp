// System Dependencies
#include <windows.h>

// Module Dependencies
#include "../include/menu.h"

namespace native
{
	namespace ui
	{
		Menu::Menu() : _handle(::CreatePopupMenu())
		{
		}

		Menu::~Menu()
		{
			if (_handle)
			{
				::DestroyMenu(HMENU(_handle));
				_handle = nullptr;
			}
		}

		void Menu::insert(size_t index, Action& action)
		{
			// TODO
		}

		void Menu::insertSeparator(size_t index)
		{
			// TODO
		}

		void Menu::insert(size_t index, Menu& menu)
		{
			// TODO
		}

		void Menu::setText(const String& text)
		{
			_text = text;

			// TODO: Update text in parent menus.
		}

		void Menu::onActionUpdated(Action* action)
		{
			// TODO: Update the menu item.
		}

		void Menu::onActionDestroyed(Action* action)
		{
			// TODO: Delete the menu item.
		}
	}
}
