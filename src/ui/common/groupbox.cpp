// Local Dependencies
#include "../include/app.h"
#include "../include/componentadapter.h"
#include "../include/groupbox.h"

namespace native
{
	namespace ui
	{
		GroupBox::GroupBox() : LayoutComponent(new GroupBoxAdapter(this))
		{
			setFont(Font::getDefault());
			setAlignment(Align::Left | Align::Top);
		}

		void GroupBox::setText(const String& text)
		{
			getAdapter()->setText(text);

			_text = text;
		}

		void GroupBox::setFont(const Font& font)
		{
			getAdapter()->setFont(font);

			_font = font;
		}

		Size GroupBox::getPreferredSize() const
		{
			Size measure = getFont().measureText(_text.getLength() ? _text : L"Thank you");
			Size size = LayoutComponent::getPreferredSize();

			if (size.width < measure.width)
				size.width = measure.width;

			size.height += measure.height + coord_t(10 * App::getDisplayScale());
			size.width += coord_t(10 * App::getDisplayScale());

			return size;
		}
	}
}

