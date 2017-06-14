// Local Dependencies
#include "../include/app.h"
#include "../include/componentadapter.h"
#include "../include/textarea.h"

namespace native
{
	namespace ui
	{
		TextArea::TextArea() : InputComponent(new TextAreaAdapter(this))
		{
		}

		Size TextArea::getPreferredSize() const
		{
			Size size = InputComponent::getPreferredSize();

			return Size(160 * App::getDisplayScale(), size.height * 5);
		}
	}
}

