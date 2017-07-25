// Module Dependencies
#include "../include/memorystream.h"

namespace native
{
	namespace io
	{
		MemoryStream::MemoryStream(size_t initialCapacity) : _capacity(initialCapacity)
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

		void MemoryStream::seek(size_t position)
		{
			throw NotImplementedException();
		}
	}
}

