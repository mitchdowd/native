// External Dependencies
#include "../../../lib/jnipp/jnipp.h"

// Module Dependencies
#include "../include/component.h"
#include "../include/menu.h"

namespace native
{
    namespace ui
    {
        Menu::Menu() : _id(0)
        {
            // TODO
        }

        Menu::Menu(handle_t handle) : _handle(handle), _id(0)
        {
        }

        Menu::~Menu()
        {
            if (_handle)
            {
                // TODO
            }
        }

        void Menu::insert(size_t index, Action& action)
        {
            // TODO

            // We want to receive notifications when the Action is updated.
            action.addListener(this);
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
            // TODO
        }

        void Menu::onActionDestroyed(Action* action)
        {
            // TODO
        }
    }
}
