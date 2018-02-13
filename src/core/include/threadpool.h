#ifndef _NATIVE_THREAD_POOL_H_
#define _NATIVE_THREAD_POOL_H_ 1

// Module Dependencies
#include "conditionvariable.h"
#include "function.h"
#include "list.h"
#include "mutex.h"
#include "queue.h"
#include "thread.h"

namespace native
{
	/**
		ThreadPool is a helper class which queues tasks to be executed on one of
		many available worker threads. The enqueued tasks are generally short-
		lived and/or repetitive, so the ThreadPool helps to remove some of the
		overhead of creating and destroying a Thread itself.

		ThreadPool is fully static as there should only be one pool of Threads,
		with a thread count generally correlating to the number of processor
		cores.
	 */
	class ThreadPool
	{
	public:
		// Prevent Instantiation
		ThreadPool() = delete;

		/**
			Enqueues a Function to be called on the next available Thread.
			\param task The Function to be executed.
		 */
		static void enqueue(const Function<void>& task);

	private:
		// Variables
		static Queue<Function<void>> _tasks;
		static List<Thread*> _threads;
		static Mutex _lock;
		static ConditionVariable _taskAvailable;
		static bool _terminate;
	};
}

#endif // _NATIVE_THREAD_POOL_H_

