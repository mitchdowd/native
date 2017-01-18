// Testing Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

/** Helper function which adds up all keys and values, for verification. */
static int getSum(Set<int>& set)
{
	int sum = 0;

	for (auto value : set)
		sum += value;

	return sum;
}

TEST(Set_add)
{
	Set<int> set;

	set.add(1);

	ASSERT(set.getLength() == 1);
}

TEST(Set_iterate)
{
	Set<int> set = { 1, 2, 3 };

	ASSERT(getSum(set) == 6);
}

TEST(Set_remove)
{
	Set<int> set;

	set.add(1);
	set.add(2);
	set.add(3);

	if (set.contains(2))
		set.remove(2);

	ASSERT(getSum(set) == 4);

	// Should do nothing, silently.
	set.remove(2);

	ASSERT(set.getLength() == 2);
}
