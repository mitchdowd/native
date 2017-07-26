// Module Dependencies
#include "../include/memorystream.h"

namespace native
{
	namespace io
	{
		MemoryStream::MemoryStream(size_t initialCapacity) : _array(initialCapacity), _length(0), _pos(0)
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

			Memory::copy(buffer, &_array[_pos], maxBytes);
			_pos += maxBytes;
			return maxBytes;
		}

		size_t MemoryStream::write(const void* data, size_t bytes)
		{
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
		}

		void MemoryStream::seek(size_t position)
		{
			if (position > _length)
				position = _length;

			_pos = position;
		}
	}
}

