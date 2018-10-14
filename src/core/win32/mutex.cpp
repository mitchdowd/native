// System Dependencies
#include <Windows.h>

// Local Dependencies
#include "../include/exception.h"
#include "../include/mutex.h"

namespace native
{
	Mutex::Mutex()
	{
		if ((_handle = ::CreateMutex(NULL, FALSE, NULL)) == NULL)
			throw Exception("Mutex::Mutex");
	}

	Mutex::~Mutex()
	{
		::CloseHandle(_handle);
	}

	void Mutex::lock()
	{
		switch (::WaitForSingleObject(_handle, INFINITE))
		{
		case WAIT_OBJECT_0:
			return;

		case WAIT_TIMEOUT:
			throw InterruptException();

		case WAIT_ABANDONED:
			throw InterruptException("Abandoned Mutex detected");

		default:
			throw Exception("Mutex::lock");
		}
	}

	bool Mutex::tryLock()
	{
		switch (::WaitForSingleObject(_handle, 0))
		{
		case WAIT_OBJECT_0:
			return true;

		case WAIT_TIMEOUT:
			return false;

		case WAIT_ABANDONED:
			throw InterruptException("Abandoned Mutex detected");

		default:
			throw Exception("Mutex::tryLock");
		}
	}

	void Mutex::release()
	{
		if (::ReleaseMutex(_handle) == 0)
			throw Exception("Mutex::unlock");
	}
}

