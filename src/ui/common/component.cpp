// External Dependencies
#include "../../core/include/exception.h"
#include "../../core/include/system.h"

// Module Dependencies
#include "../include/component.h"
#include "../include/layoutcomponent.h"

namespace native
{
	namespace ui
	{
		static Rectangle toSystemArea(const Component* component, const Rectangle& area_)
		{
			Rectangle area = area_;

			for (const Component* i = component->getParent(); i && !i->getAdapter(); i = i->getParent())
				area = area.offset(i->getArea().getPosition());

			return area;
		}

		Component::Component()
			: _adapter(nullptr)
			, _parent(nullptr)
			, _alignment(Align::Top | Align::Left)
		{
		}

		Component::Component(IComponentAdapter* adapter)
			: _adapter(adapter)
			, _parent(nullptr)
			, _alignment(Align::Top | Align::Left)
		{
		}

		Component::~Component()
		{
			if (_parent)
				_parent->removeChild(this);

			delete _adapter;
		}

		void Component::setParent(LayoutComponent* parent)
		{
			if (parent != _parent)
			{
				if (parent) {
					parent->addChild(this);
				}
				else if (_adapter != nullptr) {
					// Converting to a popup Component.
					if (_parent)
						_parent->removeChild(this);

					_parent = nullptr;
					_adapter->setParent(nullptr);
				}
				else {
					// Can't pop up a Component without an adapter.
					throw InvalidStateException();
				}
			}
		}

		void Component::setVisible(bool visible)
		{
			if (_adapter)
				_adapter->setVisible(visible);

			_visibility = visible ? Show : Hide;
		}

		bool Component::isVisible() const
		{
			if (_adapter)
				return _adapter->isVisible();

			if (_visibility == Inherit)
			{
				// Inherit visibility from the parent.
				const Component* parent = getParent();
				return parent ? parent->isVisible() : false;
			}

			return _visibility == Show;
		}

		void Component::setArea(const Rectangle& area)
		{
			Rectangle oldArea = _area;

			if (_adapter)
				_adapter->setArea(toSystemArea(this, area).scale(System::getDisplayScale()));

			_area = area;
		}

		Rectangle Component::getContentArea() const
		{
			return _adapter ? _adapter->getContentArea().scale(1 / System::getDisplayScale()) : _area.getSize();
		}

		void Component::setBackground(const Brush& background)
		{
			_background = background;
		}

		Brush Component::getBackground() const
		{
			return _background;
		}

		void Component::onPaint(Canvas& canvas)
		{
			if (_adapter)
				_adapter->doPaint(canvas);
			else if (_background.getHandle())
				canvas.fillRectangle(getContentArea().getSize(), _background);
		}

		void Component::onSize(const Size& size)
		{
			// TODO?
		}

		void Component::setParentAdapter(IComponentAdapter* parent)
		{
			if (_adapter)
				_adapter->setParent(parent);
		}

		void Component::dispatchPaintEvent(Canvas& canvas)
		{
			onPaint(canvas);
		}
	}
}

