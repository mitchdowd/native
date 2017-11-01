// External Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

TEST(Semaphore_tryAcquireDoesNotBlock)
{
	Semaphore semaphore = 1;

	semaphore.acquire();	// Decrements to zero (locked).
	
	ASSERT(semaphore.tryAcquire() == false);
	semaphore.release();
}

