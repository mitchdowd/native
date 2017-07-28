#ifndef _NATIVE_UI_ACTION_H_
#define _NATIVE_UI_ACTION_H_ 1

// External Dependencies
#include "../../core/include/string.h"

namespace native
{
	namespace ui
	{
		/**
			An action which the end user can trigger by clicking a display item
			such as a menu item or toolbar button.
		 */
		class Action
		{
		public:
			/**
				Gets the Action's display text.
				\return The action text.
			 */
			String getText() const { return _text; }

		private:
			// Instance Variables
			String _text;
		};
	}
}

#endif // _NATIVE_UI_ACTION_H_

