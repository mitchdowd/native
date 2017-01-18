// External Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

TEST(Math_min)
{
	ASSERT(Math::min(10, 20) == 10);
}

TEST(Math_max)
{
	ASSERT(Math::max(10, 20) == 20);
}

TEST(Math_abs)
{
	ASSERT(Math::abs(-1) == 1);
	ASSERT(Math::abs(1) == 1);
}

TEST(Math_squareRoot)
{
	ASSERT(Math::squareRoot(100) == 10);
	ASSERT(Math::squareRoot(99) == 9);		// Integer truncation.
}

TEST(Math_randomIsWithinBounds)
{
	for (int i = 0; i < 10; i++)
	{
		int x = Math::random(10, 100);
		ASSERT(x >= 10 && x < 100);
	}
}
