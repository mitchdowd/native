// External Dependencies
#include <test.h>
#include <core.h>

using namespace native;

TEST(Types_PrimitiveTypeSizesAreCorrect)
{
	ASSERT(sizeof(native::int8_t) == 1);
	ASSERT(sizeof(native::int16_t) == 2);
	ASSERT(sizeof(native::int32_t) == 4);
	ASSERT(sizeof(native::int64_t) == 8);

	ASSERT(sizeof(native::uint8_t) == 1);
	ASSERT(sizeof(native::uint16_t) == 2);
	ASSERT(sizeof(native::uint32_t) == 4);
	ASSERT(sizeof(native::uint64_t) == 8);

	ASSERT(sizeof(native::ptrint_t) == sizeof(void*));
	ASSERT(sizeof(native::uptrint_t) == sizeof(void*));

	ASSERT(sizeof(native::byte_t) == 1);
}
