#ifndef _NATIVE_UI_TEXT_COMPONENT_H_
#define _NATIVE_UI_TEXT_COMPONENT_H_ 1

// Module Dependencies
#include "component.h"

namespace native
{
	namespace ui
	{
		/**
			A Component which displays text.
		 */
		class TextComponent : public Component
		{
		public:
			/** Creates a TextComponent with no text set. */
			TextComponent();

			/**
				Creates a TextComponent with the given native adapter.
				\param adapter The adapter to set.
			 */
			TextComponent(IComponentAdapter* adapter);

			/**
				Sets the text to display in the TextComponent.
				\param text The text to display.
			 */
			void setText(const String& text);

			/**
				Gets the text currently set in this TextComponent.
				\return The current text in the component.
			 */
			String getText() const { return _text; }

		private:
			// Instance Variables
			String _text;
		};
	}
}

#endif // _NATIVE_UI_TEXT_COMPONENT_H_

