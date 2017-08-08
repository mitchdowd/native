// Module Dependencies
#include "../include/app.h"
#include "../include/componentadapter.h"
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
#ifdef NATIVE_PLATFORM_WIN32
			ComponentAdapter* adapter = (ComponentAdapter*) getAdapter();
			::DrawMenuBar(HWND(adapter->getHandle()));
#endif

			setVisible(true);

			while (isVisible() && EventQueue::handleEvent())
				;	// No-op.

			return EventQueue::getExitCode();
		}

		Menu& App::getMenu()
		{
#ifdef NATIVE_PLATFORM_WIN32
			if (_menu == nullptr)
			{
				ComponentAdapter* adapter = (ComponentAdapter*) getAdapter();

				HMENU menu = ::CreateMenu();
				::SetMenu(HWND(adapter->getHandle()), menu);
				
				_menu = new Menu(handle_t(menu));
			}

			return *_menu;
#else
            if (_menu == nullptr)
            {
                // TODO
                _menu = new Menu();
            }

            return *_menu;
#endif
		}
	}
}

