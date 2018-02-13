// System Dependencies
#include <Windows.h>
#include <intrin.h>

// Module Dependencies
#include "../include/atomic.h"

// Intrinsic Declarations
#pragma intrinsic(_InterlockedIncrement, _InterlockedDecrement, _InterlockedExchange, _InterlockedCompareExchange)

#if NATIVE_BIT_WIDTH == 64
// 64-bit Intrinsic Declarations
# pragma intrinsic(_InterlockedIncrement64, _InterlockedDecrement64, _InterlockedExchange64, _InterlockedCompareExchange64)
#else
// 64-bit intrinsics are only available on 64-bit processors.
# define _InterlockedIncrement64 InterlockedIncrement64
# define _InterlockedDecrement64 InterlockedDecrement64
# define _InterlockedExchange64  InterlockedExchange64
# define _InterlockedCompareExchange64 InterlockedCompareExchange64
#endif

// Safety Check
static_assert(sizeof(bool) == 1, "Unexpected size for 'bool' type.");

namespace native
{
	int16_t Atomic::increment(volatile int16_t& value) noexcept
	{
		return _InterlockedIncrement16(&value);
	}

	int32_t Atomic::increment(volatile int32_t& value) noexcept
	{
		return _InterlockedIncrement((volatile long*) &value);
	}

	int64_t Atomic::increment(volatile int64_t& value) noexcept
	{
		return _InterlockedIncrement64(&value);
	}

	int16_t Atomic::decrement(volatile int16_t& value) noexcept
	{
		return _InterlockedDecrement16(&value);
	}

	int32_t Atomic::decrement(volatile int32_t& value) noexcept
	{
		return _InterlockedDecrement((volatile long*) &value);
	}

	int64_t Atomic::decrement(volatile int64_t& value) noexcept
	{
		return _InterlockedDecrement64(&value);
	}

	int16_t Atomic::exchange(volatile int16_t& variable, int16_t value) noexcept
	{
		return _InterlockedExchange16(&variable, value);
	}

	int32_t Atomic::exchange(volatile int32_t& variable, int32_t value) noexcept
	{
		return _InterlockedExchange((volatile long*) &variable, value);
	}

	int64_t Atomic::exchange(volatile int64_t& variable, int64_t value) noexcept
	{
		return _InterlockedExchange64(&variable, value);
	}

#if NATIVE_BIT_WIDTH == 64
	void* Atomic::exchange(volatile void*& variable, void* value) noexcept
	{
		return (void*) _InterlockedExchange64((volatile int64_t*) &variable, (int64_t) value);
	}
#else
	void* Atomic::exchange(volatile void*& variable, void* value) noexcept
	{
		return (void*) _InterlockedExchange((volatile long*) &variable, (long) value);
	}
#endif

	bool Atomic::exchange(volatile bool& variable, bool value) noexcept
	{
		return (bool) _InterlockedExchange8((volatile char*) &variable, (char) value);
	}

	int16_t Atomic::compareExchange(volatile int16_t& variable, int16_t value, int16_t comparand) noexcept
	{
		return _InterlockedCompareExchange16(&variable, value, comparand);
	}

	int32_t Atomic::compareExchange(volatile int32_t& variable, int32_t value, int32_t comparand) noexcept
	{
		return _InterlockedCompareExchange((volatile long*) &variable, value, comparand);
	}

	int64_t Atomic::compareExchange(volatile int64_t& variable, int64_t value, int64_t comparand) noexcept
	{
		return _InterlockedCompareExchange64(&variable, value, comparand);
	}

#if NATIVE_BIT_WIDTH == 64
	void* Atomic::compareExchange(volatile void*& variable, void* value, void* comparand) noexcept
	{
		return (void*) _InterlockedCompareExchange64((volatile int64_t*) &variable, (int64_t) value, (int64_t) comparand);
	}
#else
	void* Atomic::compareExchange(volatile void*& variable, void* value, void* comparand) noexcept
	{
		return (void*) _InterlockedCompareExchange((volatile long*) &variable, (long) value, (long) comparand);
	}
#endif

	bool Atomic::compareExchange(volatile bool& variable, bool value, bool comparand) noexcept
	{
		return (bool) _InterlockedCompareExchange8((volatile char*) &variable, (char) value, (char) comparand);
	}
}
