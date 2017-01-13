#ifndef _NATIVE_TYPES_H_
#define _NATIVE_TYPES_H_ 1

// Standard Dependencies
#include <cstddef>
#include <utility>

// Module Dependencies
#include "platform.h"

namespace native
{
	// Integer Types
	typedef char      int8_t; 	///< A signed, 8-bit integer.
	typedef short     int16_t;	///< A signed 16-bit integer.
	typedef int       int32_t;	///< A signed 32-bit integer.
	typedef long long int64_t;	///< A signed 64-bit integer.
	typedef unsigned char      uint8_t; 	///< An unsigned, 8-bit integer.
	typedef unsigned short     uint16_t;	///< An unsigned 16-bit integer.
	typedef unsigned int       uint32_t;	///< An unsigned 32-bit integer.
	typedef unsigned long long uint64_t;	///< An unsigned 64-bit integer.

#if NATIVE_BIT_WIDTH == 64
	typedef int64_t  ptrint_t;	///< A pointer-sized integer.
	typedef uint64_t uptrint_t;	///< An unsigned, pointer-sized integer.
#elif NATIVE_BIT_WIDTH == 32
	typedef int32_t  ptrint_t; 	///< A pointer-sized integer.
	typedef uint32_t uptrint_t;	///< An unsigned, pointer-sized integer.
#else
# error Unable to define pointer-sized types.
#endif // NATIVE_ARCH_

	// Basic, Non-Structure Types
	typedef unsigned char byte_t;	///< A single byte of data.
	typedef void*         handle_t; ///< A platform-specific resource handle.
	typedef int32_t       coord_t;	///< A co-ordinate value, which can be positive or negative.
}

#endif // _NATIVE_TYPES_H_

