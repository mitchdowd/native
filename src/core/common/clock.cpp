// Standard Dependencies
#include <chrono>

// Module Dependencies
#include "../include/clock.h"

namespace native
{
	typedef std::chrono::steady_clock chrono_t;

	Clock::tick_t Clock::tick()
	{
		return chrono_t::now().time_since_epoch().count();
	}

	Clock::tick_t Clock::toMilliSeconds(tick_t duration)
	{
		return 1000 * duration / chrono_t::period::den;
	}
}

