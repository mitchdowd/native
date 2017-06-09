// Module Dependencies
#include "../include/app.h"
#include "../include/eventqueue.h"

namespace native
{
	namespace ui
	{
		handle_t App::_handle = nullptr;
		volatile App* App::_instance = nullptr;

		App::App()
		{
			if (Atomic::compareExchange((volatile void*&) _instance, (void*) this, (void*) nullptr) != nullptr)
				throw AppInitializationException("App already exists");
		}

		App::~App()
		{
			_instance = nullptr;
		}

        float App::getDisplayScale()
        {
            static float scale;

            if (scale == 0.0f)
            {
#ifdef NATIVE_PLATFORM_ANDROID
                scale = 2.75f;  // TODO: Use getResources().getDisplayMetrics().density
#elif defined(NATIVE_PLATFORM_WIN32)
                scale = 1.00f;  // TODO: Use GetDeviceCaps()
#else
                scale = 1.00f;
#endif
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
	}
}

