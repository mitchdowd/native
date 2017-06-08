#ifndef _NATIVE_RADIO_BUTTON_H_
#define _NATIVE_RADIO_BUTTON_H_ 1

// Local Dependencies
#include "textcomponent.h"

namespace native
{
	namespace ui
	{
		/**
			A RadioButton allows for mutually-exclusive option selections by the
			user. By default, all RadioButtons with the same parent Component will
			be mutually exclusive, but a different grouping object can be set in
			order to provide custom groupings.
		 */
		class RadioButton : public TextComponent
		{
		public:
			/** Default constructor. */
			RadioButton();

			/**
				Calculates the preferred size of this RadioButton based upon its contents.
				\return The preferred size.
			 */
			virtual Size getPreferredSize() const override;

		protected:
			/**
				Paints the RadioButton in its own system-defined way.
				\param canvas The Canvas to paint with.
			 */
			virtual void onPaint(Canvas& canvas) override;
		};
	}
}

#endif // _NATIVE_RADIO_BUTTON_H_

