// Module Dependencies
#include "../include/exception.h"
#include "../include/singleton.h"

namespace native
{
	namespace internal
	{
		void singletonNotInitialised()
		{
			throw InvalidStateException();
		}
	}
}
