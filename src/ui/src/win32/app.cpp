#include <iostream>

// Module Dependencies
#include "../../include/app.h"

namespace Native
{
	namespace UI
	{
		App::App()
		{
		}

		void App::setMessage(const char* message)
		{
			std::cout << message << std::endl;
		}
	}
}

