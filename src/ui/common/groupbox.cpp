// Local Dependencies
#include "../include/app.h"
#include "../include/componentadapter.h"
#include "../include/groupbox.h"

#ifdef NATIVE_PLATFORM_WIN32
# define USE_NATIVE_GROUP_BOX 1
#endif

namespace native
{
	namespace ui
	{
#ifdef USE_NATIVE_GROUP_BOX
		GroupBox::GroupBox() : LayoutComponent(new GroupBoxAdapter(this))
#else
        GroupBox::GroupBox() : LayoutComponent()
#endif // USE_NATIVE_GROUP_BOX
		{
			setBackground(Color(0xFF, 0xFF, 0xFF));
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

			size.height += (measure.height / 2) + coord_t(13);
			size.width += coord_t(15);

			return size;
		}

        void GroupBox::onPaint(Canvas& canvas)
        {
#ifdef USE_NATIVE_GROUP_BOX
            Component::onPaint(canvas);
#else
			Size measure = getFont().measureText(_text.getLength() ? _text : L"Thank you");

			Rectangle area = getSize();

			area.y += measure.height / 2;
			area.height -= measure.height / 2;

            canvas.drawRectangle(area, Color(0xDC, 0xDC, 0xDC));

			area = measure;
			area.x += 7;

			canvas.fillRectangle(area.inflate(1, 0), getBackground());

            canvas.drawText(_text, _font, Point(7, 0));
#endif // USE_NATIVE_GROUP_BOX
        }

		void GroupBox::onSize(const Size& size)
		{
			Rectangle area = size;

			Size measure = getFont().measureText(_text.getLength() ? _text : L"Thank you");

			area = area.deflate(7);
			area.y += measure.height / 2;

			for (auto child : getChildren())
				child->allocateArea(area);
		}
	}
}

