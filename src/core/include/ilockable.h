#ifndef _NATIVE_ILOCKABLE_H_
#define _NATIVE_ILOCKABLE_H_ 1

namespace native
{
	/**
		A basic interface for resource locking.
	 */
	class ILockable
	{
	public:
		/** Virtual destructor. */
		virtual ~ILockable() {}

		/** Waits for and aquires the lock on this ILockable. */
		virtual void lock() = 0;

		/** Releases the current lock on this ILockable. */
		virtual void release() = 0;
	};
}

#endif // _NATIVE_ILOCKABLE_H_

