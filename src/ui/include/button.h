#ifndef _NATIVE_UI_BUTTON_H_
#define _NATIVE_UI_BUTTON_H_ 1

// External Dependencies
#include "../../core/include/signal.h"

// Module Dependencies
#include "textcomponent.h"

namespace native
{
    namespace ui
    {
        /**
            An on-screen push button which can be clicked by the user
            in order to perform an action.
         */
        class Button : public TextComponent
        {
        public:
            /** Default constructor. A Button with no text. */
            Button();

			/**
				Convenience constructor, to create a Button and set its text
				at the same time.
				\param text The button text to set.
			 */
			Button(const String& text);

			/** Signal emitted when the Button is clicked. */
			Signal<> clicked;

			/**
				Calculates the preferred size of this Button based upon its contents.
				\return The preferred size.
			 */
			virtual Size getPreferredSize() const override;

		protected:
			/**
				Triggers the clicked Signal.
				\param event Ignored.
			 */
			virtual void onClick(const InputEvent& event) override { clicked(); }

			/**
				Paints the Button in its own system-defined way.
				\param canvas The Canvas to paint with.
			 */
			virtual void onPaint(Canvas& canvas) override;
        };
    }
}

#endif // _NATIVE_UI_BUTTON_H_
