// Testing Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

/** Helper function which adds up all keys and values, for verification. */
static int getSum(Map<int, int>& map)
{
	int sum = 0;

	for (auto pair : map)
		sum += pair.key + pair.value;

	return sum;
}

TEST(Map_defaultConstructor)
{
	Map<int, int> map;

	ASSERT(map.getLength() == 0);
}

TEST(Map_initializerListConstructor)
{
	Map<int, int> map = {
		{ 1, 10 },
		{ 2, 20 }
	};

	ASSERT(map.getLength() == 2);
}

TEST(Map_add)
{
	Map<int, int> map;

	map.add(1, 2);

	ASSERT(map.getLength() == 1);
}

TEST(Map_get)
{
	Map<int, int> map = {
		{ 1, 10 },
		{ 2, 20 }
	};

	ASSERT(map[1] == 10);
	ASSERT(map[2] == 20);
}

TEST(Map_iterate)
{
	Map<int, int> map;

	map.add(1, 10);
	map.add(2, 20);
	map.add(3, 30);

	ASSERT(getSum(map) == 66);
}


TEST(Map_remove)
{
	Map<int, int> map;

	map.add(1, 10);
	map.add(2, 20);
	map.add(3, 30);

	if (map.containsKey(2))
		map.remove(2);

	ASSERT(getSum(map) == 44);

	// This should do nothing.
	map.remove(2);

	ASSERT(map.getLength() == 2);
}
