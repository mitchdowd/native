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

		void TextArea::setScrollBars(bool horizontal, bool vertical)
		{
			TextAreaAdapter* adapter = (TextAreaAdapter*) getAdapter();

			adapter->setScrollBars(horizontal, vertical);
		}

		Size TextArea::getPreferredSize() const
		{
			Size size = InputComponent::getPreferredSize();

			return { coord_t(160 * App::getDisplayScale()), size.height * 5 };
		}
	}
}

