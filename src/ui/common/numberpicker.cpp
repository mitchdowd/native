// Local Dependencies
#include "../include/componentadapter.h"
#include "../include/numberpicker.h"

namespace native
{
	namespace ui
	{
		NumberPicker::NumberPicker() : Component(new NumberPickerAdapter(this))
		{
#ifdef NATIVE_PLATFORM_WIN32
			static const Pen BORDER_COLOR = Color(0x80, 0x80, 0x80);

			setBorder(BORDER_COLOR);
#endif // NATIVE_PLATFORM_WIN32
		}

		void NumberPicker::setValue(int value)
		{
			((NumberPickerAdapter*) getAdapter())->setValue(value);
		}

		int NumberPicker::getValue() const
		{
			return ((NumberPickerAdapter*) getAdapter())->getValue();
		}

		void NumberPicker::setRange(int min, int max)
		{
			((NumberPickerAdapter*)getAdapter())->setRange(min, max);
		}

		int NumberPicker::getMinimum() const
		{
			return ((NumberPickerAdapter*) getAdapter())->getMinimum();
		}

		int NumberPicker::getMaximum() const
		{
			return ((NumberPickerAdapter*) getAdapter())->getMaximum();
		}

		Size NumberPicker::getPreferredSize() const
		{
#ifdef NATIVE_PLATFORM_ANDROID
            // TODO: Calculate this.
			return { 100, 100 };
#else
            // TODO: Calculate this.
            return { 60, 25 };
#endif

		}
	}
}