// External Dependencies
#include "../../../lib/jnipp/jnipp.h"

// Module Dependencies
#include "../include/component.h"
#include "../include/menu.h"

namespace native
{
    namespace ui
    {
        static volatile int32_t _nextId = 1000000;

        Menu::Menu() : _handle(nullptr), _id(Atomic::increment(_nextId)), _parent(nullptr)
        {
            // TODO
        }

        Menu::Menu(handle_t handle) : _handle(handle), _id(Atomic::increment(_nextId))
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

            if (_handle)
            {
                delete (jni::Object*) _handle;
                _handle = nullptr;
            }
        }

        void Menu::insert(size_t index, Action& action)
        {
            if (_handle)
            {
                // TODO: Menu.add()
            }

            // We want to receive notifications when the Action is updated.
            action.addListener(this);
            _children.insert(index, &action);
        }

        void Menu::insertSeparator(size_t index)
        {
            // Android doesn't have separators, but we'll still track it.
            _children.insert(index, MenuItem());
        }

        void Menu::insert(size_t index, Menu& menu)
        {
            if (_handle)
            {
                // TODO: Menu.addSubmenu()
            }

            // Hierarchy updates.
            menu._parent = this;
            _children.insert(index, &menu);
        }

        void Menu::setText(const String& text)
        {
            _text = text;
        }

        void Menu::onActionUpdated(Action* action)
        {
            // TODO?
        }

        void Menu::onActionDestroyed(Action* action)
        {
            // TODO

            _children.remove(action);
        }

        void Menu::onHierarchyUpdate()
        {
            if (_parent)
                _parent->onHierarchyUpdate();
        }
    }
}
