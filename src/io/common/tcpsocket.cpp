// Local Dependencies
#include "../include/tcpsocket.h"

#ifdef NATIVE_PLATFORM_WIN32

// System Dependencies
#include <winsock2.h>

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
#include <sys/types.h>
#include <sys/socket.h>

// Type Definitions
typedef int SOCKET;

// Constants
#define INVALID_SOCKET SOCKET(-1)
#define SOCKET_ERROR (-1)

// Function Aliases
inline int closesocket(SOCKET s) { return ::close(s); }

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
			throw NotImplementedException();
		}

		size_t TcpSocket::write(const void* data, size_t bytes)
		{
			if (bytes > MAXINT)
				bytes = MAXINT;

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

