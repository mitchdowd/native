#include <iostream>

// Module Dependencies
#include "../../include/app.h"

namespace native
{
	namespace ui
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

