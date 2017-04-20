// Module Dependencies
#include "../include/componentadapter.h"
#include "../include/inputcomponent.h"

namespace native
{
	namespace ui
	{
		InputComponent::InputComponent() : TextComponent(new InputAdapter(this))
		{
			static const Pen INPUT_BORDER = Color(0xE0, 0xE0, 0xE0);

			setBorder(INPUT_BORDER);
		}

		void InputComponent::onPaint(Canvas& canvas)
		{
			// Do default system painting.
			Component::onPaint(canvas);
		}
	}
}

