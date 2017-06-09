// Module Dependencies
#include "../include/app.h"
#include "../include/eventqueue.h"

#ifdef NATIVE_PLATFORM_ANDROID
#include "../../../lib/jnipp/jnipp.h"
#elif defined(NATIVE_PLATFORM_WIN32)
# include <windows.h>
#endif // NATIVE_PLATFORM_*

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
                jni::Object* activity = (jni::Object*) _handle;

                scale = activity->call<float>("getDisplayScale");
#elif defined(NATIVE_PLATFORM_WIN32)
				HDC hdc = ::GetDC(NULL);
				scale = float(::GetDeviceCaps(hdc, LOGPIXELSX)) / 96.0f;
				::ReleaseDC(NULL, hdc);
#else
                scale = 1.00f;
#endif // NATIVE_PLATFORM_*
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

