// Module Dependencies
#include "../include/canvas.h"
#include "../include/componentadapter.h"
#include "../include/textcomponent.h"

namespace native
{
	namespace ui
	{
		TextComponent::TextComponent() : Component(new TextComponentAdapter(this))
			, _font(Font::getDefault())
		{
		}

		TextComponent::TextComponent(IComponentAdapter* adapter) : Component(adapter)
			, _font(Font::getDefault())
		{
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
			return Canvas(*(Component*) this).measureText(getText(), getFont());
		}
	}
}

