#ifndef _NATIVE_IO_ISTREAM_H_
#define _NATIVE_IO_ISTREAM_H_ 1

// External Dependencies
#include "../../core/include/exception.h"

namespace native
{
	namespace io
	{
		/**
			Interface for raw streaming of bytes between endpoints.
		 */
		class IStream
		{
		public:
			/** Virtual destructor. */
			virtual ~IStream() = default;

			/**
				Reads bytes from the stream into the supplied buffer/array.
				\param buffer The memory location to place the bytes received.
				\param maxBytes The maximum number of bytes to read.
				\return The number of bytes actually read.
			 */
			virtual size_t read(void* buffer, size_t maxBytes) = 0;

			/**
				Writes bytes of data to the stream.
				\param data The data to write to the stream.
				\param bytes The number of bytes to write.
				\return The number of bytes written.
			 */
			virtual size_t write(const void* data, size_t bytes) = 0;
		};

		/**
			Exception thrown an an IO error occurs.
		 */
		class IoException : public Exception
		{
		public:
			IoException(const char* message = "An IO error occurred") : Exception(message) {}
		};
	}
}

#endif // _NATIVE_IO_ISTREAM_H_

