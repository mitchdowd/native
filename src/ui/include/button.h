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

			/** Signal emitted when the Button is clicked. */
			Signal<> onClicked;
        };
    }
}

#endif // _NATIVE_UI_BUTTON_H_
