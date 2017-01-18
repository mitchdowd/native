// Module Dependencies
#include <test.h>
#include <core.h>

using namespace native;

TEST(Types_PrimitiveTypeSizesAreCorrect)
{
	ASSERT(sizeof(int8_t) == 1);
	ASSERT(sizeof(int16_t) == 2);
	ASSERT(sizeof(int32_t) == 4);
	ASSERT(sizeof(int64_t) == 8);

	ASSERT(sizeof(uint8_t) == 1);
	ASSERT(sizeof(uint16_t) == 2);
	ASSERT(sizeof(uint32_t) == 4);
	ASSERT(sizeof(uint64_t) == 8);

	ASSERT(sizeof(ptrint_t) == sizeof(void*));
	ASSERT(sizeof(uptrint_t) == sizeof(void*));

	ASSERT(sizeof(byte_t) == 1);
}
