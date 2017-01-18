// Standard Dependencies
#include <cstdarg>
#include <cstdio>

// Module Dependencies
#include "../../include/log.h"

// Namespace Usage
using namespace std;

namespace native
{
	namespace test
	{
		void log(const char* format, ...)
		{
			va_list args;

			va_start(args, format);
			vprintf(format, args);
			va_end(args);
		}
	}
}
