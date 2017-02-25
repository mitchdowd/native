#ifndef _NATIVE_UI_EVENT_QUEUE_H_
#define _NATIVE_UI_EVENT_QUEUE_H_ 1

// External Modules
#include "../../core/include/exception.h"

namespace native
{
	namespace ui
	{
		/**
			Allows asynchronous events to the posted and handled in the current
			Thread. In a UI application, the core message loop is encapsulated by
			the EventQueue.

			EventQueues aren't created, so much as used implicitly on a per-Thread
			basis via these static functions.
		 */
		class EventQueue
		{
			// Prevent Creation
			EventQueue() = delete;

		public:
			/**
				Handles a pending event in the current Thread's event queue. It can
				either block and wait for an event handle, or return immediately,
				depending on the parameter specified. More than one event may be
				handled in a single call to handleEvent(), depending on operating
				system functionality.
				\param block Should the function block to wait for an event?
				\return false if a quit event was handled, true otherwise.
			 */
			static bool handleEvent(bool block = true);

			/**
				Posts a quit event, which causes handleEvent() to return false.
				\param exitCode The exit code to send to the quit message.
			 */
			static void quitWithCode(int exitCode);
			static void quit() { quitWithCode(0); }

			/**
				Gets the exit code that was supplied by `quitWithCode()`. Defaults
				to zero if not specified.
				\return The exit code.
			 */
			static int getExitCode() { return _exitCode; }

		private:
			// Static Variables
			static thread_local int _exitCode;
		};


		/**
			EventException indicates there was an error in the EventLoop.
		 */
		class EventException : public Exception
		{
		public:
			EventException(const char* message = "Error processing system event") : Exception(message) {}
		};
	}
}

#endif // _NATIVE_UI_EVENT_QUEUE_H_

