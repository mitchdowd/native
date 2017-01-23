// Module Dependencies
#include "../../include/componentadapter.h"
#include "../../include/window.h"

namespace native
{
	namespace ui
	{
		Window::Window() : LayoutComponent(new WindowAdapter())	// TODO - Inject
		{
		}

		void Window::setTitle(const String& title)
		{
			ComponentAdapter* adapter = getAdapter();

			if (adapter)
				adapter->setText(title);

			_title = title;
		}
	}
}

