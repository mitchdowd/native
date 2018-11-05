#ifndef _NATIVE_IO_CONSOLE_H_
#define _NATIVE_IO_CONSOLE_H_ 1

// External Dependencies
#include "../../core/include/string.h"

namespace native
{
	namespace io
	{
		/**
			Functions for reading and writing to the system console.
		 */
		class Console
		{
		public:
			/**
				Writes a String of text to the console.
				\param text The text to write.
			 */
			static void write(const String& text);

			/**
				Writes a String of text to the console, and includes a new line
				sequence at the end.
				\param text The text to write.
			 */
			static void writeLine(const String& text);

		private:
			// Prevent Creation
			Console() = delete;
		};
	}
}

#endif // _NATIVE_IO_CONSOLE_H_

