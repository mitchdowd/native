// System Dependencies
#include <windows.h>

// Module Dependencies
#include "../include/app.h"
#include "../include/eventqueue.h"
#include "../include/menuadapter.h"

namespace native
{
	namespace ui
	{
		handle_t App::_handle = nullptr;
		volatile App* App::_instance = nullptr;

		class MenuBar : public Menu
		{
		public:
			MenuBar(Component* component) : Menu(new MenuAdapter(::CreateMenu())), _component(component)
			{
				if (component != App::getInstance())
					throw UserInterfaceException("Only the App component can currently have a MenuBar.");

				::SetMenu(HWND(component->getAdapter()->getHandle()), HMENU(getAdapter()->getHandle()));
			}

			virtual void onHierarchyUpdate() override 
			{
				::DrawMenuBar(HWND(_component->getAdapter()->getHandle()));
			}

		private:
			// Instance Variables
			Component* _component;
		};

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
				HDC hdc = ::GetDC(NULL);
				scale = float(::GetDeviceCaps(hdc, LOGPIXELSX)) / 96.0f;
				::ReleaseDC(NULL, hdc);
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
				_menu = new MenuBar(this);

			return *_menu;
		}
	}
}

