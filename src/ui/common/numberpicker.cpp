// Local Dependencies
#include "../include/componentadapter.h"
#include "../include/numberpicker.h"

namespace native
{
	namespace ui
	{
		NumberPicker::NumberPicker() : Component(new NumberPickerAdapter(this))
		{
		}

		Size NumberPicker::getPreferredSize() const
		{
			return Size(80, 30);
		}
	}
}