#ifndef _NATIVE_SINGLETON_H_
#define _NATIVE_SINGLETON_H_ 1

// Module Dependencies
#include "spinlock.h"
#include "system.h"

namespace native
{
	/**
		Singleton wraps a single instance of the given type.  All instances of the
		same type returned by Singleton::get are the same instance, created during
		the first call to Singleton::get().
	 */
	template <class T>
	class Singleton
	{
		// Prevent Creation
		Singleton() = delete;

	public:
		/** Retrieves the instance held by this Singleton. */
		static T& get();

	private:
		// Static Variables
		static SpinLock _lock;
	};

	// ---------------------------------------------------------------------- //
	//                        Singleton Implementation                        //
	// ---------------------------------------------------------------------- //

	namespace internal
	{
		void singletonNotInitialised();
	}

	template <class T> SpinLock Singleton<T>::_lock;

	template <class T>
	T& Singleton<T>::get()
	{
		static T* instance = 0;

		if (!instance)
		{
			_lock.lock();

			try
			{
				if (!instance)
				{
					T* obj = new T();

					// Make sure it is deleted later on.
					System::onExit([obj]() { delete obj; });

					instance = obj;
				}
			}
			catch (...) {
			}

			_lock.release();
		}

		if (!instance)
			internal::singletonNotInitialised();

		return *instance;
	}
}

#endif // _NATIVE_SINGLETON_H_
