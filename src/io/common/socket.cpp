// External Dependencies
#include "../../core/include/spinlock.h"

// Local Dependencies
#include "../include/socket.h"

#ifdef NATIVE_PLATFORM_WIN32

// System Dependencies
# include <WinSock2.h>

// External Libraries
# pragma comment(lib, "ws2_32.lib")

namespace native
{
	namespace io
	{
		void registerSocketApi()
		{
			static SpinLock lock;
			static bool registered = false;

			if (!registered) {
				lock.lock();

				if (!registered) {
					WSADATA wsaData;

					// Register the winsock library.
					::WSAStartup(MAKEWORD(2, 2), &wsaData);
					registered = true;

					// TODO: Where is this released?
				}

				lock.release();
			}
		}
	}
}

#else

// System Dependencies
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

// Type Definitions
typedef int SOCKET;

// Constants
#define INVALID_SOCKET SOCKET(-1)

// Function Aliases
inline int closesocket(SOCKET s) { return ::close(s); }

namespace native
{
	namespace io
	{
		inline void registerSocketApi() {}
	}
}

#endif // NATIVE_PLATFORM_WIN32

namespace native
{
	namespace io
	{
		Socket::Socket(IpProtocol protocol, IpVersion version)
		{
			int af = version == IpVersion::IPv6 ? AF_INET6 : AF_INET;
			int socktype;
			int proto;

			switch (protocol)
			{
			case IpProtocol::Tcp:
				socktype = SOCK_STREAM;
				proto = IPPROTO_TCP;
				break;

			case IpProtocol::Udp:
				socktype = SOCK_DGRAM;
				proto = IPPROTO_UDP;
				break;

			default:
				throw InvalidArgumentException("Invalid IP protocol");
			}

			registerSocketApi();

			// Allocate the system resources.
			_handle = (handle_t) (ptrint_t) ::socket(af, socktype, proto);

			// Error checking.
			if (SOCKET(ptrint_t(_handle)) == INVALID_SOCKET)
				throw SocketException("Failed to create socket");
		}

		void Socket::close() noexcept
		{
			if (SOCKET(ptrint_t(_handle)) != INVALID_SOCKET)
			{
				::closesocket(SOCKET(ptrint_t(_handle)));
				_handle = handle_t(INVALID_SOCKET);
			}
		}

		bool Socket::isClosed() const noexcept
		{
			return _handle == handle_t(INVALID_SOCKET);
		}
	}
}

