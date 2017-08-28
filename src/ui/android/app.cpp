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

        class OptionsMenu : public Menu
        {
        public:
            OptionsMenu(handle_t handle) : Menu(handle) {}

            void populate(const jni::Object& menu) const;

        protected:
            virtual void onHierarchyUpdate() override;
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

                _menu = new OptionsMenu(appMenu.isNull()? nullptr : new jni::Object(appMenu));
            }

            return *_menu;
		}

        void OptionsMenu::onHierarchyUpdate()
        {
            // TODO: Call Activity.invalidateOptionsMenu()
        }

        void OptionsMenu::populate(const jni::Object& menu) const
        {
            auto children = getChildren();

            // TODO: Set all initial handles in the tree hierarchy.
            for (auto child : children) {
                if (child.type == MenuItemType::Menu) {
                    jni::Object subMenu = menu.call<jni::Object>("addSubMenu(Ljava/lang/CharSequence;)Landroid/view/SubMenu;", child.menu->getText().toArray());

                    // TODO: Set the menu handle.

                    // TODO: Populate menu children.
                }
                else if (child.type == MenuItemType::Action) {
                    jni::Object menuItem = menu.call<jni::Object>("add(Ljava/lang/CharSequence;)Landroid/view/MenuItem;", child.action->getText().toArray());

                    // TODO: Set the action handle.
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

