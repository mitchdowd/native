// External Dependencies
#include "../../core/include/exception.h"
#include "../../../lib/jnipp/jnipp.h"

// Module Dependencies
#include "../include/component.h"
#include "../include/menu.h"
#include "../include/menuadapter.h"

namespace native
{
    namespace ui
    {
        MenuAdapter::MenuAdapter()
        {
            throw NotImplementedException();
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
            throw NotImplementedException();
        }

        void MenuAdapter::insertSeparator(size_t index)
        {
            throw NotImplementedException();
        }

        void MenuAdapter::insert(size_t index, Menu& menu)
        {
            throw NotImplementedException();
        }

        void MenuAdapter::remove(Menu& menu)
        {
            throw NotImplementedException();
        }

        void MenuAdapter::remove(Action& action)
        {
            throw NotImplementedException();
        }

        void MenuAdapter::update(Menu& menu)
        {
            throw NotImplementedException();
        }

        void MenuAdapter::update(Action& action)
        {
            throw NotImplementedException();
        }
    }
}

