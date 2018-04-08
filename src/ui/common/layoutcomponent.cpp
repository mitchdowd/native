// External Dependencies
#include "../../core/include/exception.h"

// Module Dependencies
#include "../include/layoutcomponent.h"

namespace native
{
    namespace ui
    {
		LayoutComponent::LayoutComponent()
		{
			setAlignment(Align::Fill);
		}

		LayoutComponent::LayoutComponent(IComponentAdapter* adapter) : Component(adapter)
		{
			setAlignment(Align::Fill);
		}

		LayoutComponent::~LayoutComponent()
		{
			for (auto child : _children)
				child->_parent = nullptr;
		}

		void LayoutComponent::insertChild(size_t index, Component* child)
		{
			if (child == nullptr)
				throw InvalidArgumentException();

			LayoutComponent* previousParent = child->getParent();

			if (previousParent != this)
			{
				// Remove the child from its previous parent.
				if (previousParent)
					previousParent->removeChild(child);

				// Add to its new place in the Component hierarchy.
				child->_parent = this;
				_children.insert(index, child);

				// Search for the next parent with an adapter.
				Component* tmp = this;

				while (tmp && !tmp->_adapter)
					tmp = tmp->_parent;

				// Update the native component adapter's parent.
				if (previousParent || tmp)
					child->setParentAdapter(tmp ? tmp->_adapter : nullptr);

				child->onParentChange(previousParent);
			}
		}

		void LayoutComponent::onSize(const Size& size)
		{
			for (auto child : _children)
				child->allocateArea(size);
		}

		void LayoutComponent::setParentAdapter(IComponentAdapter* parent)
		{
			IComponentAdapter* adapter = getAdapter();

			if (adapter)
				adapter->setParent(parent);
			else
			{
				for (auto child : _children)
					child->setParentAdapter(parent);
			}
		}

		void LayoutComponent::removeChild(Component* child)
		{
			for (size_t i = 0; i < _children.getLength(); ++i)
			{
				if (_children[i] == child)
				{
					_children.removeAt(i);
					break;
				}
			}
		}

		Size LayoutComponent::getPreferredSize() const
		{
			Size size;

			for (auto child : _children)
			{
				auto margins = child->getMargins();

				auto childSize = child->getPreferredSize();

				childSize.width += margins.left + margins.right;
				childSize.height += margins.top + margins.bottom;

				size = size.combine(childSize);
			}

			return size;
		}

		void LayoutComponent::dispatchInputEvent(const InputEvent& event)
		{
			// TODO: Check for mouse capture.

			// Check for a hit on a child Component.
			for (auto child : _children)
			{
				if (child->_adapter == nullptr)
				{
					Rectangle area = child->getArea();

					if (area.containsPoint(event.x, event.y)) {
						child->dispatchInputEvent({ event.action, event.source, event.x - area.x, event.y - area.y, nullptr });
						return;
					}
				}
			}

			Component::dispatchInputEvent(event);
		}

		void LayoutComponent::dispatchPaintEvent(Canvas& canvas)
		{
			// Paint our own background.
			onPaint(canvas);

			// Repaint the children.
			for (auto child : _children)
			{
				child->drawBorder(canvas);

				if (!child->_adapter)
				{
					// Offset the canvas to the child's content area.
					Point offset = child->getArea().getPosition();
					Rectangle content = child->getContentArea();
					offset.x += content.x;
					offset.y += content.y;

					canvas.offset(offset);
					child->dispatchPaintEvent(canvas);
					canvas.offset(offset.inverse());
				}
			}
		}
    }
}

