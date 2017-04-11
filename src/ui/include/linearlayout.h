#ifndef _NATIVE_UI_LINEAR_LAYOUT_H_
#define _NATIVE_UI_LINEAR_LAYOUT_H_ 1

// Module Dependencies
#include "layoutcomponent.h"

namespace native
{
	namespace ui
	{
		/**
		 * A Component which arranges its children in either a row or a column.
		 */
		class LinearLayout : public LayoutComponent
		{
		public:
			/**
			 * Constructor. Creates either a horizontal or vertical layout.
			 */
			LinearLayout(Orientation orientation = Horizontal);

			/**
				Sets the Orientation of this LineLayout.
				\param orientation The Orientation to set.
			 */
			void setOrientation(Orientation orientation) { _orientation = orientation; }

			/**
				Gets the current Orientation of this LineLayout.
				\return The current Orientation.
			 */
			Orientation getOrientation() const noexcept { return _orientation; }

			/**
				Retrieves the preferred size of this Layout, based on the preferred
				sizes of its constituent children.
				\return The preferred size.
			 */
			Size getPreferredSize() const override;

		protected:
			/**
				Called when the geometric size of the Component changes. This will
				arrange the children in either a row or column according to the
				current layout properties of all Components involved.
				\param size The new size.
			*/
			virtual void onSize(const Size& size) override;

		private:
			// Instance Variables
			Orientation _orientation;
		};

		/** A Layout which arranges its children vertically. */
		class VLayout : public LinearLayout
		{
		public:
			/** Creates the VLayout. */
			VLayout() : LinearLayout(Vertical) {}
		};

		/** A Layout which arranges its children horizontally. */
		class HLayout : public LinearLayout
		{
		public:
			/** Creates a HLayout. */
			HLayout() : LinearLayout(Horizontal) {}
		};
	}
}

#endif // _NATIVE_UI_LINEAR_LAYOUT_H_

