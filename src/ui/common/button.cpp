// Module Dependencies
#include "../include/componentadapter.h"
#include "../include/button.h"

namespace native
{
    namespace ui
    {
        Button::Button() : TextComponent(new ButtonAdapter(this))
        {
        }

		Button::Button(const String& text) : TextComponent(new ButtonAdapter(this))
		{
            setText(text);
		}

		Size Button::getPreferredSize() const
		{
			Size size = TextComponent::getPreferredSize();

#ifdef NATIVE_FORM_MOBILE
            // Mobile needs bigger buttons with plenty of padding for fat fingers.
            coord_t padding = coord_t(size.height * 1.7);
#else
			coord_t padding = coord_t(size.height * 0.666667);
#endif
			size.width  += padding;
			size.height += padding;

			return size;
		}

		void Button::onPaint(Canvas& canvas)
		{
			Component::onPaint(canvas);
		}
    }
}

