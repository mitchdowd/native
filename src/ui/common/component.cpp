// External Dependencies
#include "../../core/include/clock.h"
#include "../../core/include/exception.h"
#include "../../core/include/math.h"
#include "../../core/include/system.h"
#include "../../core/include/task.h"

// Module Dependencies
#include "../include/component.h"
#include "../include/layoutcomponent.h"

// Local Constants
#define LONG_CLICK_DURATION			750
#define CLICK_DISTANCE_THRESHOLD	 20

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
			, _area({ 0, 0, -1, -1 })
			, _alignment(Align::Top | Align::Left)
			, _margins({ 0, 0, 0, 0 })
		{
		}

		Component::Component(IComponentAdapter* adapter)
			: _adapter(adapter)
			, _parent(nullptr)
			, _area({ 0, 0, -1, -1 })
			, _alignment(Align::Top | Align::Left)
			, _margins({ 0, 0, 0, 0 })
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

			// Trigger the onSize() callback.
			if (!_adapter && area.getSize() != oldArea.getSize())
				onSize(area.getSize());
		}

		void Component::allocateArea(const Rectangle& area_)
		{
			Rectangle area = area_;

			// Take minimum size into account.
			area.ensureSize(getMinimumSize());

			// Take margins into account.
			area.x += _margins.left;
			area.y += _margins.top;
			area.width -= _margins.left + _margins.right;
			area.height -= _margins.top + _margins.bottom;

			Rectangle allocation = area;

			if (!_alignment.isSet(Align::Fill))
			{
				// Take preferred sizing into account.
				Size size = getSize();

				if (size.width < 0 || size.height < 0)
				{
					Size preferred = getPreferredSize();

					if (size.width < 0)
						size.width = preferred.width;
					if (size.height < 0)
						size.height = preferred.height;
				}

				if (!_alignment.isSet(Align::HFill))
					allocation.width = size.width;
				if (!_alignment.isSet(Align::VFill))
					allocation.height = size.height;
			}

			// Handle horizontal Alignments.
			if (_alignment.isSet(Align::Right))
				allocation.x = area.x + area.width - allocation.width;
			else if (_alignment.isSet(Align::HCenter))
				allocation.x = area.x + ((area.width - allocation.width) / 2);

			// Handle vertical Alignments.
			if (_alignment.isSet(Align::Bottom))
				allocation.y = area.y + area.height - allocation.height;
			else if (_alignment.isSet(Align::VCenter))
				allocation.y = area.y + ((area.height - allocation.height) / 2);

			setArea(allocation);
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
			if (!_background.getHandle())
			{
				// Fall back to the parent background.
				Component* parent = getParent();

				if (parent)
					return parent->getBackground();
			}

			return _background;
		}

		void Component::invokeAsync(const Function<void>& func)
		{
			Component* tmp = this;

			while (tmp && !tmp->_adapter)
				tmp = tmp->_parent;

			if (!tmp)
				throw InvalidStateException("Cannot invoke on unbound Component");

			tmp->_adapter->invokeAsync(func);
		}

		void Component::onInput(const InputEvent& event)
		{
			// TODO: Multi-touch will have an array of pressed items.
			static struct {
				Component*    component;
				Clock::tick_t time;
				InputEvent    event;
				uint32_t      counter;
			} pressed;

			if (_adapter)
				_adapter->doInput(event);

			switch (event.action)
			{
			case InputEvent::Press:
				// Prepare first half of click action.
				pressed.component = this;
				pressed.time      = Clock::tick();
				pressed.event     = event;

				if (event.source == InputEvent::Touch)
				{
					uint32_t count = ++pressed.counter;

					Task<void>([=]() {
						Thread::sleep(LONG_CLICK_DURATION);

						if (count == pressed.counter && Atomic::compareExchange((volatile void*&) pressed.component, nullptr, this) == this)
						{
							Clock::tick_t duration = Clock::tick() - pressed.time;

							if (Clock::toMilliSeconds(duration) >= LONG_CLICK_DURATION)
								invokeAsync([this]() {
									onContextClick({ InputEvent::ContextClick, InputEvent::Touch, pressed.event.x, pressed.event.y, nullptr });
								});
						}
					});
				}
				break;

			case InputEvent::Release:
				// Check for end of click.
				if (Atomic::compareExchange((volatile void*&) pressed.component, nullptr, this) == this && event.source == pressed.event.source)
				{
					Clock::tick_t duration = Clock::tick() - pressed.time;

					// Check for various types of clicks.
					if (pressed.event.source == InputEvent::LeftButton) 
						onClick({ InputEvent::Click, InputEvent::Mouse, event.x, event.y, nullptr });
					if (pressed.event.source == InputEvent::Touch && Clock::toMilliSeconds(duration) < LONG_CLICK_DURATION)
						onClick({ InputEvent::Click, InputEvent::Touch, event.x, event.y, nullptr });
					else if (pressed.event.source == InputEvent::RightButton)
						onContextClick({ InputEvent::ContextClick, InputEvent::Mouse, event.x, event.y, nullptr });
				}
				break;

			case InputEvent::Motion:
				// Check if we should cancel the current click.
				if (pressed.component && event.source == InputEvent::Touch)
					if (Point(pressed.event.x, pressed.event.y).distanceFrom({ event.x, event.y }) > CLICK_DISTANCE_THRESHOLD)
						pressed.component = nullptr;

				break;
			}
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

		void Component::dispatchInputEvent(const InputEvent& event)
		{
			// TODO: Check for mouse capture?

            onInput(event);
		}
	}
}

