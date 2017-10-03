// External Depdendencies
#include "../../../lib/jnipp/jnipp.h"

// Module Dependencies
#include "../include/app.h"
#include "../include/eventqueue.h"

namespace native
{
    namespace ui
    {
        // Static Variable Initialisations
        thread_local int EventQueue::_exitCode = 0;

        bool EventQueue::handleEvent(bool block)
        {
            throw NotImplementedException();
        }

        void EventQueue::quitWithCode(int exitCode)
        {
            jni::Object* activity = (jni::Object*) App::getAppHandle();

            activity->call<void>("finish");
        }
    }
}

