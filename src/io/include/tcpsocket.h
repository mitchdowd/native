#ifndef _NATIVE_IO_TCP_SOCKET_H_
#define _NATIVE_IO_TCP_SOCKET_H_ 1

// Local Dependencies
#include "istream.h"
#include "socket.h"

namespace native
{
	namespace io
	{
		/**
			An endpoint for reading and writing over a TCP/IP connection.
		 */
		class TcpSocket : public Socket, public IStream
		{
		public:
			/** 
				Constructor.
				\param version IP version.
			 */
			TcpSocket(IpVersion version = IpVersion::Any);

			/**
				Reads available data from the socket. Partial reads are allowed.
				\param buffer Location to store retrieved data.
				\param maxBytes The maximum number of bytes to read.
				\return The number of bytes read.
			 */
			virtual size_t read(void* buffer, size_t maxBytes) override;

			/**
				Writes data to the socket. Partial writes are allowed.
				\param data The data to write.
				\param bytes The number of bytes to write.
				\return The number of bytes written.
			 */
			virtual size_t write(const void* data, size_t bytes) override;
		};
	}
}

#endif // _NATIVE_IO_TCP_SOCKET_H_

