#ifndef _NATIVE_UI_TEXT_AREA_H_
#define _NATIVE_UI_TEXT_AREA_H_ 1

// Local Dependencies
#include "inputcomponent.h"

namespace native
{
	namespace ui
	{
		/**
			Displays an editable text box for capturing multi-line text input.
		 */
		class TextArea : public InputComponent
		{
		public:
			/** Default constructor. */
			TextArea();

			/**
				Gets the preferred size for the TextArea. Currently this is
				just the height of 5 lines of text.
				\return The preferred size.
			 */
			virtual Size getPreferredSize() const override;
		};
	}
}

#endif // _NATIVE_UI_TEXT_AREA_H_

