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
			/** TEMPORARY ONLY - Cross platform function test. */
			void setMessage(const char* message);

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
		(new TApp())->setMessage("Hello World");	\
		return 0;									\
	}												\
	int main(int argc, char** argv) {				\
		(new TApp())->setMessage("Hello World");	\
		return 0;									\
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
		(new TApp())->setMessage("Hello World");	\
	}

#else
# error "Current platform not supported for Native::UI."
#endif // NATIVE_PLATFORM_*

#endif // _NATIVE_UI_APP_H_

