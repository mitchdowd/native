// Module Dependencies
#include "../../include/componentadapter.h"
#include "../../include/window.h"

namespace native
{
	namespace ui
	{
		Window::Window() : LayoutComponent(new WindowAdapter())
		{
		}

		Window::Window(IComponentAdapter* adapter) : LayoutComponent(adapter)
		{
		}

		void Window::setTitle(const String& title)
		{
			IComponentAdapter* adapter = getAdapter();

			if (adapter)
				adapter->setText(title);

			_title = title;
		}
	}
}

