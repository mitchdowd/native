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

			Note that until the RadioButton has been added to a parent, its default,
			parent-based grouping cannot be applied.
		 */
		class RadioButton : public TextComponent
		{
		public:
			/** Default constructor. Unchecked by default, with no text. */
			RadioButton();

			/** Destructor. */
			~RadioButton();

			/**
				Checks this RadioButton and unchecks all other RadioButtons that
				share a group with this RadioButton.
			 */
			void check();

			/**
				Determines whether this RadioButton is checked or not.
				\return true if checked, false otherwise.
			 */
			bool isChecked() const noexcept { return _checked; }

			/**
				Sets a grouping identifier for this RadioButton. Any RadioButton
				in the same group will operate mutually exclusively, so only one
				may be selected at a time. By default, the group ID is the parent
				Component.

				Note that setting a group will not update the checked status of
				any RadioButtons, and if there is already a checked RadioButton
				in the new group, it will still remain checked even if this
				button is checked.

				\param group An arbitrary ID or pointer.
			 */
			void setGroup(handle_t group);

			/**
				Calculates the preferred size of this RadioButton based upon its contents.
				\return The preferred size.
			 */
			virtual Size getPreferredSize() const override;

		protected:
			/**
				Checks the RadioButton.
				\param event Ignored.
			 */
			virtual void onClick(const InputEvent& event) override { check(); }

			/**
				Paints the RadioButton in its own system-defined way.
				\param canvas The Canvas to paint with.
			 */
			virtual void onPaint(Canvas& canvas) override;

		private:
			// Instance Variables
			bool     _checked;
			handle_t _group;
		};
	}
}

#endif // _NATIVE_RADIO_BUTTON_H_

