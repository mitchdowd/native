// Testing Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

TEST(Convert_toInt)
{
	ASSERT(Convert::toInt(L"1234") == 1234);
}

TEST(Convert_toFloat)
{
	ASSERT(Convert::toFloat(L"1234.0") == 1234.0);
}
