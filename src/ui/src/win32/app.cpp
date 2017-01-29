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

		int App::run()
		{
			throw NotImplementedException();
			/*
			setVisible(true);

			while (isVisible() && EventQueue::handleEvent())
				;	// No-op.

			return EventQueue::getExitCode();
			*/
		}
	}
}

