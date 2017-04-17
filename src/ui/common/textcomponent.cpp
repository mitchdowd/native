// Module Dependencies
#include "../include/canvas.h"
#include "../include/componentadapter.h"
#include "../include/textcomponent.h"

namespace native
{
	namespace ui
	{
		TextComponent::TextComponent() : Component(new TextComponentAdapter(this))
		{
            setFont(Font::getDefault());
		}

		TextComponent::TextComponent(const String& text) : Component(new TextComponentAdapter(this))
		{
			setFont(Font::getDefault());
			setText(text);
		}

		TextComponent::TextComponent(IComponentAdapter* adapter) : Component(adapter)
		{
            setFont(Font::getDefault());
		}

		void TextComponent::setText(const String& text)
		{
			IComponentAdapter* adapter = getAdapter();

			if (adapter)
				adapter->setText(text);

			_text = text;
		}

		void TextComponent::setFont(const Font& font)
		{
			IComponentAdapter* adapter = getAdapter();

			if (adapter)
				adapter->setFont(font);

			_font = font;
		}

		Size TextComponent::getPreferredSize() const
		{
			return getFont().measureText(getText());
		}

		void TextComponent::onPaint(Canvas& canvas)
		{
			// Paint the background...
			canvas.fillRectangle(getContentArea().getSize(), getBackground());

			// Paint the text.
			canvas.drawText(getText(), getFont());
		}
	}
}

