#ifndef _NATIVE_UI_LABEL_H_
#define _NATIVE_UI_LABEL_H_ 1

// Local Dependencies
#include "textcomponent.h"

namespace native
{
	namespace ui
	{
		/**
			Currently this doesn't implement anything further over a basic
			TextComponent. But, in the future it may...
		 */
		class Label : public TextComponent
		{
		public:
			/** Creates a Label with no text set. */
			Label() : TextComponent() {}

			/**
				Creates the Label with the given text.
				\param text The text to set.
			 */
			Label(const String& text) : TextComponent(text) {}
		};
	}
}

#endif // _NATIVE_UI_LABEL_H_

