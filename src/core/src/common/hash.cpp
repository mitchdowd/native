// Module Dependencies
#include "../../include/exception.h"
#include "../../include/hash.h"

// Local Constants
#define FNV_1A32_OFFSET      (2166136261UL)
#define FNV_1A32_MAGIC_PRIME (16777619UL)
#define FNV_1A64_OFFSET      (14695981039346656037UL)
#define FNV_1A64_MAGIC_PRIME (1099511628211UL)

namespace native
{
	uint64_t hash64(const void* data, size_t size)
	{
		uint64_t value = FNV_1A64_OFFSET;
		byte_t* pos = (byte_t*) data;
		byte_t* end = pos + size;

		if (data == nullptr && size != 0)
			throw InvalidArgumentException();

		while (pos < end) {
			value ^= uint64_t(*pos++);
			value *= FNV_1A64_MAGIC_PRIME;
		}

		return value;
	}

	uint32_t hash32(const void* data, size_t size)
	{
		uint32_t value = FNV_1A32_OFFSET;
		byte_t* pos = (byte_t*) data;
		byte_t* end = pos + size;

		if (data == nullptr && size != 0)
			throw InvalidArgumentException();

		while (pos < end) {
			value ^= uint32_t(*pos++);
			value *= FNV_1A32_MAGIC_PRIME;
		}

		return value;
	}
}

