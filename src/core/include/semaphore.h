#ifndef _NATIVE_SEMAPHORE_H_
#define _NATIVE_SEMAPHORE_H_ 1

// Local Dependencies
#include "exception.h"

namespace native
{
	/**
		Semaphore is a synchronisation primitive that maintains a count of
	 	available resources which can be acquired by waiting Threads. When
	 	the value of a Semaphore reaches zero
	 */
	class Semaphore
	{
	public:
		/**
			Creates the Semaphore with the given initial value.
			\param initialValue The initial value in the Semaphore.
		 */
		Semaphore(uint32_t initialValue = 0);

		/**
			Move constructor. Moves the other Semaphore to this instance.
			\param other The Semaphore to move.
		 */
		Semaphore(Semaphore&& other) noexcept;

		/** Destructor. */
		~Semaphore();

		/**
			Acquires a slot in the Semaphore, therefore decrementing the Semaphore
		 	value. If the Semaphore value is zero, then the executing Thread blocks
		 	until there is a slot available.
		 */
		void acquire();

		/**
			Tries to acquire a slot in the Semaphore without blocking. If the Semaphore
		 	value is zero, then the result is false and the calling thread will not block.
		 	Otherwise, the Semaphore value is decremented and true is returned.
			\return `true` if slot acquired, `false` if no slot available.
		 */
		bool tryAcquire();

		/**
			Release's the current Thread's hold on one of the Semaphore slots by
		 	incrementing the Semaphore value.
		 */
		void release();

	private:
		// Instance Variables
		handle_t _handle;
	};
}

#endif // _NATIVE_SEMAPHORE_H_

