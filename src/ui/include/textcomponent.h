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
				Convenience constructor. Creates the TextComponent and sets its
				text during construction.
				\param text The text to set.
			 */
			TextComponent(const String& text);

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

			/**
				Sets the Font for this Component to draw its text with.
				\param font The Font to set.
			 */
			void setFont(const Font& font);

			/**
				Gets the Font used to draw the text in this TextComponent.
				\return The current Font.
			 */
			Font getFont() const { return _font; }

			/**
				Calculates the Size which will allow the current text to be
				displayed without being trimmed off.
				\return The preferred size.
			 */
			virtual Size getPreferredSize() const override;

		protected:
			/**
				Draws the component, including its text.
				\param canvas The canvas to draw with.
			 */
			virtual void onPaint(Canvas& canvas) override;

		private:
			// Instance Variables
			String _text;
			Font   _font;
		};
	}
}

#endif // _NATIVE_UI_TEXT_COMPONENT_H_

