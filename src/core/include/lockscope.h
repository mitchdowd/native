#ifndef _NATIVE_LOCK_SCOPE_H_
#define _NATIVE_LOCK_SCOPE_H_ 1

// Module Dependencies
#include "ilockable.h"

namespace native
{
	/**
		Automatically locks and unlocks an ILockable in its scope lifetime.
	 */
	class LockScope
	{
	public:
		/**
			Acquires a lock on the given ILockable.
			\param lock The lock to acquire.
		 */
		LockScope(ILockable& lock) : _lock(lock) { _lock.lock(); }

		/**
			Releases the lock on the scope's lockable object.
		 */
		~LockScope() { _lock.release(); }
		
	private:
		// Instance Variables
		ILockable& _lock;
	};
}

#endif // _NATIVE_LOCK_SCOPE_H_

