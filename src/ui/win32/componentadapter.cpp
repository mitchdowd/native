// System Dependencies
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <gdiplus.h>
#include <versionhelpers.h>

// External Dependencies
#include "../../core/include/spinlock.h"
#include "../../core/include/system.h"

// Module Dependencies
#include "../include/app.h"
#include "../include/button.h"
#include "../include/canvas.h"
#include "../include/checkbox.h"
#include "../include/component.h"
#include "../include/componentadapter.h"
#include "../include/inputcomponent.h"
#include "../include/radiobutton.h"
#include "../include/textcomponent.h"
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

// Custom Messages
#define WM_INVOKE_ASYNC WM_USER

// Local Macros
#define IS_TOUCH_EVENT() ((::GetMessageExtraInfo() & 0xFF515700) == 0xFF515700)

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

		/**
			Gets the default UI font to apply to Components.
		 */
		HFONT getDefaultFont();

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
			::SendMessage(HWND(_handle), WM_SETFONT, WPARAM(getDefaultFont()), TRUE);

			if (_isTouchReady)
			{
				// Register as a touch window.
				::RegisterTouchWindow(HWND(_handle), TWF_WANTPALM);
			}

			// Allow access of the adapter via its handle.
			::SetWindowLongPtr(HWND(_handle), GWLP_USERDATA, LONG_PTR(this));
		}

		ComponentAdapter::ComponentAdapter(handle_t handle, Component* component)
			: _handle(handle), _component(component)
		{
			// TODO
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

		void ComponentAdapter::setEnabled(bool enable)
		{
			::EnableWindow(HWND(_handle), enable ? TRUE : FALSE);
		}

		void ComponentAdapter::setArea(const Rectangle& area)
		{
			if (::SetWindowPos(HWND(_handle), NULL, area.x, area.y, area.width, area.height, SWP_NOZORDER) == 0)
				throw UserInterfaceException("SetWindowPos() failed");
		}

		Rectangle ComponentAdapter::getArea() const
		{
			RECT area;

			::GetWindowRect(HWND(_handle), &area);

			return { area.left, area.top, area.right - area.left, area.bottom - area.top };
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

		void ComponentAdapter::setFont(const Font& font)
		{
			::SendMessage(HWND(_handle), WM_SETFONT, WPARAM(font.getAuxHandle()), FALSE);
		}

		void ComponentAdapter::doInput(const InputEvent& event)
		{
			if (!event.nativeEvent)
				return;

			LONG_PTR baseProc = ::GetClassLongPtr(HWND(_handle), GCLP_WNDPROC);

			if (baseProc != LONG_PTR(ComponentEvent::WindowProc))
			{
				// Call paint process of the native control.
				::CallWindowProc(WNDPROC(baseProc), HWND(_handle), event.nativeEvent->msg, event.nativeEvent->wparam, event.nativeEvent->lparam);
			}
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

		void ComponentAdapter::invokeAsync(const Function<void>& func)
		{
			::PostMessage(HWND(_handle), WM_INVOKE_ASYNC, 0, (LPARAM) new Function<void>(func));
		}

		ComponentAdapter* ComponentAdapter::fromHandle(handle_t handle)
		{
			return (ComponentAdapter*) ::GetWindowLongPtr(HWND(handle), GWLP_USERDATA);
		}

		void ComponentAdapter::onEvent(ComponentEvent& event)
		{
			LONG_PTR baseProc = ::GetClassLongPtr(event.hwnd, GCLP_WNDPROC);

			if (_component == nullptr)
				throw InvalidStateException("Adapter without a Component.");

			switch (event.msg)
			{
			case WM_CTLCOLORSTATIC:
				{
					ComponentAdapter* label = ComponentAdapter::fromHandle(handle_t(event.lparam));

					if (label && label->_component)
					{
						Color bg = label->_component->getBackground().getPrimaryColor();

						// Apply the background color to the static control's device context.
						::SetBkColor(HDC(event.wparam), RGB(bg.red, bg.green, bg.blue));
						return;
					}
					break;
				}

			case WM_DESTROY:
				_handle = nullptr;
				break;

			case WM_INVOKE_ASYNC:	// WM_USER
				if (event.lparam)
				{
					Function<void>* func = (Function<void>*) event.lparam;

					func->invoke();
					delete func;
				}
				break;

			case WM_LBUTTONDOWN:
				if (!IS_TOUCH_EVENT())
					_component->dispatchInputEvent({ InputEvent::Press, InputEvent::LeftButton, GET_X_LPARAM(event.lparam), GET_Y_LPARAM(event.lparam), &event });
				return;

			case WM_LBUTTONUP:
				if (!IS_TOUCH_EVENT())
					_component->dispatchInputEvent({ InputEvent::Release, InputEvent::LeftButton, GET_X_LPARAM(event.lparam), GET_Y_LPARAM(event.lparam), &event });
				return;

			case WM_MBUTTONDOWN:
				if (!IS_TOUCH_EVENT())
					_component->dispatchInputEvent({ InputEvent::Press, InputEvent::MiddleButton, GET_X_LPARAM(event.lparam), GET_Y_LPARAM(event.lparam), &event });
				return;

			case WM_MBUTTONUP:
				if (!IS_TOUCH_EVENT())
					_component->dispatchInputEvent({ InputEvent::Release, InputEvent::MiddleButton, GET_X_LPARAM(event.lparam), GET_Y_LPARAM(event.lparam), &event });
				return;

			case WM_MOUSEMOVE:
				if (!IS_TOUCH_EVENT())
					_component->dispatchInputEvent({ InputEvent::Motion, InputEvent::Mouse, GET_X_LPARAM(event.lparam), GET_Y_LPARAM(event.lparam), &event });
				return;

			case WM_MOVE:
				if (!_component->getParent())
				{
					RECT rect;

					::GetWindowRect(HWND(_handle), &rect);

					// Ensure the new position is properly reflected in the Component.
					_component->_area.setPosition({ rect.left, rect.top });
				}
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

			case WM_RBUTTONDOWN:
				if (!IS_TOUCH_EVENT())
					_component->dispatchInputEvent({ InputEvent::Press, InputEvent::RightButton, GET_X_LPARAM(event.lparam), GET_Y_LPARAM(event.lparam), &event });
				return;

			case WM_RBUTTONUP:
				if (!IS_TOUCH_EVENT())
					_component->dispatchInputEvent({ InputEvent::Release, InputEvent::RightButton, GET_X_LPARAM(event.lparam), GET_Y_LPARAM(event.lparam), &event });
				return;

			case WM_SIZE:
				if (_component->_parent == nullptr)
				{
					RECT rect;

					::GetWindowRect(HWND(_handle), &rect);
					Size size(rect.right - rect.left, rect.bottom - rect.top);
					Size client(GET_X_LPARAM(event.lparam), GET_Y_LPARAM(event.lparam));

					// Ensure the new size is properly reflected in the Component.
					_component->_area.setSize(size.scale(1.0f / App::getDisplayScale()));
					_component->onSize(client.scale(1.0f / App::getDisplayScale()));
				}
				break;

			case WM_TOUCH:
			{
				uint16_t    count = LOWORD(event.wparam);
				HTOUCHINPUT hinput = HTOUCHINPUT(event.lparam);
				TOUCHINPUT  inputs[MAX_TOUCH_COUNT];

				// Get information on the current "touch".
				if (!::GetTouchInputInfo(hinput, count, inputs, sizeof(TOUCHINPUT)))
					break;

				for (int i = 0; i < count; ++i)
				{
					if ((inputs[i].dwFlags & TOUCHEVENTF_PRIMARY) == 0)
						continue;

					InputEvent::Action action;

					if (inputs[i].dwFlags & TOUCHEVENTF_MOVE)
						action = InputEvent::Motion;
					else if (inputs[i].dwFlags & TOUCHEVENTF_DOWN)
						action = InputEvent::Press;
					else if (inputs[i].dwFlags & TOUCHEVENTF_UP)
						action = InputEvent::Release;
					else
						continue;

					POINT pt = { inputs[i].x / 100, inputs[i].y / 100 };
					::ScreenToClient(event.hwnd, &pt);
					_component->dispatchInputEvent({ action, InputEvent::Touch, pt.x, pt.y });
				}

				::CloseTouchInputHandle(hinput);
				return;
			}

			case WM_XBUTTONDOWN:
				if (!IS_TOUCH_EVENT())
					_component->dispatchInputEvent({ InputEvent::Press, HIWORD(event.wparam) == XBUTTON1 ? InputEvent::BackButton : InputEvent::ForwardButton, GET_X_LPARAM(event.lparam), GET_Y_LPARAM(event.lparam), &event });
				return;

			case WM_XBUTTONUP:
				if (!IS_TOUCH_EVENT())
					_component->dispatchInputEvent({ InputEvent::Release, HIWORD(event.wparam) == XBUTTON1 ? InputEvent::BackButton : InputEvent::ForwardButton, GET_X_LPARAM(event.lparam), GET_Y_LPARAM(event.lparam), &event });
				return;
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

		void WindowAdapter::setArea(const Rectangle& area)
		{
			ComponentAdapter::setArea(area);
		}

		void WindowAdapter::setText(const String& text)
		{
			ComponentAdapter::setText(text);
		}

		/*
			TextComponentAdapter Functions
		*/

		TextComponentAdapter::TextComponentAdapter(TextComponent* component) 
			: ComponentAdapter({ component, nullptr, WS_CHILD | WS_VISIBLE, 0 })
		{
		}

		void TextComponentAdapter::setText(const String& text)
		{
			ComponentAdapter::setText(text);
		}

		void TextComponentAdapter::setFont(const Font& font)
		{
			ComponentAdapter::setFont(font);
		}

		/*
			ButtonAdapter Functions
		 */

		ButtonAdapter::ButtonAdapter(Button* button) 
			: ComponentAdapter({ button, L"BUTTON", WS_CHILD | WS_VISIBLE, 0 })
		{
		}

		void ButtonAdapter::setText(const String& text)
		{
			ComponentAdapter::setText(text);
		}

		void ButtonAdapter::setFont(const Font& font)
		{
			ComponentAdapter::setFont(font);
		}

		/*
			CheckboxAdapter Functions
		 */

		CheckboxAdapter::CheckboxAdapter(Checkbox* checkbox)
			: ComponentAdapter({ checkbox, L"BUTTON", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 0 })
		{
		}

		void CheckboxAdapter::setText(const String& text)
		{
			ComponentAdapter::setText(text);
		}

		void CheckboxAdapter::setFont(const Font& font)
		{
			ComponentAdapter::setFont(font);
		}

		void CheckboxAdapter::setChecked(bool checked)
		{
			::SendMessage(HWND(getHandle()), BM_SETCHECK, checked ? BST_CHECKED : BST_UNCHECKED, 0);
		}

		/*
			RadioButtonAdapter Functions
		 */

		RadioButtonAdapter::RadioButtonAdapter(RadioButton* radio)
			: ComponentAdapter({ radio, L"BUTTON", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 0 })
		{
		}

		void RadioButtonAdapter::setText(const String& text)
		{
			ComponentAdapter::setText(text);
		}

		void RadioButtonAdapter::setFont(const Font& font)
		{
			ComponentAdapter::setFont(font);
		}

		void RadioButtonAdapter::setChecked(bool checked)
		{
			::SendMessage(HWND(getHandle()), BM_SETCHECK, checked ? BST_CHECKED : BST_UNCHECKED, 0);
		}

		/*
			InputAdapter Functions
		 */

		InputAdapter::InputAdapter(InputComponent* input)
			: ComponentAdapter({ input, L"EDIT", WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_WANTRETURN | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 0 })
		{
		}

		void InputAdapter::setText(const String& text)
		{
			ComponentAdapter::setText(text);
		}

		void InputAdapter::setFont(const Font& font)
		{
			ComponentAdapter::setFont(font);
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

		static HFONT getDefaultFont()
		{
			static HFONT font = NULL;
			static SpinLock lock;

			lock.lock();

			if (font == NULL)
			{
				font = HFONT(Font::getDefault().getAuxHandle());
			}

			lock.release();

			return font;
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

