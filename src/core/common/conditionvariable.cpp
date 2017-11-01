// Local Dependencies
#include "../include/conditionvariable.h"

namespace native
{
	ConditionVariable::ConditionVariable(ILockable& lock) : _waiters(0), _lock(lock), _waitCount(0)
	{
	}

	ConditionVariable::~ConditionVariable()
	{
	}

	void ConditionVariable::wait()
	{
		Atomic::increment(_waitCount);
		_lock.release();

		_waiters.acquire();
		
		_lock.lock();
		Atomic::decrement(_waitCount);
	}

	void ConditionVariable::signalOne()
	{
		if (_waitCount > 0)
			_waiters.release();
	}

	void ConditionVariable::signalAll()
	{
		int toRelease = _waitCount;

		for (int i = 0; i < toRelease; i++)
			_waiters.release();
	}
}

