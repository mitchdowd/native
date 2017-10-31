// External Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

TEST(ConditionVariable_waitsToBeSignalled)
{
	bool signalled = false;
	bool handled = false;
	Mutex lock;	// Lock for "signalled" and "handled"
	ConditionVariable cond(lock);

	// Start a thread that waits for a condition.
	Thread thread([&]() {
		lock.lock();	// Need to lock before accessing "signalled".

		cond.wait();

		handled = signalled;

		lock.release();
	});

	Thread::sleep(100);

	// Update the signalled condition.
	lock.lock();
	signalled = true;
	lock.release();
	
	cond.signalOne();

	// Wait for the worker thread.
	thread.join();

	ASSERT(handled);
}

