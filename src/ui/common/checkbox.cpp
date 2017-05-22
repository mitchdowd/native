// Module Dependencies
#include "../include/componentadapter.h"
#include "../include/checkbox.h"

namespace native
{
	namespace ui
	{
		Checkbox::Checkbox() : TextComponent(new CheckboxAdapter(this)), _checked(false)
		{
		}

		void Checkbox::setChecked(bool checked)
		{
			((CheckboxAdapter*) getAdapter())->setChecked(checked);
		}

		Size Checkbox::getPreferredSize() const
		{
			Size size = TextComponent::getPreferredSize();

			// TODO: Proper checkbox size calculation.
			return Size(size.width + 10, size.height);
		}

		void Checkbox::onPaint(Canvas& canvas)
		{
			Component::onPaint(canvas);
		}
	}
}

