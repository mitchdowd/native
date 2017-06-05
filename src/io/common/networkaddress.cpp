// Module Dependencies
#include "../include/networkaddress.h"
#include "../include/socket.h"

#ifdef NATIVE_PLATFORM_WIN32
// System Dependencies
#include <winsock2.h>
#include <ws2tcpip.h>

namespace native
{
    namespace io
    {
        void registerSocketApi();
    }
}

#else

// System Dependencies
#include <arpa/inet.h>
#include <netdb.h>

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
        NetworkAddress::NetworkAddress(const String& ip, port_t port, IpVersion version) : _port(port), _version(version)
        {
            if (version == IpVersion::Any)
            {
                if (isValidIp(ip, IpVersion::IPv4))
                    _version = IpVersion::IPv4;
                else if (isValidIp(ip, IpVersion::IPv6))
                    _version = IpVersion::IPv6;
                else
                    throw InvalidArgumentException("Invalid IP address");
            }
            else if (!isValidIp(ip, version))
                throw InvalidArgumentException("Invalid IP address");

            // Copy in the IP address.
            Memory::copy(_ip, ip.toArray(), ip.getLength() + 1);
        }

        List<NetworkAddress> NetworkAddress::byHost(const String& hostName, IpVersion version)
        {
            List<NetworkAddress> list;
            addrinfo *result, hints = { 0 };

            registerSocketApi();

            /* Populate the hints structure. */
            if (version == IpVersion::Any)
                hints.ai_family = AF_UNSPEC;
            else if (version == IpVersion::IPv4)
                hints.ai_family = AF_INET;
            else if (version == IpVersion::IPv6)
                hints.ai_family = AF_INET6;
            else
                throw InvalidArgumentException("Unknown IP version");

            // Perform the DNS lookup call.
            if (::getaddrinfo(hostName.toUtf8(), "0", &hints, &result) != 0)
                throw SocketException("Error during DNS resolution");

            for (addrinfo* i = result; i != NULL; i = i->ai_next)
            {
                NetworkAddress addr;
                void* ip = 0;

                // Translate the IP version.
                switch (i->ai_family)
                {
                    case AF_INET6:
                        addr._version = IpVersion::IPv6;
                        ip = &((struct sockaddr_in6*) i->ai_addr)->sin6_addr;
                        break;

                    case AF_INET:
                        addr._version = IpVersion::IPv4;
                        ip = &((struct sockaddr_in*) i->ai_addr)->sin_addr;
                        break;
                }

                // Translate the protocol.
                switch (i->ai_socktype)
                {
                    case SOCK_STREAM:
                        addr._protocol = IpProtocol::Tcp;
                        break;

                    case SOCK_DGRAM:
                        addr._protocol = IpProtocol::Udp;
                        break;
                }

                // Translate the port number.
                if (i->ai_addrlen == sizeof(struct sockaddr_in))
                    addr._port = ::ntohs(((struct sockaddr_in*) i->ai_addr)->sin_port);
                else if (i->ai_addrlen == sizeof(struct sockaddr_in6))
                    addr._port = ::ntohs(((struct sockaddr_in6*) i->ai_addr)->sin6_port);

                // Translate the IP address.
                ::inet_ntop(i->ai_family, ip, addr._ip, sizeof(addr._ip));

                // Add the address to the Array.
                list.add(addr);
            }

            ::freeaddrinfo(result);
            return list;
        }

        bool NetworkAddress::isValidIp(const String& ip, IpVersion version)
        {
            byte_t addr[16];

            switch (version)
            {
                case IpVersion::IPv4:
                    return ::inet_pton(AF_INET, ip.toUtf8(), addr) == 1;

                case IpVersion::IPv6:
                    return ::inet_pton(AF_INET6, ip.toUtf8(), addr) == 1;

                case IpVersion::Any:
                    return isValidIp(ip, IpVersion::IPv4) || isValidIp(ip, IpVersion::IPv6);

                default:
                    throw InvalidArgumentException("Unknown IP version");
            }
        }
    }
}

