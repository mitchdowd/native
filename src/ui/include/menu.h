#ifndef _NATIVE_UI_MENU_H_
#define _NATIVE_UI_MENU_H_ 1

// Module Dependencies
#include "action.h"
#include "imenuadapter.h"

namespace native
{
	namespace ui
	{
		// Forward Declarations
		class Component;
        class MenuAdapter;

		/**
			A displayable menu of selectable actions.
		 */
		class Menu : public ActionListener
		{
		public:
			/** Creates a Menu. */
			Menu();

			/**
				Creates a Menu which encapsulates the given menu adapter.
			 */
			Menu(IMenuAdapter* adapter);

			// Prevent Copying
			Menu(const Menu&) = delete;

			/** Destructor. Destroys the Menu */
			virtual ~Menu();

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
                Gets this Menu's parent menu, if it has one.
                \return The parent menu if this is a submenu, or null.
             */
			Menu* getParent() const noexcept { return _parent; }

			/**
				Gets a unique numerical ID for this Menu.
			 	\return The Menu ID.
			 */
			int32_t getId() const noexcept { return _id; }

            /**
                Sets the adapter used by this Menu.
                \param adapter The new menu adapter.
             */
            void setAdapter(IMenuAdapter* adapter) { _adapter = adapter; }

			/**
				Gets the adapter which provides platform-dependent functionality.
				\return The underlying menu adapter.
			 */
			IMenuAdapter* getAdapter() const noexcept { return _adapter; }

		protected:
			// Action Listeners
			virtual void onActionUpdated(Action* action) override;
			virtual void onActionDestroyed(Action* action) override;
            virtual void onHierarchyUpdate();

            // Internal Types
            enum class MenuItemType { Menu, Action, Separator };

            struct MenuItem
            {
                MenuItem(Menu* menu) : type(MenuItemType::Menu), menu(menu) {}
                MenuItem(Action* action) : type(MenuItemType::Action), action(action) {}
                MenuItem() : type(MenuItemType::Separator), menu(nullptr) {}

                bool operator==(const MenuItem& item) const { return type == item.type && menu == item.menu; }

                MenuItemType type;
                union {
                    Menu* menu;
                    Action* action;
                };
            };

            // Perhaps this could be useful being public?
            const List<MenuItem>& getChildren() const { return _children; }

		private:
            // Class Friendships
            friend class MenuAdapter;

			// Instance Variables
			IMenuAdapter* _adapter;
			String        _text;
			int32_t       _id;

			// Hierarchy Stuff
			Menu* _parent;
			List<MenuItem> _children;
		};
	}
}

#endif // _NATIVE_UI_MENU_H_

