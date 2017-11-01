// System Dependencies
#include <errno.h>
#include <pthread.h>

// Local Dependencies
#include "../include/exception.h"
#include "../include/mutex.h"

namespace native
{
	Mutex::Mutex()
	{
		if (::pthread_mutex_init((pthread_mutex_t*) &_handle, nullptr) != 0)
            throw Exception("Mutex::Mutex");
	}

	Mutex::~Mutex()
	{
        if (_handle)
            ::pthread_mutex_destroy((pthread_mutex_t*) &_handle);
	}

	void Mutex::lock()
	{
		switch (::pthread_mutex_lock((pthread_mutex_t*) &_handle))
        {
        case 0:
            return; // All is well.

        case EDEADLK:
            throw InvalidStateException("Mutex already owned");

        default:
            throw Exception("Mutex::lock");
        }
	}

	bool Mutex::tryLock()
	{
        switch (::pthread_mutex_trylock((pthread_mutex_t*) &_handle))
        {
        case 0:
            true; // All is well.

        case EBUSY:
            return false;

        case EDEADLK:
            throw InvalidStateException("Mutex already owned");

        default:
            throw Exception("Mutex::tryLock");
        }
	}

	void Mutex::release()
	{
        switch (::pthread_mutex_unlock((pthread_mutex_t*) &_handle))
        {
        case 0:
            return; // All is well.

        case EPERM:
            throw InvalidStateException("Mutex not owned");

        default:
            throw Exception("Mutex::release");
        }
	}
}

