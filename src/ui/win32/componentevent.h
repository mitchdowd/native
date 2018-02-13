#ifndef _NATIVE_UI_COMPONENT_EVENT_H_
#define _NATIVE_UI_COMPONENT_EVENT_H_ 1

// System Dependencies
#include <Windows.h>

namespace native
{
	namespace ui
	{
		/**
			Details of a native event for a HWND in Win32.
		*/
		struct ComponentEvent
		{
			HWND    hwnd;
			UINT    msg;
			WPARAM  wparam;
			LPARAM  lparam;
			LRESULT result;

			/** This is the main callback for all Win32 Window events. */
			static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		};
	}
}

#endif // _NATIVE_UI_COMPONENT_EVENT_H_

