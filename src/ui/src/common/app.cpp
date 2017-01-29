// Module Dependencies
#include "../../include/app.h"
#include "../../include/eventqueue.h"

namespace native
{
	namespace ui
	{
		App::App()
		{
		}

		int App::run()
		{
			setVisible(true);

			while (isVisible() && EventQueue::handleEvent())
				;	// No-op.

			return EventQueue::getExitCode();
		}
	}
}

