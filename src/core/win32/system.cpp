// Standard Dependencies
#include <cstdlib>

// Module Dependencies
#include "../include/spinlock.h"
#include "../include/stack.h"
#include "../include/system.h"

namespace native
{
	void System::onExit(const Function<void>& func)
	{
		static SpinLock lock;
		static Stack< Function<void> >* funcs = nullptr;

		lock.lock();

		if (funcs == nullptr)
		{
			funcs = new Stack< Function<void> >();

			// Register as a C++ atexit() handler.
			std::atexit([]() {
				while (funcs->getSize())
					funcs->pop()();

				delete funcs;
			});
		}

		funcs->push(func);
		lock.release();
	}

	float System::getDisplayScale()
	{
		static float scale;

		if (scale == 0.0f)
			scale = 3.0f;  // TODO: Use GetDeviceCaps() or equivalent to calculate this.

		return scale;
	}
}
