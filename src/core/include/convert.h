#ifndef _NATIVE_CONVERT_H_
#define _NATIVE_CONVERT_H_ 1

// Module Dependencies
#include "types.h"

namespace native
{
	/**
		Convert is a static class that provides basic type conversions.
	 */
	class Convert
	{
		Convert() = delete;

	public:
		/**
			Converts a string to an int, or raises a FormatException.
			\param str The string to convert.
			\return The integer result.
		 */
		static int toInt(const wchar_t* str);
		static int toInt(const char* str);

		/**
			Converts a string to a float, or raises a FormatException.
			\param str The string to conert.
			\return The float result.
		 */
		static float toFloat(const wchar_t* str);
		static float toFloat(const char* str);
	};
}

#endif // _NATIVE_CONVERT_H_

