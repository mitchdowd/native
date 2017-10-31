// System Dependencies
#include <windows.h>

// Module Dependencies
#include "../include/semaphore.h"

namespace native
{
	Semaphore::Semaphore(int maxCount) : _maxCount(maxCount)
	{
		if ((_handle = ::CreateSemaphore(NULL, maxCount, maxCount, NULL)) == 0)
			throw Exception("Mutex::Mutex");
	}

	Semaphore::Semaphore(Semaphore&& other) : _handle(other._handle), _maxCount(other._maxCount)
	{
		other._handle = nullptr; 
		other._maxCount = 0;
	}

	Semaphore::~Semaphore()
	{
		::CloseHandle(_handle);
	}

	void Semaphore::acquire()
	{
		switch (::WaitForSingleObject(_handle, INFINITE))
		{
		case WAIT_OBJECT_0:
			return;

		case WAIT_TIMEOUT:
			throw InterruptException();

		case WAIT_ABANDONED:
			throw InterruptException("Abandoned Semaphore detected");

		default:
			throw Exception("Semaphore::acquire");
		}
	}

	bool Semaphore::tryAcquire()
	{
		switch (::WaitForSingleObject(_handle, 0))
		{
		case WAIT_OBJECT_0:
			return true;

		case WAIT_TIMEOUT:
			return false;

		case WAIT_ABANDONED:
			throw InterruptException("Abandoned Semaphore detected");

		default:
			throw Exception("Semaphore::tryAcquire");
		}
	}

	void Semaphore::release()
	{
		if (::ReleaseSemaphore(_handle, 1, NULL) == 0)
			throw Exception("Semaphore::release");
	}
}

