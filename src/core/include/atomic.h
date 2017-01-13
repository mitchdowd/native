#ifndef _NATIVE_ATOMIC_H_
#define _NATIVE_ATOMIC_H_ 1

// Module Dependencies
#include "types.h"

namespace native
{
	/**
		Atomic encapsulates a set of atomic operations on basic values. Atomic
		operations are simple, uninteruptable operations which will not have a
		Thread context switch occur midway through the operation.
	
		Regular arithmetic operations such as incrementing, adding, subtracting,
		etc, can often take multiple processor instructions to complete. This
		means that a context switch to another executing Thread could occur in
		the middle of such an operation. Using an Atomic function instead
		ensures such a switch does not happen, allowing potentially Thread-safe
		constructs to be built.
	 */
	class Atomic
	{
		// Prevent Instantiation
		Atomic() = delete;

	public:
		/**
			Atomically increments a value.
			\param value The value to increment.
			\return The incremented value.
		 */
		static int16_t increment(volatile int16_t& value) noexcept;
		static int32_t increment(volatile int32_t& value) noexcept;
		static int64_t increment(volatile int64_t& value) noexcept;

		/**
			Atomically decrements a value.
			\param value The value to decrement.
			\return The decremented value.
		 */
		static int16_t decrement(volatile int16_t& value) noexcept;
		static int32_t decrement(volatile int32_t& value) noexcept;
		static int64_t decrement(volatile int64_t& value) noexcept;

		/**
			Performs an atomic swap operation on two values.
			\param variable The location to swap a value into.
			\param value The value to store in `variable`
			\return The previous value from `variable`.
		 */
		static int16_t exchange(volatile int16_t& variable, int16_t value) noexcept;
		static int32_t exchange(volatile int32_t& variable, int32_t value) noexcept;
		static int64_t exchange(volatile int64_t& variable, int64_t value) noexcept;
		static void* exchange(volatile void*& variable, void* value) noexcept;

		/**
			Performs an atomic swap operation on two values, pending the result
			of a comparison. If the `comparand` is equal to the value currently
			in `variable`, the values are swapped. Otherwise there is no
			change.
			\param variable The location to swap a value into.
			\param value The value to store in `variable`
			\param comparand The value to compare with the item in `variable`.
			\return The previous value from `variable`.
		 */
		static int16_t compareExchange(volatile int16_t& variable, int16_t value, int16_t comparand) noexcept;
		static int32_t compareExchange(volatile int32_t& variable, int32_t value, int32_t comparand) noexcept;
		static int64_t compareExchange(volatile int64_t& variable, int64_t value, int64_t comparand) noexcept;
		static void* compareExchange(volatile void*& variable, void* value, void* comparand) noexcept;
	};
}

#endif // _NATIVE_ATOMIC_H_

