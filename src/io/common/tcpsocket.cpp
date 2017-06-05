// System Dependencies
#include <climits>

// Local Dependencies
#include "../include/tcpsocket.h"

#ifdef NATIVE_PLATFORM_WIN32

// System Dependencies
#include <winsock2.h>

#undef EWOULDBLOCK
#define EWOULDBLOCK WSAEWOULDBLOCK

namespace native
{
	namespace io
	{
		void registerSocketApi();

		inline int lastError() { return ::WSAGetLastError(); }
	}
}

#else

// System Dependencies
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

// Type Definitions
typedef int SOCKET;

// Constants
#define INVALID_SOCKET SOCKET(-1)
#define SOCKET_ERROR (-1)

namespace native
{
	namespace io
	{
		inline void registerSocketApi() {}

		inline int lastError() { return errno; }
	}
}

#endif // NATIVE_PLATFORM_WIN32

namespace native
{
	namespace io
	{
		TcpSocket::TcpSocket(IpVersion version) : Socket(IpProtocol::Tcp, version)
		{
		}

		size_t TcpSocket::read(void* buffer, size_t maxBytes)
		{
            if (maxBytes > INT_MAX)
                maxBytes = INT_MAX;

            // Perform the read operation.
            int result = ::recv(SOCKET(getHandle()), (char*) buffer, int(maxBytes), 0);

            // Error checking.
            if (result == SOCKET_ERROR)
            {
                if (lastError() == EWOULDBLOCK)
                    return 0;

                throw SocketException("Error reading from TcpSocket");
            }
            else if (result == 0)
            {
                // Socket was closed on the remote host.
                close();
                return 0;
            }

            return result;
		}

		size_t TcpSocket::write(const void* data, size_t bytes)
		{
			if (bytes > INT_MAX)
				bytes = INT_MAX;

			// Perform the write operation.
			int result = ::send(SOCKET(getHandle()), (const char*) data, int(bytes), 0);

			if (result == SOCKET_ERROR) 
			{
				if (lastError() == EWOULDBLOCK)
					return 0;

				throw SocketException("Error writing to TcpSocket");
			}

			return result;
		}
	}
}

