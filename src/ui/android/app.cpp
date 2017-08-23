// External Dependencies
#include "../../../lib/jnipp/jnipp.h"

// Module Dependencies
#include "../include/app.h"
#include "../include/eventqueue.h"

namespace native
{
	namespace ui
	{
		handle_t App::_handle = nullptr;
		volatile App* App::_instance = nullptr;

		App::App() : _menu(nullptr)
		{
			if (Atomic::compareExchange((volatile void*&) _instance, (void*) this, (void*) nullptr) != nullptr)
				throw AppInitializationException("App already exists");
		}

		App::~App()
		{
			delete _menu;

			_instance = nullptr;
		}

        float App::getDisplayScale()
        {
            static float scale;

            if (scale == 0.0f)
            {
                jni::Object* activity = (jni::Object*) _handle;

                scale = activity->call<float>("getDisplayScale");
            }

            return scale;
        }

		int App::run()
		{
			setVisible(true);

			while (isVisible() && EventQueue::handleEvent())
				;	// No-op.

			return EventQueue::getExitCode();
		}

		Menu& App::getMenu()
		{
            if (_menu == nullptr)
            {
                // TODO
                _menu = new Menu();
            }

            return *_menu;
		}
	}
}

