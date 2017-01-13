#ifndef _NATIVE_THREAD_H_
#define _NATIVE_THREAD_H_ 1

// Module Dependencies
#include "types.h"

namespace native
{
	/**
		An individual thread of execution within a Process.
	 */
	class Thread
	{
	public:
		/**
			Pauses execution of the current thread.
			\param milliSeconds The duration to sleep for, in milli-seconds.
		 */
		static void sleep(uint32_t milliSeconds);

		/** Relinquishes the current thread's execution context. */
		static void yield();
	};
}

#endif // _NATIVE_THREAD_H_

