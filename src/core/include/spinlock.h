#ifndef _NATIVE_SPIN_LOCK_H_
#define _NATIVE_SPIN_LOCK_H_ 1

// Module Dependencies
#include "ilockable.h"
#include "types.h"

namespace native
{
	/**
		SpinLock is a very light-weight mutual exclusion mechanism for thread
		protection. It does not utilise any OS functionality, so is very low
		on resources, and can be staticially initialised.
	
		This should never be used to protect a resource for more than a few
		execution statements, as it will leave competing threads executing.
		Use a Mutex when protecting a resource for longer periods.
	 */
	class SpinLock : public ILockable
	{
	public:
		/** Creates an unlocked SpinLock. */
		SpinLock() noexcept;

		/** Destroys the SpinLock. */
		~SpinLock();

		/** Waits for and aquires the lock on this SpinLock. */
		void lock() override;

		/** Releases the current lock on this SpinLock. */
		void release() override;

		/**
			Tells whether a lock is currently held on the SpinLock.
			\return true if locked, false if available.
		 */
		bool isLocked() const noexcept;

	private:
		// Instance Variables
		volatile int32_t _waitCount;
	};
}

#endif // _NATIVE_SPIN_LOCK_H_

