// Module Dependencies
#include "../include/app.h"
#include "../include/componentadapter.h"
#include "../include/inputcomponent.h"

namespace native
{
	namespace ui
	{
		static const Pen ENABLED_BORDER  = Color(0x80, 0x80, 0x80);
		static const Pen DISABLED_BORDER = Color(0xE0, 0xE0, 0xE0);

		InputComponent::InputComponent() : TextComponent(new InputAdapter(this))
		{
			setBorder(isEnabled() ? ENABLED_BORDER : DISABLED_BORDER);

			// TODO: Change when set to disabled.
		}

		Size InputComponent::getPreferredSize() const
		{
			String text = getText();

			Size size = getFont().measureText(text.getLength() ? text : "Thank you very much");

#ifdef NATIVE_FORM_MOBILE
            size.width  += coord_t(size.height * 2);
            size.height += coord_t(size.height * 1.5);
#else
            size.width  += coord_t(1 * App::getDisplayScale());
			size.height += coord_t(1 * App::getDisplayScale());
#endif

			return size;
		}

		void InputComponent::onPaint(Canvas& canvas)
		{
			// Do default system painting.
			Component::onPaint(canvas);
		}
	}
}

