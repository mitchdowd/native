// System Dependencies
#include <pthread.h>
#include <unistd.h>

// Module Dependencies
#include "../../include/thread.h"

namespace native
{
    void Thread::sleep(uint32_t milliSeconds)
    {
        ::usleep(milliSeconds * 1000);
    }

    void Thread::yield()
    {
        ::sched_yield();
    }
}

