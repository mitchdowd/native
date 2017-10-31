// External Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

TEST(Semaphore_tryAcquireDoesNotBlock)
{
	Semaphore semaphore(1);

	semaphore.acquire();
	
	ASSERT(semaphore.tryAcquire() == false);
	semaphore.release();
}

