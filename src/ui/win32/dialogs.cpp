// System Dependencies
#include <windows.h>

// Module Dependencies
#include "../include/dialogs.h"
#include "../include/layoutcomponent.h"

namespace native
{
	namespace ui
	{
		void Dialogs::messageBox(Component* component, const String& message, const String& caption)
		{
			Component* tmp = component;

			while (tmp && !tmp->getAdapter())
				tmp = tmp->getParent();

			IComponentAdapter* adapter = tmp ? tmp->getAdapter() : nullptr;

			::MessageBox(adapter ? HWND(adapter->getHandle()) : NULL, message.toArray(), caption.toArray(), MB_OK);
		}

		void Dialogs::messageBox(const String& message, const String& caption)
		{
			::MessageBox(NULL, message.toArray(), caption.toArray(), MB_OK);
		}
	}
}

