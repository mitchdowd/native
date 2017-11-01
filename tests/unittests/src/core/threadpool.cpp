// External Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

TEST(ThreadPool_enqueueExecutesFunction)
{
	bool hasUpdated = false;

	ThreadPool::enqueue([&] {
		hasUpdated = true;
	});

	Thread::sleep(100);

	ASSERT(hasUpdated);
}

