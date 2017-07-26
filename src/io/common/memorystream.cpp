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
			throw NotImplementedException();
		}

		size_t MemoryStream::write(const void* data, size_t bytes)
		{
			throw NotImplementedException();
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

