// External Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

// Static Variables
static bool hasUpdated = false;
static thread_local bool tlHasUpdated = false;

TEST(Task_start)
{
	hasUpdated = false;

	Task<void> task([]() { hasUpdated = true; });

	task.join();

	ASSERT(hasUpdated);
}

TEST(Task_assertIsOwnThread)
{
	tlHasUpdated = false;

	Task<void> task([]() { tlHasUpdated = true; });
	task.join();

	ASSERT(!tlHasUpdated);
}

TEST(Task_generatesResult)
{
	Task<int> task([]() { 
		Thread::sleep(10); 
		return 100; 
	});

	ASSERT(task.getResult() == 100);
}

