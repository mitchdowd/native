// System Dependencies
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

// Module Dependencies
#include "../include/exception.h"
#include "../include/thread.h"

namespace native
{
    typedef void* (*start_routine_t)(void*);

	static thread_local Thread* _current = nullptr;

    Thread::Thread(const Function<void>& func) : _func(func), _started(false), _id(0)
    {
        start(func);
    }

    Thread::~Thread()
    {
        while (!_started)
            yield();

		_current = nullptr;
    }

    void Thread::start(const Function<void>& func)
    {
        if (_handle != nullptr)
            throw InvalidStateException();

        _func = func;

        pthread_t id;

        if (::pthread_create(&id, nullptr, start_routine_t(&entryPoint), this) != 0)
            throw InsufficientResourcesException();

        _handle = (handle_t) id;
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

	Thread* Thread::getCurrent()
	{
		return _current;
	}

	int64_t Thread::getCurrentId()
	{
        return (int64_t) ::gettid();
	}

    ptrint_t Thread::entryPoint(Thread* thread)
    {
        ptrint_t result = 0;

		_current = thread;
        thread->_id = getCurrentId();
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

