// Module Dependencies
#include "../../include/window.h"
#include "../../include/windowadapter.h"

namespace native
{
	namespace ui
	{
		Window::Window() : LayoutComponent(new WindowAdapter())
		{
		}
	}
}

