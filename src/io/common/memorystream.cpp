// Module Dependencies
#include "../include/memorystream.h"

namespace native
{
	namespace io
	{
		MemoryStream::MemoryStream(const void* data, size_t length) : _length(length), _pos(0), _data(data)
		{
		}

		MemoryStream::MemoryStream(const ByteArray& array) : _array(array), _length(array.getLength()), _pos(0)
		{
			_data = _array.toArray();
		}

		MemoryStream::MemoryStream(size_t initialCapacity) : _array(initialCapacity), _length(0), _pos(0), _data(nullptr)
		{
		}

		MemoryStream::~MemoryStream()
		{
		}

		size_t MemoryStream::read(void* buffer, size_t maxBytes)
		{
			if (_pos >= _length)
				return 0;

			if (_length - _pos < maxBytes)
				maxBytes = _length - _pos;

			// May be reading from either _data or _array.
			const byte_t* data = _data ? (const byte_t*) _data : _array.toArray();
			Memory::copy(buffer, &data[_pos], maxBytes);
			_pos += maxBytes;
			return maxBytes;
		}

		size_t MemoryStream::write(const void* data, size_t bytes)
		{
			if (_data != nullptr)
				throw IoException("Cannot write to MemoryStream for existing byte array.");

			// Ensure we have capacity to write to.
			if (getCapacity() < _pos + bytes)
				_array.setLength(internal::getCapacityForLength(_pos + bytes));

			_array.set(_pos, (const byte_t*) data, bytes);
			_pos += bytes;

			if (_pos > _length)
				_length = _pos;

			return bytes;
		}

		void MemoryStream::clear()
		{
			_pos = _length = 0;
			_array.clear();
			_data = nullptr;
		}

		void MemoryStream::seek(size_t position)
		{
			if (position > _length)
				position = _length;

			_pos = position;
		}
	}
}

