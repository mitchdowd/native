// Module Dependencies
#include "../include/app.h"
#include "../include/eventqueue.h"

namespace native
{
	namespace ui
	{
		static int _appExists = 0;
		handle_t App::_handle = nullptr;

		App::App()
		{
			if (Atomic::compareExchange(_appExists, 1, 0) != 0)
				throw AppInitializationException("App already exists");
		}

		App::~App()
		{
			_appExists = 0;
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

