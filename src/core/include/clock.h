#ifndef _NATIVE_CLOCK_H_
#define _NATIVE_CLOCK_H_ 1

// Module Dependencies
#include "types.h"

namespace native
{
	/**
		A simple timing mechanism for measuring how much time has passed between
		two code statements. Time between Clock ticks is not dependent on the
		DateTime values, so changes in computer settings will not affect it.
	 */
	class Clock final
	{
	public:
		/** Storage type for a single time moment, or "tick". */
		typedef uint64_t tick_t;

		/**
			Gets the current tick value. Tick values can be compared to determine
			how much time has passed.
		 */
		static tick_t tick();

		/**
			Converts the number of ticks to a duration in milliseconds.
		 	\param duration The number of ticks.
		 	\return The number of milliseconds.
		 */
		static tick_t toMilliSeconds(tick_t duration);
	};
}

#endif // _NATIVE_CLOCK_H_

