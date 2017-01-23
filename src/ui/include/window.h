#ifndef _NATIVE_UI_WINDOW_H_
#define _NATIVE_UI_WINDOW_H_ 1

// External Dependencies
#include "../../core/include/string.h"

// Module Dependencies
#include "layoutcomponent.h"

namespace native
{
	namespace ui
	{
		/**
			A top-level Component.
		 */
		class Window : public LayoutComponent
		{
		public:
			/** Default constructor. */
			Window();

			/**
				Sets the title to display at the top of the Window.
				\param title The title text to display.
			 */
			void setTitle(const String& title);

			/**
				Gets the current title text for the Window.
				\return The current Window title.
			 */
			String getTitle() const { return _title; }

		private:
			// Instance Variables
			String _title;
		};
	}
}

#endif // _NATIVE_UI_WINDOW_H_

