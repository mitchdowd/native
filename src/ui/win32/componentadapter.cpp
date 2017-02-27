// System Dependencies
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <gdiplus.h>

// External Dependencies
#include "../../core/include/spinlock.h"
#include "../../core/include/system.h"

// Module Dependencies
#include "../include/canvas.h"
#include "../include/component.h"
#include "../include/componentadapter.h"
#include "../include/window.h"

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

		/**
			A child Window must have a parent. In order to still have a default
			constructor for class Component, we create a default HWND to hold those
			orphaned children.
		 */
		HWND getDefaultParent();

		ComponentAdapter::ComponentAdapter(const ComponentAdapterProperties& props) : _component(props.component)
		{
			ensureApiRegistered();

			// Create the Window handle.
			_handle = ::CreateWindowEx(props.exStyle, props.className ? props.className : NATIVE_WINDOW_CLASS_NAME,
				L"", props.style, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				(props.style & WS_CHILD) ? getDefaultParent() : NULL, NULL, ::GetModuleHandle(0), NULL);

			if (_handle == NULL)
				throw UserInterfaceException("CreateWindowEx");

			// Intercept messages that do not have our WindowProc specified.
			if (::GetClassLongPtr(HWND(_handle), GCLP_WNDPROC) != LONG_PTR(ComponentEvent::WindowProc))
				::SetWindowLongPtr(HWND(_handle), GWLP_WNDPROC, LONG_PTR(ComponentEvent::WindowProc));

			// Set the default GUI font.
			// ::SendMessage(HWND(_handle), WM_SETFONT, WPARAM(Font::getDefault().getAuxHandle()), TRUE);

			if (_isTouchReady)
			{
				// Register as a touch window.
				::RegisterTouchWindow(HWND(_handle), TWF_WANTPALM);
			}

			// Allow access of the adapter via its handle.
			::SetWindowLongPtr(HWND(_handle), GWLP_USERDATA, LONG_PTR(this));
		}

		void ComponentAdapter::setParent(IComponentAdapter* parent)
		{
			DWORD style = ::GetWindowLong(HWND(_handle), GWL_STYLE);

			if (parent)
				style = (style | WS_CHILD) & ~WS_POPUP;
			else
				style = (style | WS_POPUP) & ~WS_CHILD;

			::SetWindowLong(HWND(_handle), GWL_STYLE, style);

			if (::SetParent(HWND(_handle), HWND(parent ? ((ComponentAdapter*) parent)->_handle : NULL)) == NULL)
				throw UserInterfaceException("SetParent()");
		}

		ComponentAdapter::~ComponentAdapter()
		{
			::DestroyWindow(HWND(_handle));
		}

		void ComponentAdapter::setVisible(bool visible)
		{
			::ShowWindow(HWND(_handle), visible ? SW_SHOW : SW_HIDE);
		}

		bool ComponentAdapter::isVisible() const
		{
			return ::IsWindowVisible(HWND(_handle)) != FALSE;
		}

		void ComponentAdapter::setArea(const Rectangle& area)
		{
			if (::SetWindowPos(HWND(_handle), NULL, area.x, area.y, area.width, area.height, SWP_NOZORDER) == 0)
				throw UserInterfaceException("SetWindowPos() failed");
		}

		Rectangle ComponentAdapter::getContentArea() const
		{
			RECT client, window;

			::GetClientRect(HWND(_handle), &client);
			::GetWindowRect(HWND(_handle), &window);
			::MapWindowPoints(HWND(_handle), NULL, LPPOINT(&client), sizeof(RECT) / sizeof(POINT));
			::OffsetRect(&client, -window.left, -window.top);

			return { client.left, client.top, client.right - client.left, client.bottom - client.top };
		}

		void ComponentAdapter::setText(const String& text)
		{
			::SetWindowText(HWND(_handle), text.toArray());
		}

		void ComponentAdapter::doPaint(Canvas& canvas)
		{
			LONG_PTR baseProc = ::GetClassLongPtr(HWND(_handle), GCLP_WNDPROC);

			if (baseProc != LONG_PTR(ComponentEvent::WindowProc))
			{
				// Call paint process of the native control.
				::CallWindowProc(WNDPROC(baseProc), HWND(_handle), WM_PRINTCLIENT, WPARAM(canvas.getAuxHandle()), 0);
			}
			else if (_component->getBackground().getHandle())
			{
				canvas.fillRectangle(_component->getContentArea().getSize(), _component->getBackground());
			}
		}

		ComponentAdapter* ComponentAdapter::fromHandle(handle_t handle)
		{
			return (ComponentAdapter*) ::GetWindowLongPtr(HWND(handle), GWLP_USERDATA);
		}

		void ComponentAdapter::onEvent(ComponentEvent& event)
		{
			LONG_PTR baseProc = ::GetClassLongPtr(event.hwnd, GCLP_WNDPROC);

			switch (event.msg)
			{
			case WM_DESTROY:
				_handle = nullptr;
				break;

			case WM_PAINT:
				if (::GetUpdateRect(event.hwnd, NULL, FALSE) != 0)
				{
					PAINTSTRUCT ps = { 0 };

					HDC hdc = ::BeginPaint(event.hwnd, &ps);

					{
						// TODO: Dispatch the paint messages.
						Gdiplus::Graphics graphics = hdc;
						Canvas canvas(&graphics, hdc);

						_component->dispatchPaintEvent(canvas);
					}

					::EndPaint(event.hwnd, &ps);
					return;
				}
				break;

			case WM_SIZE:
				{
					RECT rect;

					::GetWindowRect(HWND(_handle), &rect);

					// Ensure the new size is properly reflected in the Component.
					Rectangle area = _component->getArea();
					area.setSize({ rect.right - rect.left, rect.bottom - rect.top });

					_component->updateArea(area);
				}
				break;
			}

			// Check for inherited window proc.
			if (baseProc != LONG_PTR(ComponentEvent::WindowProc)) {
				event.result = ::CallWindowProc(WNDPROC(baseProc), event.hwnd, event.msg, event.wparam, event.lparam);
				return;
			}

			// Everything else...  not handled.
			event.result = ::DefWindowProc(event.hwnd, event.msg, event.wparam, event.lparam);
		}

		/*
			WindowAdapter Functions
		*/

		WindowAdapter::WindowAdapter(Window* window) : ComponentAdapter({ window, nullptr, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 0 })
		{
		}

		void WindowAdapter::setText(const String& text)
		{
			ComponentAdapter::setText(text);
		}

		/*
			TextComponentAdapter Functions
		*/

		TextComponentAdapter::TextComponentAdapter() : ComponentAdapter({ nullptr, 0, 0 })
		{
		}

		/*
			Local Functions
		 */

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
				wc.cbSize        =   sizeof(wc);
				wc.lpfnWndProc   =   ComponentEvent::WindowProc;
				wc.hInstance     = ::GetModuleHandle(0);
				wc.hIcon         = ::LoadIcon(0, IDI_APPLICATION);
				wc.hCursor       = ::LoadCursor(0, IDC_ARROW);
				wc.lpszClassName =   NATIVE_WINDOW_CLASS_NAME;
				wc.hIconSm       = ::LoadIcon(0, IDI_APPLICATION);
				wc.style         =   CS_HREDRAW | CS_VREDRAW;

				::RegisterClassEx(&wc);

				// Check for a touch-screen device.
				if (::GetSystemMetrics(SM_DIGITIZER) & 0x00000080 /* NID_READY */)
					_isTouchReady = true;

				isRegistered = true;
			}

			lock.release();
		}

		static HWND getDefaultParent()
		{
			static HWND hwnd = NULL;
			static SpinLock lock;

			if (!hwnd)
			{
				lock.lock();

				if (!hwnd)
				{
					ensureApiRegistered();

					// Create a top-level HWND to hold orphan children.
					HWND handle = hwnd = ::CreateWindowEx(0, NATIVE_WINDOW_CLASS_NAME, L"", 0, 0, 0, 0, 0, NULL, NULL, ::GetModuleHandle(0), NULL);
					System::onExit([=]() { ::DestroyWindow(hwnd); });
				}

				lock.release();
			}

			if (!hwnd)
				throw UserInterfaceException("Could not create default HWND");

			return hwnd;
		}

		LRESULT CALLBACK ComponentEvent::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
		{
			ComponentAdapter* adapter = ComponentAdapter::fromHandle(hwnd);

			if (adapter)
			{
				ComponentEvent event = { hwnd, msg, wparam, lparam, 0 };

				adapter->onEvent(event);
				return event.result;
			}

			// Check for inherited window proc.
			LONG_PTR baseProc = ::GetClassLongPtr(hwnd, GCLP_WNDPROC);
			if (baseProc != LONG_PTR(ComponentEvent::WindowProc))
				return ::CallWindowProc(WNDPROC(baseProc), hwnd, msg, wparam, lparam);

			return ::DefWindowProc(hwnd, msg, wparam, lparam);
		}
	}
}

