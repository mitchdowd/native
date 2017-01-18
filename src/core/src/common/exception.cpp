// Module Dependencies
#include "../../include/exception.h"

namespace native
{
	const char* Exception::what() const noexcept
	{
		static const char temp[] = "Error";

		return temp;
	}
}

