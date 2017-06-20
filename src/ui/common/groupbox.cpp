// Local Dependencies
#include "../include/app.h"
#include "../include/componentadapter.h"
#include "../include/groupbox.h"

namespace native
{
	namespace ui
	{
#ifdef NATIVE_PLATFORM_WIN32
		GroupBox::GroupBox() : LayoutComponent(new GroupBoxAdapter(this))
#else
        GroupBox::GroupBox() : LayoutComponent()
#endif // NATIVE_PLATFORM_WIN32
		{
			setFont(Font::getDefault());
			setAlignment(Align::Left | Align::Top);
		}

		void GroupBox::setText(const String& text)
		{
            IComponentAdapter* adapter = getAdapter();

            if (adapter)
			    adapter->setText(text);

			_text = text;
		}

		void GroupBox::setFont(const Font& font)
		{
            IComponentAdapter* adapter = getAdapter();

            if (adapter)
			    adapter->setFont(font);

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

			return Size(500, 500);
		}

        void GroupBox::onPaint(Canvas& canvas)
        {
#ifdef NATIVE_PLATFORM_WIN32
            Component::onPaint(canvas);
#else
            canvas.drawRectangle(getSize(), Color());

            canvas.drawText(_text, _font);
#endif // NATIVE_PLATFORM_WIN32
        }
	}
}

