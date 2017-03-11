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

TEST(Thread_start)
{
	hasUpdated = false;

	Thread thread(&doUpdate);
	thread.join();

	ASSERT(hasUpdated);
}

TEST(Thread_assertIsOwnThread)
{
	tlHasUpdated = false;

	Thread thread(&doUpdateTl);
	thread.join();

	ASSERT(!tlHasUpdated);
}
