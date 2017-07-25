#ifndef _NATIVE_IO_MEMORY_STREAM_H_
#define _NATIVE_IO_MEMORY_STREAM_H_ 1

// Module Dependencies
#include "istream.h"

namespace native
{
	namespace io
	{
		/**
			MemoryStream provides in-memory IO operations on a simple byte array.
		 */
		class MemoryStream : public IStream
		{
		public:
			/**
				Creates a MemoryStream with the specified initial capacity. The
				capacity will still expand as needed during a write() operation.
				\param initialCapacity The initial capacity, in bytes.
			 */
			MemoryStream(size_t initialCapacity = 0);

			/** Destroys the MemoryStream and its contents. */
			~MemoryStream();

			/**
				Reads bytes of data from the current position in the stream. This
				will update the current seek position in the stream.
				\param buffer Place to store the retrieved bytes.
				\param maxBytes The maximum number of bytes to read.
				\return The number of bytes read.
			 */
			virtual size_t read(void* buffer, size_t maxBytes) override;

			/**
				Writes an array of bytes to the current position in the stream.
				This will increase the MemoryStream's capacity if required. It
				will also update the seek position of the stream.
				\param data The data to write to the stream.
				\param bytes The number of bytes to write.
				\return The number of bytes written.
			 */
			virtual size_t write(const void* data, size_t bytes) override;

			/**
				Changes the current read/write position to the given index in the
				stream's internal buffer. Produces an ArrayIndexException if the
				seek position is out of bounds.
				\param position The seek position to set.
			 */
			void seek(size_t position);

			/**
				Gets the current capacity (in bytes) of this MemoryStream.
				\return The number of usable allocated bytes of memory.
			 */
			size_t getCapacity() const noexcept { return _capacity; }

		private:
			// Instance Variables
			size_t _capacity;
		};
	}
}

#endif // _NATIVE_IO_MEMORY_STREAM_H_

