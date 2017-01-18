// Testing Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

class NonTrivial
{
public:
	int value;

	NonTrivial(int x = 0) : value(x * 10) {}
};

int getSum(List<int>& list)
{
	int sum = 0;

	for (auto i : list)
		sum += i;

	return sum;
}

TEST(List_initializer_list)
{
	List<int> list = { 0, 1, 2, 3, 4 };

	ASSERT(list.getLength() == 5);
}

TEST(List_add)
{
	List<int> list;

	list.add(1);

	ASSERT(list[0] == 1);
}

TEST(List_iterator)
{
	List<int> list = { 0, 1, 2, 3, 4 };

	ASSERT(getSum(list) == 10);
}

TEST(List_insert_remove)
{
	List<char> str;

	for (auto ch : "testing")
		str.add(ch);

	str.insert(3, 'X');

	ASSERT(str[7] == 'g');

	str.removeAt(3);

	ASSERT(str[6] == 'g');
}

TEST(List_nonTrivial)
{
	List<NonTrivial> list;

	for (int i = 0; i < 5; ++i)
		list.add(i);

	int sum = 0;

	for (auto i : list)
		sum += i.value;

	ASSERT(sum == 100);
}
