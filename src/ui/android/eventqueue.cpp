// Module Dependencies
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
            throw NotImplementedException();
        }
    }
}

