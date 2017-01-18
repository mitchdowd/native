// Testing Dependencies
#include <test.h>
#include <core.h>

// Namespace Usage
using namespace native;

TEST(Atomic_increment)
{
	volatile int16_t i16 = 0;
	volatile int32_t i32 = 0;
	volatile int64_t i64 = 0;

	ASSERT(Atomic::increment(i16) == 1);
	ASSERT(Atomic::increment(i32) == 1);
	ASSERT(Atomic::increment(i64) == 1);
}

class Foobar
{
	char bytes[10000];
};

TEST(Atomic_decrement)
{
	auto x = new Foobar();

	volatile int16_t i16 = 1;
	volatile int32_t i32 = 1;
	volatile int64_t i64 = 1;

	ASSERT(Atomic::decrement(i16) == 0);
	ASSERT(Atomic::decrement(i32) == 0);
	ASSERT(Atomic::decrement(i64) == 0);
}

TEST(Atomic_exchange)
{
	volatile int16_t i16 = 1;
	volatile int32_t i32 = 1;
	volatile int64_t i64 = 1;
	volatile void* ptr = &i64;

	ASSERT(Atomic::exchange(i16, 0) == 1);
	ASSERT(Atomic::exchange(i32, 0) == 1);
	ASSERT(Atomic::exchange(i64, 0) == 1);
	ASSERT(Atomic::exchange(ptr, nullptr) == &i64);

	ASSERT(i16 == 0);
	ASSERT(i32 == 0);
	ASSERT(i64 == 0);
	ASSERT(ptr == nullptr);
}

TEST(Atomic_compareExchange)
{
	int one, two, three;

	volatile int16_t i16 = 1;
	volatile int32_t i32 = 1;
	volatile int64_t i64 = 1;
	volatile void* ptr = &one;

	// These should perform no operation, as comparison fails.
	Atomic::compareExchange(i16, 2, 3);
	Atomic::compareExchange(i32, 2, 3);
	Atomic::compareExchange(i64, 2, 3);
	Atomic::compareExchange(ptr, &two, &three);

	// These should update the value.
	ASSERT(Atomic::compareExchange(i16, 0, 1) == 1);
	ASSERT(Atomic::compareExchange(i32, 0, 1) == 1);
	ASSERT(Atomic::compareExchange(i64, 0, 1) == 1);
	ASSERT(Atomic::compareExchange(ptr, nullptr, &one) == &one);

	ASSERT(i16 == 0);
	ASSERT(i32 == 0);
	ASSERT(i64 == 0);
	ASSERT(ptr == nullptr);
}
