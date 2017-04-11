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
			Size size;

			// Check what our x/y co-ordinates are.
			const Orientation LENGTH = getOrientation();
			const Orientation DEPTH  = getOrientation() == Horizontal ? Vertical : Horizontal;

			for (auto child : getChildren())
			{
				Size childSize = child->getPreferredSize();

				// Increase the preferred length.
				size[LENGTH] += childSize[LENGTH];

				// Adjust the depth (against the orientation).
				if (size[DEPTH] < childSize[DEPTH])
					size[DEPTH] = childSize[DEPTH];
			}

			return size;
		}
	}
}

