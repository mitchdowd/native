#ifndef _NATIVE_HASH_H_
#define _NATIVE_HASH_H_ 1

// Module Dependencies
#include "types.h"

namespace native
{
	/**
		Hashes a chunk of bytes to get a 32-bit hash code using the FNV-1a algorithm.
		\param data The data to hash.
		\param size The number of bytes to hash.
		\return The calculated hash code.
	*/
	uint32_t hash32(const void* data, size_t size);

	/**
		Hashes a chunk of bytes to get a 32-bit hash code using the FNV-1a algorithm.
		\param data The data to hash.
		\param size The number of bytes to hash.
		\return The calculated hash code.
	*/
	uint64_t hash64(const void* data, size_t size);

	/**
		Hashes an integer to try to even the spread of the hash result.
		\param i The integer to hash.
		\return The calculated hash code.
	 */
	uint32_t hash32(uint64_t i);
	uint64_t hash64(uint64_t i);

#if NATIVE_BIT_WIDTH == 64
	inline uptrint_t hash(const void* data, size_t size) { return hash64(data, size); }
	inline uptrint_t hash(uint64_t i) { return hash64(i); }
#else
	inline uptrint_t hash(const void* data, size_t size) { return hash32(data, size); }
	inline uptrint_t hash(uint64_t i) { return hash32(i); }
#endif // NATIVE_ARCH_X64

	/**
		Hashes any basic value to get a hash code. Class values with more complex
		hashing should overload their own hash functions.
		\param value The value to get a hash code for.
		\return The hash code.
	*/
	template <typename type_t>
	inline uptrint_t hash(const type_t& value)
	{
		return hash(&value, sizeof(type_t));
	}

	/**
		Hashes pointer values.
		\param value The pointer to hash.
		\return The hash code.
	 */
	template <typename type_t>
	inline uptrint_t hash(const type_t* value)
	{
		return hash(uint64_t(value));
	}
}

#endif // _NATIVE_HASH_H_

