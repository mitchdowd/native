// Standard Dependencies
#include <cstdlib>
#include <cstring>

// Module Dependencies
#include "../include/memory.h"

namespace native
{
	void* Memory::allocate(size_t bytes)
	{
		return std::malloc(bytes);
	}

	void* Memory::allocateAndZero(size_t bytes)
	{
		return std::calloc(1, bytes);
	}

	void Memory::free(void* memory) noexcept
	{
		std::free(memory);
	}

	void* Memory::copy(void* dest, const void* src, size_t bytes)
	{
		return std::memcpy(dest, src, bytes);
	}

	void* Memory::move(void* dest, const void* src, size_t bytes)
	{
		return std::memmove(dest, src, bytes);
	}

	void Memory::zero(void* memory, size_t bytes)
	{
		std::memset(memory, 0, bytes);
	}
}

