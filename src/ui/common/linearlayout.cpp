// External Dependencies
#include "../../core/include/math.h"

// Module Dependencies
#include "../include/linearlayout.h"

namespace native
{
	namespace ui
	{
		/**
			Helper function which tests if an Alignment is a Fill alignment
			in the direction of the given Orientation.
		 */
		static bool isExpanding(Orientation orientation, Flags<Alignment> alignment)
		{
			// Optimised hack version.
			return alignment & (Alignment) orientation & Align::Fill;
		}

		LinearLayout::LinearLayout(Orientation orientation) : _orientation(orientation), _fillStrategy(FillStrategy::After)
		{
		}

		void LinearLayout::onSize(const Size& size)
		{
			const List<Component*> children = getChildren();
			Rectangle area = size;
			int32_t numChildren = 0;		// The number of child Components.
			int32_t expandingChildren = 0;	// The number of child Components which are Fill alignment.

			// Take minimum size into account.
			Size minSize = getMinimumSize();
			area.ensureSize(minSize);

			// Check what our x/y co-ordinates are.
			const Orientation LENGTH = getOrientation();
			const Orientation DEPTH = getOrientation() == Horizontal ? Vertical : Horizontal;

			// Determine how we'll be allocating "extra" space.
			Size prefSize = getPreferredSize();
			bool usePrefSize = area[LENGTH] > prefSize[LENGTH];

			// Expanding layouts will need some pre-calculation performed to divide the free space.
			for (Component* child : children)
			{
				// Count the visible children.
				numChildren++;

				// Count the expanding children.
				if (isExpanding(getOrientation(), getAlignment()) && isExpanding(getOrientation(), child->getAlignment()))
					expandingChildren++;
			}

			if (numChildren == 1)
			{
				// If there's only one child, just give it the whole area.
				children[0]->allocateArea(area);
			}
			else if (numChildren)
			{
				Rectangle childArea = area;

				// Determine how much "extra" space needs dividing among children.
				int32_t extraSpace   = area[LENGTH] - (usePrefSize ? prefSize[LENGTH] : minSize[LENGTH]);
				int32_t childSpacing = extraSpace / numChildren;
				int32_t remainingChildren = usePrefSize && expandingChildren ? expandingChildren : numChildren;

				// Allocate areas to children.
				for (Component* child : children)
				{
					Size childPrefSize = child->getPreferredSize();

					// Add desired margins.
					Margins childMargins = child->getMargins();
					childPrefSize.width += childMargins.left + childMargins.right;
					childPrefSize.height += childMargins.top + childMargins.bottom;

					if (usePrefSize)
					{
						// Grant it the preferred length.
						childArea[LENGTH] = childPrefSize[LENGTH];

						if ((expandingChildren == 0 || isExpanding(getOrientation(), child->getAlignment())) && _fillStrategy == FillStrategy::Between)
						{
							// Handle filling (Spacing Strategy: Space between).
							int32_t childExtra = --remainingChildren ? childSpacing : extraSpace;
							childArea[LENGTH] += childExtra;
							extraSpace -= childExtra;
						}
					}
					else
					{
						// Grant at least the minimum length.
						Size childMinSize = child->getMinimumSize();
						childArea[LENGTH] = childMinSize[LENGTH];

						// Fill up to preferred length (FillStrategy: Prioritise by index).
						int32_t childExtra = Math::min(extraSpace, childPrefSize[LENGTH] - childMinSize[LENGTH]);
						childArea[LENGTH] += childExtra;
						extraSpace -= childExtra;
					}

					// Allocate the area to the child.
					child->allocateArea(childArea);

					// Move on for the next child.
					if (getOrientation() == Horizontal)
						childArea.x += childArea.width;
					else
						childArea.y += childArea.height;
				}
			}
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

				// Add desired margins.
				Margins childMargins = child->getMargins();
				childSize.width  += childMargins.left + childMargins.right;
				childSize.height += childMargins.top + childMargins.bottom;

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

