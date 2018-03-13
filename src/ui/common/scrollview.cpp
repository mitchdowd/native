// Local Dependencies
#include "../include/componentadapter.h"
#include "../include/scrollview.h"

namespace native
{
    namespace ui
    {
        ScrollView::ScrollView() : LayoutComponent(new ScrollViewAdapter(this))
        {
        }

		void ScrollView::onSize(const Size& size)
		{
			for (auto child : getChildren())
				child->allocateArea(child->getPreferredSize());
		}
    }
}
