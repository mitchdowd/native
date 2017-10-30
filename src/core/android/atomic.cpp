// Module Dependencies
#include "../include/atomic.h"

namespace native
{
    int16_t Atomic::increment(volatile int16_t& value) noexcept
    {
        return __sync_add_and_fetch(&value, 1);
    }

    int32_t Atomic::increment(volatile int32_t& value) noexcept
    {
        return __sync_add_and_fetch(&value, 1);
    }

    int64_t Atomic::increment(volatile int64_t& value) noexcept
    {
        return __sync_add_and_fetch_4(&value, 1);
    }

    int16_t Atomic::decrement(volatile int16_t& value) noexcept
    {
        return __sync_sub_and_fetch(&value, 1);
    }

    int32_t Atomic::decrement(volatile int32_t& value) noexcept
    {
        return __sync_sub_and_fetch(&value, 1);
    }

    int64_t Atomic::decrement(volatile int64_t& value) noexcept
    {
        return __sync_sub_and_fetch_4(&value, 1);
    }

    int16_t Atomic::exchange(volatile int16_t& variable, int16_t value) noexcept
    {
        return __sync_lock_test_and_set(&variable, value);
    }

    int32_t Atomic::exchange(volatile int32_t& variable, int32_t value) noexcept
    {
        return __sync_lock_test_and_set(&variable, value);
    }

    void* Atomic::exchange(volatile void*& variable, void* value) noexcept
    {
        return __sync_lock_test_and_set((void**) &variable, value);
    }

    int64_t Atomic::exchange(volatile int64_t& variable, int64_t value) noexcept
    {
        return __sync_lock_test_and_set_4(&variable, value);
    }
	
	bool Atomic::exchange(volatile bool& variable, bool value) noexcept
	{
		return __sync_lock_test_and_set(&variable, value);
	}

    int16_t Atomic::compareExchange(volatile int16_t& variable, int16_t value, int16_t comparand) noexcept
    {
        return __sync_val_compare_and_swap(&variable, comparand, value);
    }

    int32_t Atomic::compareExchange(volatile int32_t& variable, int32_t value, int32_t comparand) noexcept
    {
        return __sync_val_compare_and_swap(&variable, comparand, value);
    }

    int64_t Atomic::compareExchange(volatile int64_t& variable, int64_t value, int64_t comparand) noexcept
    {
        return __sync_val_compare_and_swap_4(&variable, comparand, value);
    }

    void* Atomic::compareExchange(volatile void*& variable, void* value, void* comparand) noexcept
    {
        return __sync_val_compare_and_swap((void**) &variable, comparand, value);
    }
	
	bool Atomic::compareExchange(volatile bool& variable, bool value, bool comparand) noexcept
	{
		return __sync_val_compare_and_swap(&variable, comparand, value);
	}
}

