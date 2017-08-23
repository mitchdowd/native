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
            // TODO

            // We want to receive notifications when the Action is updated.
            action.addListener(this);
            _children.insert(index, &action);
            onHierarchyUpdate();
        }

        void Menu::insertSeparator(size_t index)
        {
            // TODO

            // Hierarchy updates.
            _children.insert(index, MenuItem());
            onHierarchyUpdate();
        }

        void Menu::insert(size_t index, Menu& menu)
        {
            // TODO

            // Hierarchy updates.
            menu._parent = this;
            _children.insert(index, &menu);
            menu.onHierarchyUpdate();
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
