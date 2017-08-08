#ifndef _NATIVE_UI_APP_H_
#define _NATIVE_UI_APP_H_ 1

// Core Dependencies
#include "../../core/include/platform.h"

// Module Dependencies
#include "menu.h"
#include "window.h"

namespace native
{
	namespace ui
	{
		/**
			Provides the entry point and overall application management functions
			for a UI-based application.
		 */
		class App : public Window
		{
		public:
			/** Destructor. */
			~App();

			/**
				Enters an event loop centered on this Window. The event loop will
				continue until either a quit message is posted, or this Window is
				closed.
			 */
			int run();

			/**
				Gets the application menu for this App. This is created automatically
				when required.
				\return The application menu.
			 */
			Menu& getMenu();

            /**
                Gets what _should be_ the only App instance, if there is one.
                \return The App instance.
             */
			static App* getInstance() { return (App*) _instance; }

            /**
                Gets a scaling factor for the default display. This allows for high
                (or low) DPI displays to still render outputs in a sensible way.
                \return The scaling factor applied to display output operations.
             */
            static float getDisplayScale();

			/**
				Sets a system handle for this App. Not all platforms have a relevant app
			 	handle. Those platforms that do will automatically call this function.
			 	\param handle The handle to set.
			 */
			static void setAppHandle(handle_t handle) noexcept { _handle = handle;}

			/**
				Gets the system-wide app-handle. Not all platforms have a relevant app handle.
			 	Those which do not will return null.
			 	\return The app handle.
			 */
			static handle_t getAppHandle() noexcept { return _handle; }

		protected:
			/** Default constructor. */
			App();

		private:
			// Static Variables
			static handle_t _handle;
            static volatile App* _instance;

			// Instance Variables
			Menu* _menu;
		};

		/**
			Exception thrown when an error occurred initializing an App.
		 */
		class AppInitializationException : public Exception
		{
		public:
			AppInitializationException(const char* msg) : Exception(msg) {}
		};
	}
}

#if defined(NATIVE_PLATFORM_WIN32)

// Forward Declarations
struct HINSTANCE__;

#define NATIVE_UI_APP(TApp)							\
	int __stdcall WinMain(							\
		HINSTANCE__* hInstance,						\
		HINSTANCE__* hPrevInstance, 				\
		char* lpCmdLine,							\
		int nCmdShow								\
	) {												\
		return (new TApp())->run();					\
	}												\
	int main(int argc, char** argv) {				\
		return (new TApp())->run();					\
	}



#elif defined(NATIVE_PLATFORM_ANDROID)

// Forward Declarations
class _jobject;
struct _JNIEnv;

namespace native {
	namespace ui {
		// Forward Declarations
		void init(_JNIEnv*, _jobject*);
	}
}

#define NATIVE_UI_APP(TApp)							\
	extern "C" void 								\
	Java_libnative_ui_MainActivity_onCreate(		\
		_JNIEnv* env,								\
		_jobject* activity							\
	) {												\
		native::ui::init(env, activity);			\
        if (App::getInstance() == nullptr)          \
		    new TApp();							    \
	}

#else
# error "Current platform not supported for native::ui."
#endif // NATIVE_PLATFORM_*

#endif // _NATIVE_UI_APP_H_

