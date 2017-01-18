// External Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

int getSum(LinkedList<int>& list)
{
	int sum = 0;

	for (auto i : list)
		sum += i;

	return sum;
}

TEST(LinkedList_initializer_list)
{
	LinkedList<int> list = { 0, 1, 2, 3, 4 };

	ASSERT(list.getLength() == 5);
}

TEST(LinkedList_add)
{
	LinkedList<int> list;

	list.add(1);

	ASSERT(*list.begin() == 1);
}

TEST(LinkedList_iterator)
{
	LinkedList<int> list = { 0, 1, 2, 3, 4 };

	ASSERT(getSum(list) == 10);
}
