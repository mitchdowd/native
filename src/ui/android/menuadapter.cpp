// External Dependencies
#include "../../core/include/exception.h"
#include "../../../lib/jnipp/jnipp.h"

// Module Dependencies
#include "../include/menu.h"
#include "../include/menuadapter.h"

#define HANDLE_OBJ ((jni::Object*) _handle)

namespace native
{
    namespace ui
    {
        MenuAdapter::MenuAdapter()
        {
            throw InvalidStateException("Android MenuAdapters shouldn't be default constructed!");
        }

        MenuAdapter::MenuAdapter(handle_t handle) : _handle(handle)
        {
        }

        MenuAdapter::~MenuAdapter()
        {
            delete (jni::Object*) _handle;
        }

        void MenuAdapter::insert(size_t index, Action& action)
        {
            HANDLE_OBJ->call<jni::Object>("add(IIILjava/lang/CharSequence;)Landroid/view/MenuItem;",
                0, action.getId(), int(index), action.getText().toArray());

            // TODO: Update ordering of other children to accommodate inserted item.
        }

        void MenuAdapter::insertSeparator(size_t index)
        {
            // "Separators are for wimps, yo!"
            //   -- Android
        }

        void MenuAdapter::insert(size_t index, Menu& menu)
        {
            jni::Object handle = HANDLE_OBJ->call<jni::Object>("addSubMenu(IIILjava/lang/CharSequence;)Landroid/view/SubMenu;",
                0, menu.getId(), int(index), menu.getText().toArray());

            if (menu.getAdapter())
                delete menu.getAdapter();

            IMenuAdapter* adapter = new MenuAdapter(new jni::Object(handle));
            menu.setAdapter(adapter);

            // Re-insert the submenu's children to account for its new adapter.
            for (size_t i = 0; i < menu.getChildren().getLength(); ++i) {
                auto& child = menu.getChildren()[i];

                if (child.type == Menu::MenuItemType::Menu) {
                    adapter->insert(i, *child.menu);
                }
                else if (child.type == Menu::MenuItemType::Action) {
                    adapter->insert(i, *child.action);
                }
            }

            // TODO: Update ordering of other children to accommodate inserted item.
        }

        void MenuAdapter::remove(Menu& menu)
        {
            HANDLE_OBJ->call<void>("removeItem(I)V", menu.getId());
        }

        void MenuAdapter::remove(Action& action)
        {
            HANDLE_OBJ->call<void>("removeItem(I)V", action.getId());
        }

        void MenuAdapter::update(Menu& menu)
        {
            if (menu.getAdapter())
            {
                jni::Object* handle = (jni::Object*) menu.getAdapter()->getHandle();

                handle->call<jni::Object>("setTitle(Ljava/lang/CharSequence;)Landroid/view/MenuItem;", menu.getText().toArray());
            }
        }

        void MenuAdapter::update(Action& action)
        {
            jni::Object menuItem = HANDLE_OBJ->call<jni::Object>("findItem(I)Landroid/view/MenuItem;", action.getId());

            if (!menuItem.isNull())
            {
                menuItem.call<jni::Object>("setTitle(Ljava/lang/CharSequence;)Landroid/view/MenuItem;", action.getText().toArray());
            }
        }
    }
}

