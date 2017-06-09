// Module Dependencies
#include "../include/app.h"
#include "../include/componentadapter.h"
#include "../include/checkbox.h"

namespace native
{
	namespace ui
	{
		Checkbox::Checkbox() : TextComponent(new CheckboxAdapter(this)), _checked(false)
		{
			setMargins(coord_t(2 * App::getDisplayScale()), 0, coord_t(2 * App::getDisplayScale()), 0);
		}

		void Checkbox::setChecked(bool checked)
		{
			((CheckboxAdapter*) getAdapter())->setChecked(checked);
		}

		Size Checkbox::getPreferredSize() const
		{
			Size size = TextComponent::getPreferredSize();

#ifdef NATIVE_FORM_MOBILE
			// TODO: Proper checkbox size calculation.
			return Size(size.width + 40, size.height + 5);
#else
            // TODO: Proper checkbox size calculation.
			return Size(size.width + 10, size.height);
#endif
		}

		void Checkbox::onPaint(Canvas& canvas)
		{
			Component::onPaint(canvas);
		}
	}
}

