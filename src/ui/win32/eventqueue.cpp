// System Dependencies
#include <Windows.h>

// Module Dependencies
#include "../include/eventqueue.h"

namespace native
{
	namespace ui
	{
		// Static Variable Initialisations
		thread_local int EventQueue::_exitCode = 0;

		bool EventQueue::handleEvent(bool block)
		{
			MSG  msg = {};
			BOOL result = 0;

			// Retrieve the message.
			result = block
				? ::GetMessage(&msg, NULL, 0, 0)
				: ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

			if (result == -1)
				throw EventException();

			HWND wnd = ::GetActiveWindow();

			// Process the message.
			if (result > 0 && !::IsDialogMessage(wnd, &msg))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}

			return result != 0;
		}

		void EventQueue::quitWithCode(int exitCode)
		{
			::PostQuitMessage(_exitCode = exitCode);
		}
	}
}

