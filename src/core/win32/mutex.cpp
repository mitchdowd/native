// System Dependencies
#include <windows.h>

// Local Dependencies
#include "../include/exception.h"
#include "../include/mutex.h"

namespace native
{
	Mutex::Mutex()
	{
		if ((_handle = ::CreateMutex(NULL, FALSE, NULL)) == 0)
			throw Exception("Mutex::Mutex");
	}

	Mutex::Mutex(const String& name)
	{
		if ((_handle = ::CreateMutex(NULL, FALSE, name.toArray())) == 0)
		{
			switch (::GetLastError())
			{
			case ERROR_ACCESS_DENIED:
			case ERROR_INVALID_HANDLE:
				throw AccessException("No access to given named Mutex");
			}

			throw Exception("Mutex::Mutex");
		}
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

