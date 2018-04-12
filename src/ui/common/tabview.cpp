// Local Dependencies
#include "../include/componentadapter.h"
#include "../include/tabview.h"

namespace native
{
	namespace ui
	{
		TabView::TabView() : LayoutComponent(new TabViewAdapter(this))
		{
		}
	}
}

