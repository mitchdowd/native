#ifndef _NATIVE_EXCEPTION_H_
#define _NATIVE_EXCEPTION_H_ 1

// Standard Dependencies
#include <exception>

// Module Dependencies
#include "string.h"

namespace native
{
	/**
		Base class for all exceptions thrown in this framework.
	 */
	class Exception : public std::exception
	{
	public:
		/**
			Creates an Exception with a (hopefully) helpful error message.
			\param message The error message.
		 */
		Exception(String message) : _message(message.toUtf8()) {}

		/**
			Provides a message concerning the Exception.
			\return An Exception message with more information.
		 */
		String getMessage() const { return String(_message); }

		/**
			Provides a message concerning the Exception, exposed in the format
			used by std::exception.
			\return An Exception message with more information.
		 */
		virtual const char* what() const noexcept override { return _message; }

	private:
		// Instance Variables
		ByteArray _message;
	};

	/**
		The supplied index to an Array is out of bounds.
	 */
	class ArrayIndexException : public Exception
	{
	public:
		ArrayIndexException(const char* message = "Array index out of bounds") : Exception(message) {}
	};

	/**
		An input was in the incorrect format.
	 */
	class FormatException : public Exception
	{
	public:
		FormatException(const char* message = "Invalid input format") : Exception(message) {}
	};

	/**
		There are not enough system resources to perform the given operation.
	 */
	class InsufficientResourcesException : public Exception
	{
	public:
		InsufficientResourcesException(const char* message = "Insufficient resources") : Exception(message) {}
	};

	/**
		A provided function argument was not valid.
	 */
	class InvalidArgumentException : public Exception
	{
	public:
		InvalidArgumentException(const char* message = "Invalid argument") : Exception(message) {}
	};

	/**
		The object is in an invalid state to execute this function.
	 */
	class InvalidStateException : public Exception
	{
	public:
		InvalidStateException(const char* message = "Invalid object state") : Exception(message) {}
	};

	/**
		The given function has not yet been implemented.
	 */
	class NotImplementedException : public Exception
	{
	public:
		NotImplementedException(const char* message = "Function not implemented") : Exception(message) {}
	};

	/**
		The given operation is not supported on the current platform.
	 */
	class NotSupportedException : public Exception
	{
	public:
		NotSupportedException(const char* message = "Operation not supported") : Exception(message) {}
	};

	/**
		Insufficient access is granted on a particular resource.
	 */
	class AccessException : public Exception
	{
	public:
		AccessException(const char* message = "Insufficient access") : Exception(message) {}
	};

	/**
		Exception thrown when a blocking call has been interrupted.
	 */
	class InterruptException : public Exception
	{
	public:
		InterruptException(const char* message = "Wait timer interrupted") : Exception(message) {}
	};
}

#endif // _NATIVE_EXCEPTION_H_

