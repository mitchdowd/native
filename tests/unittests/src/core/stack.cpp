// External Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

TEST(Stack_pushPop)
{
	Stack<int> stack;

	stack.push(1);
	stack.push(2);
	stack.push(3);

	ASSERT(stack.pop() == 3);
	ASSERT(stack.pop() == 2);
	ASSERT(stack.pop() == 1);
}
