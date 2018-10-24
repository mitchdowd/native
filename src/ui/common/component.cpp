// External Dependencies
#include "../../core/include/clock.h"
#include "../../core/include/exception.h"
#include "../../core/include/stack.h"
#include "../../core/include/system.h"
#include "../../core/include/task.h"

// Module Dependencies
#include "../include/app.h"
#include "../include/component.h"
#include "../include/layoutcomponent.h"

// Local Constants
#define LONG_CLICK_DURATION			750
#define CLICK_DISTANCE_THRESHOLD	 20

namespace native
{
	namespace ui
	{
		static Rectangle toContentArea(const Component* component, const Rectangle& area)
		{
			Pen border = component->getBorder();

			if (border.getThickness() != 0.0)
				return area.deflate(border.getThickness());

			return area;
		}

		static Rectangle toSystemArea(const Component* component, const Rectangle& area_)
		{
			Rectangle area = component->getParent() ? toContentArea(component, area_) : area_;

			for (const Component* i = component->getAdapter() ? component->getParent() : component; i && !i->getAdapter(); i = i->getParent())
			{
				area = area.offset(toContentArea(i, area.getSize()).getPosition());
				area = area.offset(i->getArea().getPosition());
			}

			return area;
		}

		Component::Component()
			: _adapter(nullptr)
			  , _parent(nullptr)
			  , _visibility(Inherit)
			  , _enabled(true)
			  , _area({0, 0, -1, -1})
			  , _refreshing(false)
			  , _alignment(Align::Top | Align::Left)
			  , _margins({0, 0, 0, 0})
		{
		}

		Component::Component(IComponentAdapter* adapter)
			: _adapter(adapter)
			, _parent(nullptr)
			, _visibility(Inherit)
			, _enabled(true)
			, _area({ 0, 0, -1, -1 })
			, _refreshing(false)
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
					LayoutComponent* oldParent = _parent;

					// Converting to a popup Component.
					if (oldParent)
						oldParent->removeChild(this);

					_parent = nullptr;
					_adapter->setParent(nullptr);

