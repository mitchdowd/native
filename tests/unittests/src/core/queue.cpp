// External Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

TEST(Queue_pushPop)
{
	Queue<int> queue;

	queue.push(1);
	queue.push(2);
	queue.push(3);

	ASSERT(queue.pop() == 1);
	ASSERT(queue.pop() == 2);
	ASSERT(queue.pop() == 3);
}
