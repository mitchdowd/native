// External Dependencies
#include "../../../lib/jnipp/jnipp.h"

// Module Dependencies
#include "../include/app.h"

namespace native
{
    namespace ui
    {
        void init(_JNIEnv* env, jni::jobject activity)
        {
            jni::init(env);

            App::setAppHandle(new jni::Object(activity));
        }
    }
}

extern "C"
{
    void Java_libnative_ui_MainActivity_onDestroyApp(_JNIEnv*, jni::jobject) {
        delete native::ui::App::getInstance();
    }
}

