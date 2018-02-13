// Standard Dependencies
#include <cstring>

// Module Dependencies
#include "../include/array.h"
#include "../include/exception.h"

namespace native
{
	ByteArray::ByteArray(const byte_t* data, size_t length) : Array<byte_t>(length)
	{
		if (data != nullptr)
		{
			set(0, data, length);

			// Null-terminate. Array is hard-coded to always allocate enough space.
			*((byte_t*) toArray() + length) = 0;
		}
	}

	ByteArray::ByteArray(size_t length) : Array<byte_t>(length)
	{
		if (length > 0)
		{
			// Null-terminate. Array is hard-coded to always allocate enough space.
			*((byte_t*) toArray() + length) = 0;
		}
	}

	ByteArray::ByteArray(const char* data, size_t length)
	{
		if (data != nullptr)
		{
			if (length == size_t(~0))
				length = std::strlen(data);

			setLength(length);
			set(0, (const byte_t*) data, length);

			// Null-terminate. Array is hard-coded to always allocate enough space.
			*((byte_t*) toArray() + length) = 0;
		}
	}

	ByteArray operator+(const ByteArray& lhs, const ByteArray& rhs)
	{
		if (lhs.getLength() == 0)
			return rhs;
		if (rhs.getLength() == 0)
			return lhs;

		ByteArray result(lhs.getLength() + rhs.getLength());
		result.set(0, lhs.toArray(), lhs.getLength());
		result.set(lhs.getLength(), rhs.toArray(), rhs.getLength());
		return result;
	}

	ByteArray operator+(const ByteArray& lhs, const char* rhs)
	{
		if (lhs.getLength() == 0)
			return rhs;
		if (rhs == nullptr)
			return lhs;

		size_t rhsLen = std::strlen(rhs);

		ByteArray result(lhs.getLength() + rhsLen);
		result.set(0, lhs.toArray(), lhs.getLength());
		result.set(lhs.getLength(), (const byte_t*) rhs, rhsLen);
		return result;
	}

	ByteArray operator+(const char* lhs, const ByteArray& rhs)
	{
		if (lhs == nullptr)
			return rhs;
		if (rhs.getLength() == 0)
			return lhs;

		size_t lhsLen = std::strlen(lhs);

		ByteArray result(lhsLen + rhs.getLength());
		result.set(0, (const byte_t*) lhs, lhsLen);
		result.set(lhsLen, rhs.toArray(), rhs.getLength());
		return result;
	}

	namespace internal
	{
		void raiseInvalidArgumentException()
		{
			throw InvalidArgumentException();
		}

		void raiseArrayIndexException()
		{
			throw ArrayIndexException();
		}

		size_t getCapacityForLength(size_t length) noexcept
		{
			size_t capacity = ++length;

			capacity |= capacity >> 1;
			capacity |= capacity >> 2;
			capacity |= capacity >> 4;
			capacity |= capacity >> 8;

			return capacity |= capacity >> 16;
		}
	}
}

