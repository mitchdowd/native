#ifndef _NATIVE_UI_APP_H_
#define _NATIVE_UI_APP_H_ 1

// Core Dependencies
#include "../../core/include/platform.h"

// Module Dependencies
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
			/**
				Enters an event loop centered on this Window. The event loop will
				continue until either a quit message is posted, or this Window is
				closed.
			 */
			int run();

		protected:
			/** Default constructor. */
			App();
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

#define NATIVE_UI_APP(TApp)							\
	extern "C" void 								\
	Java_libnative_ui_MainActivity_onCreate(		\
		_JNIEnv* env,								\
		_jobject* activity							\
	) {												\
		new TApp();									\
	}

#else
# error "Current platform not supported for native::ui."
#endif // NATIVE_PLATFORM_*

#endif // _NATIVE_UI_APP_H_

