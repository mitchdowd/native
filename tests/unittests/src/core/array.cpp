// Module Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

static int constructors = 0;
static int destructors = 0;
static int assignments = 0;

struct Counter
{
	Counter() { ++constructors; }
	~Counter() { ++destructors; }
	Counter& operator=(const Counter&) { ++assignments; return *this; }
};

TEST(Array_defaultConstructorHasZeroLength)
{
	Array<int> a;

	ASSERT(a.getLength() == 0);
}

TEST(Array_initializerListConstructor)
{
	Array<char> a = { 'a', 'b', 'c', '\0' };

	ASSERT(a.getLength() == 4);
	ASSERT_EQUAL(a.toArray(), "abc");
}

TEST(Array_lengthConstructorSetsLength)
{
	Array<int> a(100);

	ASSERT(a.getLength() == 100);
}

TEST(Array_nonTrivialLengthConstructor)
{
	constructors = destructors = assignments = 0;

	Array<Counter> array(10);

	ASSERT(array.getLength() == 10);
	ASSERT(constructors == 10);
}

TEST(Array_setLengthSetsArrayLength)
{
	Array<int> a;

	a.setLength(100);

	ASSERT(a.getLength() == 100);
}

TEST(Array_copyConstructorSharesData)
{
	Array<char> a = { 'a', 'b', 'c' };
	Array<char> b = a;

	ASSERT(a.toArray() == b.toArray());
}

TEST(Array_moveConstructorNullsSource)
{
	Array<char> a = { 'a', 'b', 'c', '\0' };
	Array<char> b = std::move(a);

	ASSERT(a.getLength() == 0);
	ASSERT_EQUAL(b.toArray(), "abc");
}

TEST(Array_setLengthPreservesData)
{
	Array<char> a = { 'a', 'b', 'c', 'd', 'e' };

	a.setLength(2);

	ASSERT(a[0] == 'a');
	ASSERT(a[1] == 'b');
}

TEST(Array_iterate)
{
	Array<int> array = { 1, 2, 3, 4, 5 };

	int sum = 0;

	for (int i : array)
		sum += i;

	ASSERT(sum == 15);
}

TEST(Array_atIndex)
{
	Array<char> array = { 'a', 'b', 'c' };

	ASSERT(array.atIndex(2) == 'c');
}

TEST(Array_clear)
{
	Array<char> array = { 'a', 'b', 'c', };

	array.clear();

	ASSERT(array.getLength() == 0);
}

TEST(Array_detatchCreatesDeepCopy)
{
	Array<char> a = { 'a', 'b', 'c', '\0' };
	Array<char> b = a;

	b.detatch();

	ASSERT(a.toArray() != b.toArray());
	ASSERT_EQUAL(a.toArray(), b.toArray());
}

TEST(Array_ArrayIndexException)
{
	Array<char> array;

	ASSERT_THROWS(array[10], ArrayIndexException);
	ASSERT_THROWS(array.set(0, 'x'), ArrayIndexException);
}

TEST(Array_setValueDoesNotDropCounts)
{
	constructors = destructors = 0;

	// Force the scope.
	{
		Array<Counter> blah(10);
		Counter c, d, e;

		blah.set(0, c);
		blah.set(0, d);
		blah.set(1, e);
	}

	ASSERT(constructors == 13);
	ASSERT(assignments == 3);
	ASSERT(constructors == destructors);
}

TEST(Array_setRange)
{
	Array<char> array(10);

	array.set(0, "testing", 7);
	array.set(4, "ting", 4);

	ASSERT_EQUAL(array.toArray(), "testting");
}

TEST(Array_setMultiple)
{
	Array<char> array(10);

	array.set(0, 'x', 3);

	ASSERT_EQUAL(array.toArray(), "xxx");
}

TEST(ByteArray_asciiInitialiser)
{
	ByteArray array = "I am an array";

	ASSERT_EQUAL(array, "I am an array");
}

TEST(ByteArray_concatenation)
{
	ByteArray lhs = "test";
	ByteArray rhs = "ing";

	ASSERT_EQUAL(lhs + rhs, "testing");
	ASSERT_EQUAL(lhs + "ing", "testing");
	ASSERT_EQUAL("test" + rhs, "testing");
}
