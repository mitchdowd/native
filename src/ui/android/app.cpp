// External Dependencies
#include "../../../lib/jnipp/jnipp.h"

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

        class OptionsMenu : public Menu
        {
        public:
            OptionsMenu() : Menu() {}

            void populate(const jni::Object& menu);
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
                jni::Object* activity = (jni::Object*) App::getInstance()->getAppHandle();
                jni::Object  appMenu  = activity->call<jni::Object>("getAppMenu()Landroid/view/Menu;");

                _menu = new OptionsMenu();

                if (!appMenu.isNull())
                    ((OptionsMenu*) _menu)->populate(appMenu);
            }

            return *_menu;
		}

        void OptionsMenu::populate(const jni::Object& menu)
        {
            auto children = getChildren();

            // Set up the adapter if we don't have one.
            if (!getAdapter())
                setAdapter(new MenuAdapter(new jni::Object(menu)));

            IMenuAdapter* adapter = getAdapter();

            // Parse the tree hierarchy, instantiating system resources.
            for (size_t i = 0; i < children.getLength(); ++i) {
                auto& child = children[i];

                if (child.type == MenuItemType::Menu) {
                    adapter->insert(i, *child.menu);
                }
                else if (child.type == MenuItemType::Action) {
                    adapter->insert(i, *child.action);
                }
            }
        }
	}
}

// Namespace Usage
using namespace native::ui;

extern "C"
{
    void Java_libnative_ui_MainActivity_populateOptionsMenu(_JNIEnv*, jni::jobject, jni::jobject optionsMenu)
    {
        ((OptionsMenu&) App::getInstance()->getMenu()).populate(optionsMenu);
    }
}

