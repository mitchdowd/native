// System Dependencies
#include <iostream>

// Local Dependencies
#include "../include/console.h"

namespace native
{
	namespace io
	{
		void Console::write(const String& text)
		{
			std::wcout << text.toArray() << std::flush;
		}

		void Console::writeLine(const String& text)
		{
			std::wcout << text.toArray() << std::endl;
		}
	}
}