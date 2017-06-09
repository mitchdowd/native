// External Dependencies
#include "../../core/include/set.h"
#include "../../core/include/map.h"
#include "../../core/include/spinlock.h"

// Local Dependencies
#include "../include/app.h"
#include "../include/componentadapter.h"
#include "../include/radiobutton.h"

namespace native
{
	namespace ui
	{
		static Map<handle_t, Set<RadioButton*>> groups;
		static SpinLock groupsLock;

		RadioButton::RadioButton() : TextComponent(new RadioButtonAdapter(this)), _group(nullptr), _checked(false)
		{
			setMargins(coord_t(2 * App::getDisplayScale()), 0, coord_t(2 * App::getDisplayScale()), 0);
		}

		RadioButton::~RadioButton()
		{
			setGroup(nullptr);
		}

		void RadioButton::check()
		{
			if (_group == nullptr)
				setGroup(getParent());

			RadioButtonAdapter* adapter = (RadioButtonAdapter*) getAdapter();
			adapter->setChecked(_checked = true);

			if (_group)
			{
				groupsLock.lock();

				// Uncheck others in group.
				for (auto radio : groups[_group])
					if (radio->isChecked() && radio != this)
						((RadioButtonAdapter*) radio->getAdapter())->setChecked(radio->_checked = false);

				groupsLock.release();
			}
		}

		void RadioButton::setGroup(handle_t group)
		{
			if (_group != group)
			{
				groupsLock.lock();

				if (_group)
				{
					// Remove from old group.
					groups[_group].remove(this);
				}

				if ((_group = group))
				{
					// Add to new group.
					if (!groups.containsKey(_group))
						groups.add(_group, Set<RadioButton*>());

					groups[_group].add(this);
				}

				groupsLock.release();
			}
		}

		Size RadioButton::getPreferredSize() const
		{
			Size size = TextComponent::getPreferredSize();

#ifdef NATIVE_FORM_MOBILE
			size.width += coord_t(size.height * 1.7);
            size.height *= 1.1;
#else
			size.width += coord_t(size.height * 0.666667);
#endif

			return size;
		}

		void RadioButton::onPaint(Canvas& canvas)
		{
			Component::onPaint(canvas);
		}
	}
}

