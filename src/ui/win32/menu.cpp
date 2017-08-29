// System Dependencies
#include <windows.h>

// Module Dependencies
#include "../include/component.h"
#include "../include/menu.h"
#include "../include/menuadapter.h"

namespace native
{
	namespace ui
	{
		static volatile int32_t _nextId = 1000000;

		Menu::Menu() : _adapter(new MenuAdapter()), _id(Atomic::increment(_nextId)), _parent(nullptr)
		{
		}

		Menu::Menu(IMenuAdapter* adapter) : _adapter(adapter), _id(Atomic::increment(_nextId))
		{

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

			delete _adapter;
		}

		void Menu::insert(size_t index, Action& action)
		{
			if (_adapter)
				_adapter->insert(index, action);

			// We want to receive notifications when the Action is updated.
			action.addListener(this);
			_children.insert(index, &action);
			onHierarchyUpdate();
		}

		void Menu::insertSeparator(size_t index)
		{
			if (_adapter)
				_adapter->insertSeparator(index);

			// Hierarchy updates.
			_children.insert(index, MenuItem());
			onHierarchyUpdate();
		}

		void Menu::insert(size_t index, Menu& menu)
		{
			if (_adapter && menu._adapter)
				_adapter->insert(index, menu);

			// Remove the menu from its previous parent.
			if (menu._parent)
			{
				Menu* oldParent = menu.getParent();

				if (oldParent && oldParent->getAdapter())
					oldParent->getAdapter()->remove(menu);

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
				info.hSubMenu   = HMENU(_adapter->getHandle());
				info.dwTypeData = LPWSTR(_text.toArray());

				if (::SetMenuItemInfo(HMENU(_parent->getAdapter()->getHandle()), UINT(_id), FALSE, &info) == 0)
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

			if (::SetMenuItemInfo(HMENU(_adapter->getHandle()), id, FALSE, &info) == 0)
				throw UserInterfaceException("SetMenuItemInfo() failed");

			onHierarchyUpdate();
		}

		void Menu::onActionDestroyed(Action* action)
		{
			if (_adapter && action)
				_adapter->remove(*action);

			_children.remove(action);
		}

		void Menu::onHierarchyUpdate()
		{
			if (_parent)
				_parent->onHierarchyUpdate();
		}
	}
}
