// Module Dependencies
#include "../include/atomic.h"
#include "../include/spinlock.h"
#include "../include/thread.h"

namespace native
{
	SpinLock::SpinLock() noexcept : _waitCount(0)
	{
	}

	SpinLock::~SpinLock()
	{
		Atomic::exchange(_waitCount, 0);
	}

	void SpinLock::lock() 
	{
		while (Atomic::compareExchange(_waitCount, 1, 0) != 0)
			Thread::yield();
	}

	void SpinLock::release() 
	{
		Atomic::exchange(_waitCount, 0);
	}

	bool SpinLock::isLocked() const noexcept
	{
		return _waitCount != 0;
	}
}

