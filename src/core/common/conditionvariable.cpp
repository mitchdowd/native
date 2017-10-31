// Local Dependencies
#include "../include/conditionvariable.h"

namespace native
{
	ConditionVariable::ConditionVariable(Mutex& mutex) : _waiters(0), _mutex(mutex), _waitCount(0)
	{
	}

	ConditionVariable::~ConditionVariable()
	{
	}

	void ConditionVariable::wait()
	{
		Atomic::increment(_waitCount);
		_mutex.release();

		_waiters.acquire();
		
		_mutex.lock();
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

