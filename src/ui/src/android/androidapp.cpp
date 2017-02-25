// External Dependencies
#include "../../../../lib/jnipp/jnipp.h"

// Module Dependencies
#include "../../include/app.h"

namespace native
{
    namespace ui
    {
        void init(_JNIEnv* env, _jobject* activity)
        {
            jni::init(env);

            App::setAppHandle(activity);
        }
    }
}