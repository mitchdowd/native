// Testing Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

TEST(hash_sameResultOnSameData)
{
	char a[] = "This is something to hash";
	char b[] = "This is something to hash";

	ASSERT(hash(a, sizeof(a)) == hash(b, sizeof(b)));
}

