#ifndef _NATIVE_MEMORY_H_
#define _NATIVE_MEMORY_H_ 1

// Module Dependencies
#include "types.h"

namespace native
{
	/**
		Provides memory management operations for allocating and freeing
		blocks of memory on the heap.
	 */
	class Memory
	{
	public:
		// Prevent Creation
		Memory() = delete;

		/**
			Allocates a block of memory of at least the given number of bytes.
			That memory must later be used by calling Memory::free().
			\param bytes The minimum number of bytes to allocate.
			\return The allocated memory.
		 */
		static void* allocate(size_t bytes);

		/**
			Allocates a block of memory of at least the given number of bytes.
			That memory must later be used by calling Memory::free(). All
			memory allocated is zero-initialised for safety.
			\param bytes The minimum number of bytes to allocate.
			\return The allocated memory.
		 */
		static void* allocateAndZero(size_t bytes);

		/**
			Frees the given block of memory which was previously allocated 
			using Memory::allocate().
			\param memory The memory block to free.
		 */
		static void free(void* memory) noexcept;

		/**
			Copies an array of bytes from `src` to `dest`. The destination
			buffer must have at least the supplied bytes of space. The source
			and destination arrays should not overlap. If they do, use `move`
			instead.
			\param dest The place to copy the data to.
			\param src The data to copy.
			\param bytes The number of bytes to copy.
			\return The destination location (`dest`).
		*/
		static void* copy(void* dest, const void* src, size_t bytes);

		/**
			Copies an array of bytes from `src` to `dest`. The destination
			buffer must have at least the supplied bytes of space. This is only
			different to the `copy` function in that the source and destination
			can overlap when calling `move`, but cannot when calling `copy`.
			\param dest The place to copy the data to.
			\param src The data to copy.
			\param bytes The number of bytes to copy.
			\return The destination location (`dest`).
		*/
		static void* move(void* dest, const void* src, size_t bytes);

		/**
			Initialises the given memory block to zeroes.
			\param memory The memory to initialise.
			\param bytes The number of bytes to set.
		 */
		static void zero(void* memory, size_t bytes);
	};
}

#endif // _NATIVE_MEMORY_H_

