// System Dependencies
#include <windows.h>

// Module Dependencies
#include "../include/component.h"
#include "../include/menu.h"

namespace native
{
	namespace ui
	{
		static volatile int32_t _nextId = 1000000;

		Menu::Menu() : _handle(::CreatePopupMenu()), _id(Atomic::increment(_nextId))
		{
		}

		Menu::~Menu()
		{
			if (_handle)
			{
				::DestroyMenu(HMENU(_handle));
				_handle = NULL;
			}
		}

		void Menu::insert(size_t index, Action& action)
		{
			MENUITEMINFO info = { 0 };

			// Fill out the regular menu item information.
			info.cbSize     = sizeof(info);
			info.fMask      = MIIM_STRING | MIIM_STATE | MIIM_ID | MIIM_BITMAP;
			info.fState     = MFS_ENABLED;
			info.wID        = uptrint_t(action.getHandle());
			info.dwTypeData = (LPWSTR) action.getText().toArray();

			// Insert the menu item into the menu.
			if (::InsertMenuItem(HMENU(_handle), index, TRUE, &info) == 0)
				throw UserInterfaceException("InsertMenuItem() failed");

			// We want to receive notifications when the Action is updated.
			action.addListener(this);
		}

		void Menu::insertSeparator(size_t index)
		{
			MENUITEMINFO info = { 0 };

			// Fill out the regular menu item information.
			info.cbSize = sizeof(info);
			info.fMask  = MIIM_TYPE;
			info.fType  = MFT_SEPARATOR;

			// Insert the separator into the menu.
			if (::InsertMenuItem(HMENU(_handle), index, TRUE, &info) == 0)
				throw UserInterfaceException("InsertMenuItem() failed");
		}

		void Menu::insert(size_t index, Menu& menu)
		{
			MENUITEMINFO info = { 0 };

			// Fill out the regular menu item information.
			info.cbSize     = sizeof(info);
			info.fMask      = MIIM_STRING | MIIM_STATE | MIIM_SUBMENU | MIIM_ID;
			info.fState     = MFS_ENABLED;
			info.wID        = menu._id;
			info.hSubMenu   = HMENU(menu._handle);
			info.dwTypeData = LPWSTR(menu._text.toArray());

			// Insert the menu item into the Menu.
			if (::InsertMenuItem(HMENU(_handle), index, TRUE, &info) == 0)
				throw UserInterfaceException("InsertMenuItem() failed");
		}

		void Menu::setText(const String& text)
		{
			_text = text;

			// TODO: Update text in parent menus.
		}

		void Menu::onActionUpdated(Action* action)
		{
			MENUITEMINFO info = { 0 };

			// Set the new menu item information.
			info.cbSize     = sizeof(info);
			info.fMask      = MIIM_STRING | MIIM_STATE | MIIM_BITMAP;
			info.fState     = MFS_ENABLED;
			info.dwTypeData = (LPTSTR) action->getText().toArray();

			if (::SetMenuItemInfo(HMENU(_handle), uptrint_t(action->getHandle()), FALSE, &info) == 0)
				throw UserInterfaceException("SetMenuItemInfo() failed");
			
		}

		void Menu::onActionDestroyed(Action* action)
		{
			::RemoveMenu(HMENU(_handle), uptrint_t(action->getHandle()), MF_BYCOMMAND);
		}
	}
}
