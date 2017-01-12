// Module Dependencies
#include "../../include/app.h"



#include <jni.h>

static const char* _message = 0;

extern "C" jstring Java_libnative_ui_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */)
{
	return env->NewStringUTF(_message);
}

namespace Native
{
	namespace UI
	{
		App::App()
		{
		}

		void App::setMessage(const char* message)
		{
			_message = message;
		}
	}
}

