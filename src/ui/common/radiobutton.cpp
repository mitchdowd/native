// External Dependencies
#include "../../core/include/set.h"
#include "../../core/include/map.h"
#include "../../core/include/spinlock.h"

// Local Dependencies
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
		}

		RadioButton::~RadioButton()
		{
			groupsLock.lock();

			if (groups.containsKey(_group))
				groups[_group].remove(this);

			groupsLock.release();
		}

		void RadioButton::check()
		{
			if (_group == nullptr)
				setGroup(getParent());

			RadioButtonAdapter* adapter = (RadioButtonAdapter*)getAdapter();
			adapter->setChecked(_checked = true);

			// TODO: Uncheck others in group.
		}

		void RadioButton::setGroup(handle_t group)
		{
			if (_group)
				; // TODO: Remove from old group.

			if ((_group = group))
				; // TODO: Add to new group.
		}

		Size RadioButton::getPreferredSize() const
		{
			Size size = TextComponent::getPreferredSize();

#ifdef NATIVE_PLATFORM_ANDROID
			size.width += coord_t(size.height * 1.7);
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

