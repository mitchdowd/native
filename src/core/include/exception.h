#ifndef _NATIVE_EXCEPTION_H_
#define _NATIVE_EXCEPTION_H_ 1

// Standard Dependencies
#include <exception>

namespace native
{
	/**
		Base class for all exceptions thrown in this framework.
	 */
	class Exception : public std::exception
	{
	public:
		/**
			Provides a message concerning the Exception.
			\return An Exception message with more information.
		 */
		virtual const char* what() const override;
	};

	/**
		There are not enough system resources to perform the given operation.
	 */
	class InsufficientResourcesException : public Exception
	{
	};

	/**
		A provided function argument was not valid.
	 */
	class InvalidArgumentException : public Exception
	{
	};

	/**
		The object is in an invalid state to execute this function.
	 */
	class InvalidStateException : public Exception
	{
	};

	/**
		The given function has not yet been implemented.
	 */
	class NotImplementedException : public Exception
	{
	};
}

#endif // _NATIVE_EXCEPTION_H_