					onParentChange(oldParent);
				}
				else {
					// Can't pop up a Component without an adapter.
					throw InvalidStateException();
				}
			}
		}

		bool Component::isDescendantOf(const Component* parent) const
		{
			for (const Component* i = getParent(); i; i = i->getParent())
				if (i == parent)
					return true;

			return false;
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

		void Component::setEnabled(bool enable)
		{
			if (_adapter)
				_adapter->setEnabled(enable);

			_enabled = enable;
		}

		void Component::setArea(const Rectangle& area)
		{
			Rectangle oldArea = _area;

			if (_adapter)
				_adapter->setArea(toSystemArea(this, area).scale(App::getDisplayScale()));

			_area = area;

			// Trigger the onSize() callback.
			if (((_parent || !_adapter) && area.getSize() != oldArea.getSize()) || isRefreshing())
				onSize(toContentArea(this, area).getSize());
		}

		void Component::setSize(coord_t width, coord_t height)
		{
			Rectangle area = getArea();

			area.width  = width;
			area.height = height;

			setArea(area);
		}

		void Component::allocateArea(const Rectangle& area)
		{
			Rectangle area_ = area;

			// Take minimum size into account.
			area_.ensureSize(getMinimumSize());

			// Take margins into account.
			area_.x += _margins.left;
			area_.y += _margins.top;
			area_.width -= _margins.left + _margins.right;
			area_.height -= _margins.top + _margins.bottom;

			Rectangle allocation = area_;

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
				allocation.x = area_.x + area_.width - allocation.width;
			else if (_alignment.isSet(Align::HCenter))
				allocation.x = area_.x + ((area_.width - allocation.width) / 2);

			// Handle vertical Alignments.
			if (_alignment.isSet(Align::Bottom))
				allocation.y = area_.y + area_.height - allocation.height;
			else if (_alignment.isSet(Align::VCenter))
				allocation.y = area_.y + ((area_.height - allocation.height) / 2);

			setArea(allocation);
		}

        void Component::refresh()
        {
            // Trigger repositioning of all child items.
            _refreshing = true;
            onSize(getContentArea().getSize());
            _refreshing = false;
        }

		void Component::repaint()
		{
			Component* parent = this;

			// Find the adapter to pass the call to.
			while (parent && !parent->getAdapter())
				parent = parent->getParent();

			if (parent)
			{
				Rectangle area = toSystemArea(this, getContentArea().getSize()).scale(App::getDisplayScale());
				parent->getAdapter()->invalidate(area);
			}
		}

		Rectangle Component::getContentArea() const
		{
			return toContentArea(this, _adapter ? _adapter->getContentArea().scale(1 / App::getDisplayScale()) : _area.getSize());
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

		void Component::setBorder(const Pen& pen)
		{
			_border = pen;
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
			if (_adapter)
				_adapter->doInput(event);
		}

		void Component::onPaint(Canvas& canvas)
		{
			if (_background.getHandle())
				canvas.fillRectangle(getContentArea().getSize(), _background);

			if (_adapter)
				_adapter->doPaint(canvas);
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

            // Disabled Components get no input.
			if (!isEnabled())
				return;

			// TODO: Multi-touch will have an array of pressed items.
			static struct {
				Component*    component;
				Clock::tick_t time;
				InputEvent    event;
				uint32_t      counter;
			} pressed;

			// Stack of components which the mouse is hovering over.
			static Stack<Component*> hovers;

			switch (event.action)
			{
			case InputEvent::Press:
				// Prepare first half of click action.
				pressed.component = this;
				pressed.time = Clock::tick();
				pressed.event = event;

				if (event.source == InputEvent::Touch)
				{
					uint32_t count = ++pressed.counter;

					Task<void>([=]() {
						Thread::sleep(LONG_CLICK_DURATION);

						if (count == pressed.counter && Atomic::compareExchange((volatile void*&)pressed.component, nullptr, this) == this)
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
				if (Atomic::compareExchange((volatile void*&)pressed.component, nullptr, this) == this && event.source == pressed.event.source)
				{
					Clock::tick_t duration = Clock::tick() - pressed.time;

					// Sent the Release event _before_ the Click calls.
					onInput(event);

					// Check for various types of clicks.
					if (pressed.event.source == InputEvent::LeftButton)
						onClick({ InputEvent::Click, InputEvent::Mouse, event.x, event.y, nullptr });
					if (pressed.event.source == InputEvent::Touch && Clock::toMilliSeconds(duration) < LONG_CLICK_DURATION)
						onClick({ InputEvent::Click, InputEvent::Touch, event.x, event.y, nullptr });
					else if (pressed.event.source == InputEvent::RightButton)
						onContextClick({ InputEvent::ContextClick, InputEvent::Mouse, event.x, event.y, nullptr });

					return;
				}
				break;

			case InputEvent::Motion:
				// Check if we should cancel the current click.
				if (pressed.component && event.source == InputEvent::Touch)
					if (Point(pressed.event.x, pressed.event.y).distanceFrom({ event.x, event.y }) > CLICK_DISTANCE_THRESHOLD)
						pressed.component = nullptr;

				if (event.source == InputEvent::Mouse)
				{
					if (hovers.isEmpty() || hovers.peek() != this)
					{
						// Generate leave events.
						while (!hovers.isEmpty() && !isDescendantOf(hovers.peek()))
						{
							// TODO: Sent translated co-ordinates.
							hovers.pop()->onInput({ InputEvent::Leave, InputEvent::Mouse, 0, 0, nullptr });
						}

						Queue<Component*> reverse;

						// Find all components we need to generate Enter actions for.
						for (Component* i = this; i; i = i->getParent()) {
							if (hovers.isEmpty() || hovers.peek() != i) {
								reverse.push(i);
								break;
							}
						}

						// Send the Enter events.
						while (!reverse.isEmpty())
						{
							hovers.push(reverse.peek());

							// TODO: Sent translated co-ordinates.
							reverse.pop()->onInput({ InputEvent::Enter, InputEvent::Mouse, 0, 0, nullptr });
						}
					}
				}

				break;
			}

			// Send the raw press/release/motion event.
			onInput(event);
		}

		void Component::drawBorder(Canvas& canvas)
		{
			Rectangle area = _adapter && !_parent ? _adapter->getContentArea().scale(1.0f / App::getDisplayScale()).getSize() : _area;

			// Draw the border as a rectangle.
			if (_border.getThickness() != 0.0)
			{
				if (isEnabled())
				{
					canvas.drawRectangle(area, _border);
				}
				else
				{
					Pen disabledBorder(_border.getColor().lighten(50), _border.getThickness());
					canvas.drawRectangle(area, disabledBorder);
				}
			}
		}

        bool Component::isRefreshing() const noexcept
        {
            if (_refreshing)
                return true;

            return _parent ? _parent->isRefreshing() : false;
        }
	}
}

