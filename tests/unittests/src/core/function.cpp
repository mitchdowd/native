// Testing Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

struct FunctionHelper
{
	FunctionHelper(int value) : _value(value) {}

	static int staticFunc(int x) { return x + 1; }
	int memberFunc() const { return _value + 1; }

	int _value;
};

TEST(Function_lambda)
{
	int value = 1;

	Function<int, int> plusOne = [](int x) { return x + 1; };

	ASSERT(plusOne(value) == value + 1);
}

TEST(Function_static)
{
	int value = 1;

	Function<int, int> plusOne = &FunctionHelper::staticFunc;

	ASSERT(plusOne(value) == value + 1);
}

TEST(Function_member)
{
	int value = 1;
	FunctionHelper helper(value);

	Function<int> plusOne(helper, &FunctionHelper::memberFunc);

	ASSERT(plusOne() == value + 1);
}\