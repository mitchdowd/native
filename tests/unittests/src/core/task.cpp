// External Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

// Static Variables
static bool hasUpdated = false;
static thread_local bool tlHasUpdated = false;

// Helper Functions
static void doUpdate() { hasUpdated = true; }
static void doUpdateTl() { tlHasUpdated = true; }

TEST(Task_start)
{
	hasUpdated = false;

	Task<void> task(&doUpdate);

	task.join();

	ASSERT(hasUpdated);
}

TEST(Task_assertIsOwnThread)
{
	tlHasUpdated = false;

	Task<void> task(&doUpdateTl);
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

