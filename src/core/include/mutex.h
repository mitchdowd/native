#ifndef _NATIVE_MUTEX_H_
#define _NATIVE_MUTEX_H_ 1

// Local Dependencies
#include "exception.h"

namespace native
{
	/**
		A Mutex is a resource locking mechanism, which can lock and release a
		resource and allow resource consumers to block until the resource is
		available.
	 */
	class Mutex
	{
	public:
		/**
			Creates an unnamed, in-process Mutex. The Mutex is initially
			unlocked.
		 */
		Mutex();

		/**
			Move constructor. Moves the other Mutex to this instance.
			\param other The Mutex to move.
		 */
		Mutex(Mutex&& other) : _handle(other._handle) { other._handle = nullptr; }

		/** Destructor. */
		~Mutex();

		/**
			Locks the Mutex. If the Mutex is already locked, this waits until
			it is released before claiming the lock.
		 */
		void lock();

		/**
			Attempts to lock the Mutex, without waiting. If the Mutex is already
			locked, it does not claim the lock. If the Mutex is free, this claims
			the lock.
			\return true if lock is claimed, false if already locked elsewhere.
		 */
		bool tryLock();

		/**
			Releases the Mutex to allow other code to lock it.
		 */
		void release();

	private:
		// Instance Variables
		handle_t _handle;
	};
}

#endif // _NATIVE_MUTEX_H_

