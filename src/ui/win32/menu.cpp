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

		Menu::Menu() : _handle(::CreatePopupMenu()), _id(Atomic::increment(_nextId)), _parent(nullptr)
		{
			if (!_handle)
				throw InsufficientResourcesException();
		}

		Menu::Menu(handle_t handle) : _handle(handle), _id(Atomic::increment(_nextId))
		{
			if (!::IsMenu(HMENU(handle)))
				throw InvalidArgumentException();
		}

		Menu::~Menu()
		{
			// Remove from parent Menus.
			if (_parent)
				_parent->_children.remove(this);

			// Remove child Menus from this.
			for (auto child : _children)
				if (child.type == MenuItemType::Menu)
					child.menu->_parent = nullptr;

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
			info.fMask      = MIIM_STRING | MIIM_STATE | MIIM_ID;
			info.fState     = MFS_ENABLED;
			info.wID        = (UINT) uptrint_t(action.getHandle());
			info.dwTypeData = LPWSTR(action.getText().toArray());

			// Insert the menu item into the menu.
			if (::InsertMenuItem(HMENU(_handle), UINT(index), TRUE, &info) == 0)
				throw UserInterfaceException("InsertMenuItem() failed");

			// We want to receive notifications when the Action is updated.
			action.addListener(this);
			_children.insert(index, &action);
			onHierarchyUpdate();
		}

		void Menu::insertSeparator(size_t index)
		{
			MENUITEMINFO info = { 0 };

			// Fill out the regular menu item information.
			info.cbSize = sizeof(info);
			info.fMask  = MIIM_TYPE;
			info.fType  = MFT_SEPARATOR;

			// Insert the separator into the menu.
			if (::InsertMenuItem(HMENU(_handle), UINT(index), TRUE, &info) == 0)
				throw UserInterfaceException("InsertMenuItem() failed");

			// Hierarchy updates.
			_children.insert(index, MenuItem());
			onHierarchyUpdate();
		}

		void Menu::insert(size_t index, Menu& menu)
		{
			MENUITEMINFO info = { 0 };

			// Fill out the regular menu item information.
			info.cbSize     = sizeof(info);
			info.fMask      = MIIM_STRING | MIIM_STATE | MIIM_SUBMENU | MIIM_ID;
			info.fState     = MFS_ENABLED;
			info.wID        = UINT(menu._id);
			info.hSubMenu   = HMENU(menu._handle);
			info.dwTypeData = LPWSTR(menu._text.toArray());

			// Insert the menu item into the Menu.
			if (::InsertMenuItem(HMENU(_handle), UINT(index), TRUE, &info) == 0)
				throw UserInterfaceException("InsertMenuItem() failed");

			// Remove the menu from its previous parent.
			if (menu._parent)
			{
				::RemoveMenu(HMENU(menu._parent->_handle), UINT(menu._id), MF_BYCOMMAND);
				menu._parent->_children.remove(&menu);
			}

			// Hierarchy updates.
			menu._parent = this;
			_children.insert(index, &menu);
			menu.onHierarchyUpdate();
		}

		void Menu::setText(const String& text)
		{
			_text = text;

			// Update parent Menus.
			if (_parent)
			{
				MENUITEMINFO info = { 0 };

				// Set the new menu item information.
				info.cbSize     = sizeof(info);
				info.fMask      = MIIM_STRING | MIIM_STATE | MIIM_SUBMENU | MIIM_ID | MIIM_FTYPE;
				info.fState     = MFS_ENABLED;
				info.fType      = MFT_STRING;
				info.wID        = UINT(_id);
				info.hSubMenu   = HMENU(_handle);
				info.dwTypeData = LPWSTR(_text.toArray());

				if (::SetMenuItemInfo(HMENU(_parent->getHandle()), UINT(_id), FALSE, &info) == 0)
					throw UserInterfaceException("SetMenuItemInfo() failed");

				_parent->onHierarchyUpdate();
			}
		}

		void Menu::onActionUpdated(Action* action)
		{
			MENUITEMINFO info = { 0 };

			UINT id = (UINT) uptrint_t(action->getHandle());

			// Set the new menu item information.
			info.cbSize     = sizeof(info);
			info.fMask      = MIIM_STRING | MIIM_STATE | MIIM_FTYPE;
			info.fState     = MFS_ENABLED;
			info.fType      = MFT_STRING;
			info.dwTypeData = LPWSTR(action->getText().toArray());

			if (::SetMenuItemInfo(HMENU(_handle), id, FALSE, &info) == 0)
				throw UserInterfaceException("SetMenuItemInfo() failed");

			onHierarchyUpdate();
		}

		void Menu::onActionDestroyed(Action* action)
		{
			::RemoveMenu(HMENU(_handle), (UINT) uptrint_t(action->getHandle()), MF_BYCOMMAND);
			_children.remove(action);
		}

		void Menu::onHierarchyUpdate()
		{
			if (_parent)
				_parent->onHierarchyUpdate();
		}
	}
}
