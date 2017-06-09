#ifndef _NATIVE_SYSTEM_H_
#define _NATIVE_SYSTEM_H_ 1

// Module Dependencies
#include "function.h"

namespace native
{
	/**
		System provides system-scoped functionality, which tends to not belong
		in its own class for one reason or another.
	 */
	class System
	{
		// Prevent Instantiation
		System() = delete;

	public:
		/**
			Registers the given Function to be called on program termination.
			\param func The Function to register.
		 */
		static void onExit(const Function<void>& func);
	};
}

#endif // _NATIVE_SYSTEM_H_
