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

using namespace native::ui;

extern "C"
{
    void Java_libnative_ui_MainActivity_onDestroyApp(_JNIEnv*, jni::jobject) {
        delete native::ui::App::getInstance();
    }

    bool Java_libnative_ui_MainActivity_onAction(_JNIEnv*, jni::jobject, int actionId) {
        Action* action = Action::fromId(actionId);

        if (action == nullptr)
            return false;

        action->emit();
        return true;
    }
}

