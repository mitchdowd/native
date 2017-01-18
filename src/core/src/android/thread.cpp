// System Dependencies
#include <pthread.h>
#include <unistd.h>

// Module Dependencies
#include "../../include/exception.h"
#include "../../include/thread.h"

namespace native
{
    typedef void* (*start_routine_t)(void*);

    Thread::Thread(const Function<void>& func) : _func(func), _started(false)
    {
        pthread_t id;

        if (::pthread_create(&id, nullptr, start_routine_t(&entryPoint), this) != 0)
            throw InsufficientResourcesException();

        _handle = (handle_t) id;
    }

    Thread::~Thread()
    {
        while (!_started)
            yield();
    }

    void Thread::join() const
    {
        ::pthread_join(pthread_t(_handle), nullptr);
    }

    void Thread::sleep(uint32_t milliSeconds)
    {
        ::usleep(milliSeconds * 1000);
    }

    void Thread::yield()
    {
        ::sched_yield();
    }

    ptrint_t Thread::entryPoint(Thread* thread)
    {
        ptrint_t result = 0;

        thread->_started = true;

        try
        {
            // Execute the Thread's Function.
            thread->_func();
        }
        catch (...)
        {
            result = 1;
        }

        return result;
    }
}

