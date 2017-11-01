#define NO_STRICT 1

// System Dependencies
#include <windows.h>

// Module Dependencies
#include "../include/exception.h"
#include "../include/thread.h"

namespace native
{
	static thread_local Thread* _current = nullptr;

	Thread::Thread(const Function<void>& func) : _handle(nullptr), _func(func), _started(false), _id(0)
	{
		start(_func);
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

		// Create the Thread resource with the OS.
		_handle = ::CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(&entryPoint), this, 0, NULL);

		if (_handle == NULL)
			throw InsufficientResourcesException();
	}

	void Thread::join() const
	{
		::WaitForSingleObject(_handle, INFINITE);
	}

	void Thread::sleep(uint32_t milliSeconds)
	{
		if (milliSeconds > MAXDWORD)
			milliSeconds = MAXDWORD;

		::Sleep(milliSeconds);
	}

	void Thread::yield()
	{
		::YieldProcessor();
	}

	Thread* Thread::getCurrent()
	{
		return _current;
	}

	int64_t Thread::getCurrentId()
	{
		return ::GetCurrentThreadId();
	}

	ptrint_t Thread::entryPoint(Thread* thread)
	{
		_current = thread;
		thread->_started = true;

		try
		{
			// Execute the Thread's Function.
			thread->_func();
		}
		catch (...)
		{
			return 1;
		}

		return 0;
	}
}

