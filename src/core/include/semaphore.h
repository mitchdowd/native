#ifndef _NATIVE_SEMAPHORE_H_
#define _NATIVE_SEMAPHORE_H_ 1

// Local Dependencies
#include "exception.h"

namespace native
{
	/**
		Semaphore is a synchronisation primitive that allows only a certain
		number of threads to access a protected resource at a particular time.
	 */
	class Semaphore
	{
	public:
		/**
			Creates the Semaphore. It is initially unlocked.
			\param maxCount The maximum Threads to access at one time.
		 */
		Semaphore(int maxCount);

		/**
			Move constructor. Moves the other Semaphore to this instance.
			\param other The Semaphore to move.
		 */
		Semaphore(Semaphore&& other);


		/** Destructor. */
		~Semaphore();

		/**
			Acquires a slot in the Semaphore. If there is no available slot, then
			the executing Thread blocks until there is a slot available.
		 */
		void acquire();

		/**
			Tries to acquire a slot in the Semaphore without blocking. If there is
			no available slot, then the result is false.
			\return `true` if slot acquired, `false` if no slot available.
		 */
		bool tryAcquire();

		/**
			Release's the current Thread's hold on one of the Semaphore slots.
		 */
		void release();

		/**
			Gets the maximum number of Threads which can enter the Semaphore
			concurrently, as supplied in the constructor.
			\return The slot count.
		 */
		int getMaxCount() const noexcept { return _maxCount; }

	private:
		// Instance Variables
		handle_t _handle;
		int _maxCount;
	};
}

#endif // _NATIVE_SEMAPHORE_H_

