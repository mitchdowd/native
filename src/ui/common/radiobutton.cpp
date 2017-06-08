// Local Dependencies
#include "../include/componentadapter.h"
#include "../include/radiobutton.h"

namespace native
{
	namespace ui
	{
		RadioButton::RadioButton() : TextComponent(new RadioButtonAdapter(this))
		{
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

