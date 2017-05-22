#ifndef _NATIVE_UI_CHECKBOX_H_
#define _NATIVE_UI_CHECKBOX_H_ 1

// Module Dependencies
#include "textcomponent.h"

namespace native
{
	namespace ui
	{
		/**
			Allows the user to enter a true/false value by selecting or unselecting
			the check box component.
		 */
		class Checkbox : public TextComponent
		{
		public:
			/** Creates a Checkbox. */
			Checkbox();

			/**
				Checks or unchecks the Checkbox.
				\param checked true to check, false to uncheck.
			 */
			void setChecked(bool checked);

			/**
				Tells whether the Checkbox is currently checked or not.
				\return true if checked, false if unchecked.
			 */
			bool isChecked() const noexcept { return _checked; }
			
			/**
				Calculates the preferred size of this Checkbox based upon its text.
				\return The preferred size.
			 */
			virtual Size getPreferredSize() const override;

		protected:
			/**
				Paints the Checkbox in its own system-defined way.
				\param canvas The Canvas to paint with.
			 */
			virtual void onPaint(Canvas& canvas) override;

		private:
			// Instance Variables
			bool _checked;
		};
	}
}

#endif // _NATIVE_UI_CHECKBOX_H_

