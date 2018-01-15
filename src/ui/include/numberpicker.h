#ifndef _NATIVE_UI_NUMBER_PICKER_H_
#define _NATIVE_UI_NUMBER_PICKER_H_ 1

// Local Dependencies
#include "component.h"

namespace native
{
	namespace ui
	{
		/**
			NumberPicker is an input Component which allows the user to select
			a number.
		 */
		class NumberPicker : public Component
		{
		public:
			/** Creates a NumberPicker with unbounded range. */
			NumberPicker();
		};
	}
}

#endif // _NATIVE_UI_NUMBER_PICKER_H_

