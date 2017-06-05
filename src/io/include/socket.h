#ifndef _NATIVE_IO_SOCKET_H_
#define _NATIVE_IO_SOCKET_H_ 1

// External Dependencies
#include "../../core/include/exception.h"

namespace native
{
	namespace io
	{
		/** IP protocols which can be applied to a Socket. */
		enum class IpProtocol 
		{
			Tcp,
			Udp
		};

		/** Supported internet protocol versions. */
		enum class IpVersion
		{
			Any,
			IPv4,
			IPv6
		};

		/**
			The basis for network communication. Various subclasses may implement
			various networking protocols.
		 */
		class Socket
		{
		public:
			/** Destructor. */
			virtual ~Socket() { close(); }

			/**
				Closes the Socket. It can no longer perform any IO operations.
			 */
			void close() noexcept;

			/**
				Tells whether the Socket is closed or not.
				\return true if closed, false if connected.
			 */
			bool isClosed() const noexcept;

			/**
				Gets the socket descriptor for this Socket.
				\return The socket descriptor.
			 */
			handle_t getHandle() const noexcept { return _handle; }

		protected:
			/**
				Constructor. Creates a Socket with the given protocol.
				\param protocol The IP protocol to apply.
				\param version The IP version to use.
			 */
			Socket(IpProtocol protocol, IpVersion version = IpVersion::Any);

		private:
			// Instance Variables
			handle_t _handle;
		};

		/** Exception thrown on failed Socket operations. */
		class SocketException : public Exception
		{
		public:
			SocketException(const char* message = "Socket error") : Exception(message) {}
		};
	}
}

#endif // _NATIVE_IO_SOCKET_H_

