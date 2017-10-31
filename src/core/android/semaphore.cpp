// System Dependencies
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <semaphore.h>

// Module Dependencies
#include "../include/semaphore.h"

namespace native
{
	Semaphore::Semaphore(int maxCount) : _maxCount(maxCount), _handle(new sem_t())
	{
		if (::sem_init((sem_t*) _handle, 0, maxCount) != 0)
			throw Exception("Semaphore::Semaphore");
	}

	Semaphore::Semaphore(Semaphore&& other) : _handle(other._handle), _maxCount(other._maxCount)
	{
		other._handle = nullptr;
		other._maxCount = 0;
	}

	Semaphore::~Semaphore()
	{
		::sem_destroy((sem_t*) _handle);
		delete (sem_t*) _handle;
	}

	void Semaphore::acquire()
	{
		if (::sem_wait((sem_t*) _handle) != 0)
			throw Exception("Semaphore::acquire");
	}

	bool Semaphore::tryAcquire()
	{
		if (::sem_trywait((sem_t*) _handle) != 0)
		{
			if (errno == EAGAIN)
				return false;

			throw Exception("Semaphore::tryAcquire");
		}

		return true;
	}

	void Semaphore::release()
	{
		if (::sem_post((sem_t*) _handle) != 0)
			throw Exception("Semaphore::release");
	}
}

