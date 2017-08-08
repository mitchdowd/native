#ifndef _NATIVE_UI_ACTION_H_
#define _NATIVE_UI_ACTION_H_ 1

// External Dependencies
#include "../../core/include/set.h"
#include "../../core/include/signal.h"
#include "../../core/include/string.h"

namespace native
{
	namespace ui
	{
		// Forward Declarations
		class Action;

		/**
			ActionListeners are those classes which are interested if an Action
			is updated or deleted. These are generally the UI classes which display
			Actions, and need to update their display according to the Action updates.
		 */
		class ActionListener
		{
		public:
			/**
				Unregisters this listener from all Actions it is subscribed to during
				destruction.
			 */
			virtual ~ActionListener();

		protected:
			/**
				Called when when an Action's details (text, etc) are updated and
				this listener is subscribed to its updates.
				\param action The Action which was updated.
			 */
			virtual void onActionUpdated(Action* action) = 0;

			/**
				Called when when an Action is being destroyed and this listener is
				subscribed to its updates.
				\param action The Action which is being destroyed.
			 */
			virtual void onActionDestroyed(Action* action) = 0;

			// Class Friendships
			friend class Action;

		private:
			// Instance Variables
			Set<Action*> _actions;
		};

		/**
			An action which the end user can trigger by clicking a display item
			such as a menu item or toolbar button.
		 */
		class Action : public Signal<>
		{
		public:
			/** Default constructor. */
			Action();

			/** Destructor. Disconnects all listeners when destroyed. */
			~Action();

			/**
				Sets the displayable label text for this Action.
				\param text The new text to display.
			 */
			void setText(const String& text);

			/**
				Gets the Action's display text.
				\return The action text.
			 */
			String getText() const { return _text; }

			/**
				Adds an ActionListener which should get notifications about updates
				to this Action. If you only want to receive notifications on when
				the Action is _triggered_, use `connect` instead.
				\param listener The Action listener to register.
			 */
			void addListener(ActionListener* listener);

			/**
				Gets an Action via its handle. Used for implementation purposes.
				\param handle The handle of the Action.
				\return The Action with that handle, or null.
			 */
			static Action* fromHandle(handle_t handle);

			/**
				Gets the underlying handle for this Action.
				\return The system resource handle.
			 */
			handle_t getHandle() const noexcept { return _handle; }

		private:
			// Class Friendships
			friend class ActionListener;

			// Instance Variables
			handle_t _handle;
			String _text;
			Set<ActionListener*> _listeners;
		};
	}
}

#endif // _NATIVE_UI_ACTION_H_

