#ifndef _NATIVE_UI_GROUP_BOX_H_
#define _NATIVE_UI_GROUP_BOX_H_ 1

// Local Dependencies
#include "layoutcomponent.h"

namespace native
{
	namespace ui
	{
		/**
			A GroupBox is a LayoutComponent which displays a title and a border
			around its children, portraying a logical grouping of Components.
		 */
		class GroupBox : public LayoutComponent
		{
		public:
			/** Creates a GroupBox with no initial text. */
			GroupBox();

			/**
				Sets the GroupBox heading text.
				\param text The new heading text.
			 */
			void setText(const String& text);

			/**
				Gets the current heading text for the GroupBox.
				\return The current ext.
			 */
			String getText() const { return _text; }

			/**
				Sets the Font used to display the GroupBox text.
				\param font The Font to set.
			 */
			void setFont(const Font& font);

			/**
				Gets the current Font for the GroupBox.
				\return The GroupBox Font.
			 */
			Font getFont() const { return _font; }

			/**
				Gets the preferred size, based upon its child Components.
				\return The preferred size.
			 */
			virtual Size getPreferredSize() const override;

		protected:
            /**
                Paints the GroupBox.
                @param canvas The Canvas to paint with.
             */
			virtual void onPaint(Canvas& canvas) override;

		private:
			// Instance Variables
			String _text;
			Font   _font;
		};
	}
}

#endif // _NATIVE_UI_GROUP_BOX_H_

