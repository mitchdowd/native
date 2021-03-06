// System Dependencies
#include <Windows.h>

// Module Dependencies
#include "../include/alerts.h"
#include "../include/layoutcomponent.h"

namespace native
{
	namespace ui
	{
		void Alerts::messageBox(Component* owner, const String& message, const String& title)
		{
			Component* tmp = owner;

			while (tmp && !tmp->getAdapter())
				tmp = tmp->getParent();

			IComponentAdapter* adapter = tmp ? tmp->getAdapter() : nullptr;

			::MessageBox(adapter ? HWND(adapter->getHandle()) : NULL, message.toArray(), title.toArray(), MB_OK);
		}

		void Alerts::messageBox(const String& message, const String& title)
		{
			::MessageBox(NULL, message.toArray(), title.toArray(), MB_OK);
		}
	}
}

