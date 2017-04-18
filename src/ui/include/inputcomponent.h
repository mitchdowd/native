#ifndef _NATIVE_UI_INPUT_COMPONENT_H_
#define _NATIVE_UI_INPUT_COMPONENT_H_ 1

// Module Dependencies
#include "textcomponent.h"

namespace native
{
	namespace ui
	{
		/**
			An InputComponent allows the user to enter basic text input into the
			app.
		 */
		class InputComponent : public TextComponent
		{
		public:
			/** Default constructor. */
			InputComponent();

		protected:
			/** Draws the input. */
			virtual void onPaint(Canvas& canvas) override;
		};
	}
}

#endif // _NATIVE_UI_INPUT_COMPONENT_H_

