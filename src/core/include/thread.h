#ifndef _NATIVE_THREAD_H_
#define _NATIVE_THREAD_H_ 1

// Module Dependencies
#include "function.h"

namespace native
{
	/**
		An individual thread of execution within a Process.
	 */
	class Thread
	{
		// Prevent Copying
		Thread(const Thread&) = delete;

	public:
		/** Creates a Thread, but does not start it. */
		Thread() : _handle(nullptr), _func([]() {}), _started(false) {}

		/**
			Move constructor.
			\param other The Thread to move to this one.
		 */
		Thread(Thread&& other) : _handle(other._handle), _func(other._func), _started(other._started)
		{
			other._handle = nullptr;
			other._started = false;
		}

		/**
			Creates a Thread which will execute the given Function upon creation.
			\param func The Function to execute when started.
		 */
		Thread(const Function<void>& func);

		/** Destructor. Note, this does not end the Thread's execution. */
		virtual ~Thread();

		/**
			Starts the Thread, which will execute the given Function. The Thread
			must not have already been started.
			\param func The Function to execute.
		 */
		void start(const Function<void>& func);

		/** Waits for this thread to finish execution. */
		void join() const;

		/**
			Pauses execution of the current thread.
			\param milliSeconds The duration to sleep for, in milli-seconds.
		 */
		static void sleep(uint32_t milliSeconds);

		/** Relinquishes the current thread's execution context. */
		static void yield();

	private:
		/** Entry point to the Thread, as far as the OS is concerned. */
		static ptrint_t entryPoint(Thread*);

		// Instance Variables
		handle_t _handle;
		Function<void> _func;
		bool _started;
	};
}

#endif // _NATIVE_THREAD_H_

