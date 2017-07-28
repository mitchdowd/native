#ifndef _NATIVE_UI_MENU_H_
#define _NATIVE_UI_MENU_H_ 1

// Module Dependencies
#include "action.h"

namespace native
{
	namespace ui
	{
		/**
			A displayable menu of selectable actions.
		 */
		class Menu
		{
		public:
			/**
				Inserts the given Action at the given index in the menu.
				\param index The zero-based index to insert at.
				\param action The action to add.
			 */
			void insert(size_t index, Action& action) {}

			/**
				Adds an Action to the Menu.
				\param action The Action to add.
			 */
			void add(Action& action) {}

			/**
				Inserts the given Menu as a sub-menu at the given index in the menu.
				\param index The zero-based index to insert at.
				\param menu The sub-menu to add.
			 */
			void insert(size_t index, Menu& menu) {}

			/**
				Adds a sub-menu to the Menu.
				\param menu The sub-menu to add.
			 */
			void add(Menu& menu) {}
		};
	}
}

#endif // _NATIVE_UI_MENU_H_

