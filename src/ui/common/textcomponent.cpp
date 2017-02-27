// Module Dependencies
#include "../include/componentadapter.h"
#include "../include/textcomponent.h"

namespace native
{
	namespace ui
	{
		TextComponent::TextComponent() : Component(new TextComponentAdapter())
		{
		}

		TextComponent::TextComponent(IComponentAdapter* adapter) : Component(adapter)
		{
		}

		void TextComponent::setText(const String& text)
		{
			IComponentAdapter* adapter = getAdapter();

			if (adapter)
				adapter->setText(text);

			_text = text;
		}
	}
}

