// External Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

// Constants
#define THREAD_WAIT_TIME 10

// Static Variables
static bool hasUpdated = false;
static thread_local bool tlHasUpdated = false;

// Helper Functions
static void doUpdate() { hasUpdated = true; }
static void doUpdateTl() { tlHasUpdated = true; }

TEST(Thread_start)
{
	hasUpdated = false;

	Thread thread(&doUpdate);
	Thread::sleep(THREAD_WAIT_TIME);

	ASSERT(hasUpdated);
}

TEST(Thread_assertIsOwnThread)
{
	tlHasUpdated = false;

	Thread thread(&doUpdateTl);
	Thread::sleep(THREAD_WAIT_TIME);

	ASSERT(!tlHasUpdated);
}
