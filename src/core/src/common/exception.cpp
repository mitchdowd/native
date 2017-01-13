// Module Dependencies
#include "../../include/exception.h"

namespace native
{
	const char* Exception::what() const
	{
		static const char temp[] = "Error";

		return temp;
	}
}

