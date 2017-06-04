#ifndef _NATIVE_IO_FILE_H_
#define _NATIVE_IO_FILE_H_ 1

// Local Dependencies
#include "istream.h"

namespace native
{
	namespace io
	{
		/**
			An endpoing for reading and writing on the file system.
		 */
		class File : public IStream
		{
		public:
			/**
				Reads up to `maxBytes` from the file into the buffer. A partial
				read indicates the end of the file.
				\param maxBytes The maximum bytes to read.
				\param buffer The memory location to store the read data.
				\return The number of bytes read.
			 */
			virtual size_t read(void* buffer, size_t maxBytes) override;

			/**
				Writes data to the file. If all bytes cannot be written, an
				Exception is thrown.
				\param data The data to write.
				\param bytes The number of bytes to write.
				\return The number of bytes written.
			 */
			virtual size_t write(const void* data, size_t bytes) override;

		};
	}
}

#endif // _NATIVE_IO_FILE_H_

