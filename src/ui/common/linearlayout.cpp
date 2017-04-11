// Module Dependencies
#include "../include/linearlayout.h"

namespace native
{
	namespace ui
	{
		LinearLayout::LinearLayout(Orientation orientation) : _orientation(orientation)
		{
		}

		void LinearLayout::onSize(const Size& size)
		{
			LayoutComponent::onSize(size);
		}

		Size LinearLayout::getPreferredSize() const
		{
			return LayoutComponent::getPreferredSize();
		}
	}
}

