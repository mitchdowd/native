// System Dependencies
#include <Windows.h>

// External Dependencies
#include "../../core/include/exception.h"

// Module Dependencies
#include "../include/component.h"
#include "../include/menu.h"
#include "../include/menuadapter.h"

namespace native
{
	namespace ui
	{
		MenuAdapter::MenuAdapter() : _handle(::CreatePopupMenu())
		{
			if (!_handle)
				throw InsufficientResourcesException();
		}

		MenuAdapter::MenuAdapter(handle_t handle) : _handle(handle)
		{
		}

		MenuAdapter::~MenuAdapter()
		{
			::DestroyMenu(HMENU(_handle));
		}

		void MenuAdapter::insert(size_t index, Action& action)
		{
			MENUITEMINFO info = { 0 };

			// Fill out the regular menu item information.
			info.cbSize     = sizeof(info);
			info.fMask      = MIIM_STRING | MIIM_STATE | MIIM_ID;
			info.fState     = MFS_ENABLED;
			info.wID        = UINT(action.getId());
			info.dwTypeData = LPWSTR(action.getText().toArray());

			// Insert the menu item into the menu.
			if (::InsertMenuItem(HMENU(_handle), UINT(index), TRUE, &info) == 0)
				throw UserInterfaceException("InsertMenuItem() failed");
		}

		void MenuAdapter::insertSeparator(size_t index)
		{
			MENUITEMINFO info = { 0 };

			// Fill out the regular menu item information.
			info.cbSize = sizeof(info);
			info.fMask  = MIIM_TYPE;
			info.fType  = MFT_SEPARATOR;

			// Insert the separator into the menu.
			if (::InsertMenuItem(HMENU(_handle), UINT(index), TRUE, &info) == 0)
				throw UserInterfaceException("InsertMenuItem() failed");
		}

		void MenuAdapter::insert(size_t index, Menu& menu)
		{
			MENUITEMINFO info = { 0 };

			IMenuAdapter* adapter = menu.getAdapter();

			if (!adapter)
				throw UserInterfaceException("Cannot insert menu without an adapter.");

			// Fill out the regular menu item information.
			info.cbSize     = sizeof(info);
			info.fMask      = MIIM_STRING | MIIM_STATE | MIIM_SUBMENU | MIIM_ID;
			info.fState     = MFS_ENABLED;
			info.wID        = UINT(menu.getId());
			info.hSubMenu   = HMENU(adapter->getHandle());
			info.dwTypeData = LPWSTR(menu.getText().toArray());

			// Insert the menu item into the Menu.
			if (::InsertMenuItem(HMENU(_handle), UINT(index), TRUE, &info) == 0)
				throw UserInterfaceException("InsertMenuItem() failed");
		}

		void MenuAdapter::remove(Menu& menu)
		{
			::RemoveMenu(HMENU(_handle), UINT(menu.getId()), MF_BYCOMMAND);
		}

		void MenuAdapter::remove(Action& action)
		{
			::RemoveMenu(HMENU(_handle), (UINT) uptrint_t(action.getId()), MF_BYCOMMAND);
		}

		void MenuAdapter::update(Menu& menu)
		{
			MENUITEMINFO info = { 0 };

			if (menu.getAdapter())
			{
				// Set the new menu item information.
				info.cbSize     = sizeof(info);
				info.fMask      = MIIM_STRING | MIIM_STATE | MIIM_SUBMENU | MIIM_ID | MIIM_FTYPE;
				info.fState     = MFS_ENABLED;
				info.fType      = MFT_STRING;
				info.wID        = UINT(menu.getId());
				info.hSubMenu   = HMENU(menu.getAdapter()->getHandle());
				info.dwTypeData = LPWSTR(menu.getText().toArray());

				if (::SetMenuItemInfo(HMENU(getHandle()), UINT(menu.getId()), FALSE, &info) == 0)
					throw UserInterfaceException("SetMenuItemInfo() failed");
			}
		}

		void MenuAdapter::update(Action& action)
		{
			MENUITEMINFO info = { 0 };

			// Set the new menu item information.
			info.cbSize     = sizeof(info);
			info.fMask      = MIIM_STRING | MIIM_STATE | MIIM_FTYPE;
			info.fState     = MFS_ENABLED;
			info.fType      = MFT_STRING;
			info.dwTypeData = LPWSTR(action.getText().toArray());

			if (::SetMenuItemInfo(HMENU(getHandle()), UINT(action.getId()), FALSE, &info) == 0)
				throw UserInterfaceException("SetMenuItemInfo() failed");
		}
	}
}

