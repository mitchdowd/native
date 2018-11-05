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
				Creates a MemoryStream initialised with the given data. The data
				should remain valid for the lifetime of the MemoryStream. The
				MemoryStream may not write to this data array.
				\param data The array of byte data.
				\param length The number of bytes in the array.
			 */
			MemoryStream(const void* data, size_t length);

			/**
				Creates a MemoryStream initialised with the given data. The data
				should remain valid for the lifetime of the MemoryStream. The
				MemoryStream may not write to this data array.
				\param array A ByteArray to initialise the stream with.
			 */
			MemoryStream(const ByteArray& array);

			/**
				Creates a MemoryStream with the specified initial capacity. The
				capacity will still expand as needed during a write() operation.
				\param initialCapacity The initial capacity, in bytes.
			 */
			MemoryStream(size_t initialCapacity = 0);

			/** Destroys the MemoryStream and its contents. */
			~MemoryStream() = default;

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
				will also update the seek position of the stream, and overwrite
				the data at the current seek position (if the seek position is
				not at the end of the stream).
				\param data The data to write to the stream.
				\param bytes The number of bytes to write.
				\return The number of bytes written.
			 */
			virtual size_t write(const void* data, size_t bytes) override;

			/** Empties the MemoryStream buffer. */
			void clear();

			/**
				Changes the current read/write position to the given index in the
				stream's internal buffer. Attempting to navigate further than the
				length of the buffer will simply navigate to the end of the buffer.
				\param position The seek position to set.
			 */
			void seek(size_t position);

			/**
				Gets the current capacity (in bytes) of this MemoryStream.
				\return The number of usable allocated bytes of memory.
			 */
			size_t getCapacity() const noexcept { return _array.getLength(); }

			/**
				Gets the number of buffered bytes in the MemoryStream.
				\return The number of bytes available.
			 */
			size_t getLength() const noexcept { return _length; }

			/**
				Returns the current seek position in the stream buffer.
				\return The current seek position.
			 */
			size_t getPosition() const noexcept { return _pos; }

			/**
				Gets the array which serves as the buffer, storing the stream's
				contents.
				\return The buffer containing the stream's contents.
			 */
			ByteArray getBuffer() const { return _array; }

		private:
			// Instance Variables
			ByteArray _array;
			size_t _length;
			size_t _pos;
			const void* _data;
		};
	}
}

#endif // _NATIVE_IO_MEMORY_STREAM_H_

