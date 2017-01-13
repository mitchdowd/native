#define NO_STRICT 1

// System Dependencies
#include <windows.h>

// Module Dependencies
#include "../../include/thread.h"

namespace native
{
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
}

