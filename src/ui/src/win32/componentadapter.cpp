// System Dependencies
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <gdiplus.h>

// External Dependencies
#include "../../../core/include/spinlock.h"

// Module Dependencies
#include "../../include/component.h"
#include "../../include/componentadapter.h"

// Local Dependencies
#include "componentadapterproperties.h"
#include "componentevent.h"

// Library Dependencies
#pragma comment(lib, "comctl32.lib")

// Enable newer common controls versions.
#pragma comment(linker,                         \
    "\"/manifestdependency:type='Win32' "       \
    "name='Microsoft.Windows.Common-Controls' " \
    "version='6.0.0.0' "                        \
    "processorArchitecture='*' "                \
    "publicKeyToken='6595b64144ccf1df' "        \
    "language='*'\"")

// Local Constants
#define NATIVE_WINDOW_CLASS_NAME	L"native::ui::Component"

namespace native
{
	namespace ui
	{
		// Static Variables
		static bool _isTouchReady = false;

		/**
			Ensures that functions related to a native ComponentAdapter are
			able to be called, by registering with the underling platform.
		 */
		void ensureApiRegistered();

		ComponentAdapter::ComponentAdapter(const ComponentAdapterProperties& props)
		{
			ensureApiRegistered();

			throw NotImplementedException();
		}

		void ComponentAdapter::setParent(IComponentAdapter* parent_)
		{
			ComponentAdapter* parent = (ComponentAdapter*) parent_;

			// TODO
		}

		void ComponentAdapter::setText(const String& text)
		{

		}

		WindowAdapter::WindowAdapter() : ComponentAdapter({ /* todo */ })
		{
		}

		static void ensureApiRegistered()
		{
			static bool isRegistered = false;
			static SpinLock lock;
			static ULONG_PTR gdiPlusToken = 0;

			lock.lock();

			if (!isRegistered)
			{
				INITCOMMONCONTROLSEX icc = { 0 };
				WNDCLASSEX wc = { 0 };

				// Initialise common control window classes.
				icc.dwSize = sizeof(icc);
				icc.dwICC = ICC_WIN95_CLASSES;
				::InitCommonControlsEx(&icc);

				// Register the main window class.
				wc.cbSize        = sizeof(wc);
				wc.lpfnWndProc   = ComponentEvent::WindowProc;
				wc.hInstance     = ::GetModuleHandle(0);
				wc.hIcon         = ::LoadIcon(0, IDI_APPLICATION);
				wc.hCursor       = ::LoadCursor(0, IDC_ARROW);
				wc.lpszClassName = NATIVE_WINDOW_CLASS_NAME;
				wc.hIconSm       = ::LoadIcon(0, IDI_APPLICATION);
				wc.style         = CS_HREDRAW | CS_VREDRAW;
				wc.hbrBackground = HBRUSH(COLOR_WINDOW + 1);

				::RegisterClassEx(&wc);

				// Check for a touch-screen device.
				if (::GetSystemMetrics(SM_DIGITIZER) & 0x00000080 /* NID_READY */)
					_isTouchReady = true;

				isRegistered = true;
			}

			lock.release();
		}

		LRESULT CALLBACK ComponentEvent::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
		{
			throw NotImplementedException();
		}
	}
}

