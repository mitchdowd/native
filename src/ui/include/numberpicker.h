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

			/**
				Sets the current value in the NumberPicker.
				\param value The value to set.
			 */
			void setValue(int value);

			/**
				Gets the current number value.
				\return The current value.
			 */
			int getValue() const;

			/**
				Sets the range of allows values (the minimum and maximum).
				\param min The minimum value.
				\param max The maximum value.
			 */
			void setRange(int min, int max);

			/**
				Gets the minimum value of the NumberPicker.
				\return The minimum value.
			 */
			int getMinimum() const;

			/**
				Gets the maximum allowed value in the NumberPicker.
				\return The maximum value
			 */
			int getMaximum() const;

			/**
				Gets the preferred size for this Component.
				\return The preferred size.
			 */
			virtual Size getPreferredSize() const override;
		};
	}
}

#endif // _NATIVE_UI_NUMBER_PICKER_H_

