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
		lock.lock();

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

TEST(ConditionVariable_signalAllReleasesAll)
{
	Mutex lock;
	ConditionVariable cond(lock);
	Thread threads[10];
	int finished = 0;

	for (int i = 0; i < 10; i++)
		threads[i].start([&]() {
			lock.lock();

			cond.wait();

			Atomic::increment(finished);

			lock.release();
		});

	Thread::sleep(100);

	cond.signalAll();

	for (int i = 0; i < 10; i++)
		threads[i].join();

	ASSERT(finished == 10);
}