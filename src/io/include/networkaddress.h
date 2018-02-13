#ifndef _NATIVE_IO_NETWORK_ADDRESS_H_
#define _NATIVE_IO_NETWORK_ADDRESS_H_ 1

// External Dependencies
#include "../../core/include/list.h"
#include "../../core/include/string.h"

namespace native
{
    namespace io
    {
        /** Internet protocol versions. */
        enum class IpVersion
        {
            Any  = 0,	///< Any IP version is acceptable.
            IPv4 = 1,	///< IP version 4.
            IPv6 = 2	///< IP version 6.
        };

        /** Available networking protocols. */
        enum class IpProtocol
        {
			Any = 0,
            Tcp = 1,	///< Transmission control protocol.
            Udp = 2 	///< User datagram protocol.
        };

        /** A network port. */
        typedef uint16_t port_t;

        /**
         * An address to identify a networking end-point.
         */
        class NetworkAddress
        {
        public:
            /**
                Creates a Network address with the given IP address and port number.
                \param ip The IP address, as either IPv4 or IPv6.
                \param port The port number.
                \param version The IP version to try to parse it as.
             */
            NetworkAddress(const String& ip, port_t port, IpVersion version = IpVersion::Any);

            /**
                Retrieves the port number.
                \return The port number.
             */
            port_t getPort() const noexcept { return _port; }

            /**
                Retrieves the IP address, as a String.
                \return The IP address string.
             */
            String getIp() const { return _ip; }

            /**
                Returns the IP version for this address (IPv4 or IPv6).
                \return The IpVersion.
             */
            IpVersion getIpVersion() const noexcept { return _version; }

            /**
                Retrieves an Array of NetworkAddresses which match the given hostName.
                This performs a full DNS resolution to acquire IP addresses.
                \param hostName The host name to resolve.
                \param version The IP version (defaults to IPv4).
                \return Matching NetworkAddresses.
             */
            static List<NetworkAddress> byHost(const String& hostName, IpVersion version = IpVersion::Any);

            /**
                Checks whether the specified IP address is validly formatted.
                \param ip The IP address string.
                \param version The IP version to match against.
                \return true or false.
             */
            static bool isValidIp(const String& ip, IpVersion version = IpVersion::Any);

        private:
            // Default Constructor
			NetworkAddress() = default;

            // Instance Variables
            IpVersion  _version;
            IpProtocol _protocol;
            port_t     _port;
            char       _ip[46];
        };
    }
}

#endif // _NATIVE_IO_NETWORK_ADDRESS_H_

