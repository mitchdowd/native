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
		class Menu : public ActionListener
		{
		public:
			/** Creates a Menu. */
			Menu();

			/** Destructor. Destroys the Menu */
			~Menu();

			/**
				Inserts the given Action at the given index in the menu.
				\param index The zero-based index to insert at.
				\param action The action to add.
			 */
			void insert(size_t index, Action& action);

			/**
				Inserts a separator at the given index in the Menu.
				\param index The zero-based index to insert at.
			 */
			void insertSeparator(size_t index);

			/**
				Adds an Action to the Menu.
				\param action The Action to add.
			 */
			void add(Action& action) { insert(~0, action); }

			/** Appends a separator to the end of this Menu. */
			void addSeparator() { insertSeparator(~0); }

			/**
				Inserts the given Menu as a sub-menu at the given index in the menu.
				\param index The zero-based index to insert at.
				\param menu The sub-menu to add.
			 */
			void insert(size_t index, Menu& menu);

			/**
				Adds a sub-menu to the Menu.
				\param menu The sub-menu to add.
			 */
			void add(Menu& menu) { insert(~0, menu); }

			/**
				Sets the Menu's text.
				\param text The text to set.
			 */
			void setText(const String& text);

			/**
				Gets the Menu's label text.
				\return The menu text.
			 */
			String getText() const { return _text; }

			/**
				Retrieves the system handle for this Menu.
				\return The system handle.
			 */
			handle_t getHandle() const noexcept { return _handle; }

		protected:
			// Action Listeners
			virtual void onActionUpdated(Action* action) override;
			virtual void onActionDestroyed(Action* action) override;

		private:
			// Prevent Copying
			Menu(const Menu&) = delete;

			// Instance Variables
			handle_t _handle;
			String _text;
		};
	}
}

#endif // _NATIVE_UI_MENU_H_

