#ifndef _NATIVE_CONDITION_VARIABLE_H_
#define _NATIVE_CONDITION_VARIABLE_H_ 1

// Module Dependencies
#include "mutex.h"
#include "semaphore.h"

namespace native
{
	/**
		A ConditionVariable allows a Thread to wait for a particular condition
		to be met on a protected resource, without having to explicitly unlock
		the Mutex protecting that resource to poll the condition's status.
	 */
	class ConditionVariable
	{
	public:
		/** 
			Constructor.
			\param mutex Mutex protecting the shared resource.
		 */
		ConditionVariable(Mutex& mutex);

		/** Destructor. */
		~ConditionVariable();

		/**
			Waits for this ConditionVariable to be signalled to indicate a
			condition has been met to access the protected resource.
		 */
		void wait();

		/**
			Signals the ConditionVariable allowing just one waiting Thread through.
			
		 */
		void signalOne();

		/**
			Signals the ConditionVariable, allowing all waiting Threads to execute.
		 */
		void signalAll();

	private:
		// Instance Variables
		Semaphore _waiters;
		Mutex& _mutex;
		int _waitCount;
	};
}

#endif // _NATIVE_CONDITION_VARIABLE_H_

