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
	}
}

