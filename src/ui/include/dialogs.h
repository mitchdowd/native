#ifndef _NATIVE_UI_DIALOGS_H_
#define _NATIVE_UI_DIALOGS_H_ 1

// Module Dependencies
#include "component.h"

namespace native
{
	namespace ui
	{
		/**
			A set of predefined dialog popups for capturing and displaying common
			bits of information in an application.
		 */
		class Dialogs
		{
		public:
			/**
				Displays a message box over the given Component, with a message
				and a title, along with an OK button to dismiss the message.
				\param owner The owner Component to display over.
				\param message The message to display.
				\param title The title at the top of the message box.
			 */
			static void messageBox(Component* owner, const String& message, const String& title);
			static void messageBox(Component& owner, const String& message, const String& title) { messageBox(&owner, message, title); }

			/**
				Displays a message box with the given message and title, along
				with an OK button to dismiss the message.
				\param message The message to display.
				\param title The title at the top of the message box.
			 */
			static void messageBox(const String& message, const String& title);
		};
	}
}

#endif // _NATIVE_UI_DIALOGS_H_

