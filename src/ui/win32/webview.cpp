// System Dependencies
#include <windows.h>
#include <exdisp.h>

// External Dependencies
#include "../../core/include/spinlock.h"
#include "../../core/include/system.h"

// Module Dependencies
#include "componentadapterproperties.h"
#include "../include/componentadapter.h"
#include "../include/webview.h"

namespace native
{
	namespace ui
	{
		class Win32WebViewAdapter : public WebViewAdapter, public IOleClientSite, public IOleInPlaceSite
		{
		public:
			// Constructor
			Win32WebViewAdapter(WebView* view);
			~Win32WebViewAdapter();

			// Helper Functions
			void setSize(const Size& size);
			virtual void navigate(const String& url) override;
			virtual void goBack() override;
			virtual void goForward() override;

			// IUnknown Functions
			virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override;
			virtual ULONG STDMETHODCALLTYPE AddRef()  override { return 1; }	// Unneeded
			virtual ULONG STDMETHODCALLTYPE Release() override { return 1; }	// Unneeded

			// IOleClientSite Functions
			virtual HRESULT STDMETHODCALLTYPE SaveObject() override { return E_NOTIMPL; }
			virtual HRESULT STDMETHODCALLTYPE GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker** ppmk) override { return E_NOTIMPL; }
			virtual HRESULT STDMETHODCALLTYPE GetContainer(IOleContainer** ppContainer) override { return E_NOINTERFACE; }
			virtual HRESULT STDMETHODCALLTYPE ShowObject() override { return S_OK; }
			virtual HRESULT STDMETHODCALLTYPE OnShowWindow(BOOL fShow) override { return E_NOTIMPL; }
			virtual HRESULT STDMETHODCALLTYPE RequestNewObjectLayout() override { return E_NOTIMPL; }

			// IOleWindow Functions
			virtual HRESULT STDMETHODCALLTYPE GetWindow(HWND* phwnd) override;
			virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(BOOL fEnterMode) override { return E_NOTIMPL; }

			// IOleInPlaceSite Functions
			virtual HRESULT STDMETHODCALLTYPE CanInPlaceActivate() override { return S_OK; }
			virtual HRESULT STDMETHODCALLTYPE OnInPlaceActivate()  override { return S_OK; }
			virtual HRESULT STDMETHODCALLTYPE OnUIActivate() override { return S_OK; }
			virtual HRESULT STDMETHODCALLTYPE GetWindowContext(IOleInPlaceFrame** ppFrame, IOleInPlaceUIWindow** ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo) override;
			virtual HRESULT STDMETHODCALLTYPE Scroll(SIZE scrollExtant) override { return E_NOTIMPL; }
			virtual HRESULT STDMETHODCALLTYPE OnUIDeactivate(BOOL fUndoable) override { return S_OK; }
			virtual HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate() override { return S_OK; }
			virtual HRESULT STDMETHODCALLTYPE DiscardUndoState() override { return E_NOTIMPL; }
			virtual HRESULT STDMETHODCALLTYPE DeactivateAndUndo() override { return E_NOTIMPL; }
			virtual HRESULT STDMETHODCALLTYPE OnPosRectChange(LPCRECT lprcPosRect) override;

			// Instance Variables
			IStorage*   storage;
			IOleObject* webObject;
			HWND        hwnd;
		};

		/*
			WebView Functions
		 */

		WebView::WebView() : Component(new Win32WebViewAdapter(this))
		{
			setAlignment(Align::Fill);
		}

		void WebView::navigate(const String& url)
		{
			((WebViewAdapter*) getAdapter())->navigate(url);
		}

		void WebView::goBack()
		{
			((WebViewAdapter*) getAdapter())->goBack();
		}

		void WebView::goForward()
		{
			((WebViewAdapter*) getAdapter())->goForward();
		}

		void WebView::onSize(const Size& size)
		{
			((Win32WebViewAdapter*) getAdapter())->setSize(size);
		}

		/*
			WebViewAdapter Functions
		*/

		WebViewAdapter::WebViewAdapter(WebView* view) : ComponentAdapter({ view, nullptr, WS_CHILD | WS_VISIBLE, 0 })
		{
		}

		WebViewAdapter::~WebViewAdapter()
		{
		}

		void WebViewAdapter::navigate(const String& url)
		{
			// Always overridden.
			throw NotSupportedException();
		}

		void WebViewAdapter::goBack()
		{
			// Always overridden.
			throw NotSupportedException();
		}

		void WebViewAdapter::goForward()
		{
			// Always overridden.
			throw NotSupportedException();
		}

		/*
			Win32WebViewAdapter Functions
		*/

		Win32WebViewAdapter::Win32WebViewAdapter(WebView* view) : WebViewAdapter(view), hwnd(HWND(getHandle()))
		{
			static bool isOleInitialized = false;
			static SpinLock lock;

			lock.lock();

			if (!isOleInitialized)
			{
				// Initialise the ActiveX environment.
				isOleInitialized = true;
				::OleInitialize(NULL);
				System::onExit([]() { ::OleUninitialize(); });
				
				// Get the current process name.
				// TODO: Make this a function elsewhere.
				WCHAR buffer[MAX_PATH + 1];
				::GetModuleFileName(NULL, buffer, sizeof(buffer));
				String fileName = buffer;
				fileName = fileName.substring(fileName.lastIndexOf(L"\\") + 1, fileName.getLength());

				// Ensure we're using a decent browser version.
				HKEY browserEmulationKey;
				DWORD ieVersion = 11000;	// IE11 pretty please.
				::RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_BROWSER_EMULATION", 0, KEY_WRITE, &browserEmulationKey);
				::RegSetValueEx(browserEmulationKey, fileName.toArray(), 0, REG_DWORD, (BYTE*) &ieVersion, sizeof(ieVersion));
				::RegCloseKey(browserEmulationKey);
			}

			lock.release();

			// Create the ActiveX container.
			if (FAILED(::StgCreateStorageEx(NULL, STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT | STGM_CREATE | STGM_DELETEONRELEASE, STGFMT_STORAGE, 0, NULL, NULL, IID_IStorage, (void**)&storage)))
				throw UserInterfaceException("Failed to create ActiveX browser component.");

			if (FAILED(::OleCreate(CLSID_WebBrowser, IID_IOleObject, OLERENDER_DRAW, NULL, this, storage, (LPVOID*) &webObject)))
				throw UserInterfaceException("Failed to create ActiveX browser component.");

			// Embed the ActiveX container in our Component.
			RECT rect = { 0 };
			::OleSetContainedObject(webObject, TRUE);
			webObject->DoVerb(OLEIVERB_INPLACEACTIVATE, NULL, this, -1, hwnd, &rect);
		}

		Win32WebViewAdapter::~Win32WebViewAdapter()
		{
			if (storage)   storage->Release();
			if (webObject) webObject->Release();
		}

		void Win32WebViewAdapter::setSize(const Size& size)
		{
			IWebBrowser2* browser = nullptr;

			webObject->QueryInterface(IID_IWebBrowser2, (void**) &browser);

			browser->put_Width(size.width);
			browser->put_Height(size.height);

			browser->Release();
		}

		void Win32WebViewAdapter::navigate(const String& url)
		{
			IWebBrowser2* browser = nullptr;
			webObject->QueryInterface(IID_IWebBrowser2, (void**) &browser);

			VARIANT vurl, vempty;

			vempty.vt = VT_EMPTY;
			vurl.vt   = VT_BSTR;
			vurl.bstrVal = ::SysAllocString(url.toArray());

			browser->Navigate2(&vurl, &vempty, &vempty, &vempty, &vempty);
			
			browser->Release();
			::SysFreeString(vurl.bstrVal);
		}

		void Win32WebViewAdapter::goBack()
		{
			IWebBrowser2* browser = nullptr;
			webObject->QueryInterface(IID_IWebBrowser2, (void**) &browser);

			browser->GoBack();

			browser->Release();
		}

		void Win32WebViewAdapter::goForward()
		{
			IWebBrowser2* browser = nullptr;
			webObject->QueryInterface(IID_IWebBrowser2, (void**) &browser);

			browser->GoForward();

			browser->Release();
		}

		HRESULT Win32WebViewAdapter::QueryInterface(REFIID riid, void** ppvObject)
		{
			if (riid == IID_IUnknown || riid == IID_IOleClientSite)
			{
				*ppvObject = (IOleClientSite*) this;
			}
			else if (riid == IID_IOleInPlaceSite)
			{
				*ppvObject = (IOleInPlaceSite*) this;
			}
			else
			{
				*ppvObject = NULL;
				return E_NOINTERFACE;
			}

			AddRef();
			return S_OK;
		}

		HRESULT Win32WebViewAdapter::GetWindow(HWND* phwnd)
		{
			*phwnd = hwnd; 
			return S_OK;
		}

		HRESULT Win32WebViewAdapter::GetWindowContext(IOleInPlaceFrame** ppFrame, IOleInPlaceUIWindow** ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo)
		{
			*ppFrame = NULL;
			*ppDoc = NULL;
			*lprcPosRect = { 0 };
			*lprcClipRect = *lprcPosRect;

			lpFrameInfo->fMDIApp = FALSE;
			lpFrameInfo->hwndFrame = hwnd;
			lpFrameInfo->cAccelEntries = 0;

			return S_OK;
		}

		HRESULT Win32WebViewAdapter::OnPosRectChange(LPCRECT lprcPosRect)
		{
			IOleInPlaceObject* place = nullptr;

			webObject->QueryInterface(IID_IOleInPlaceObject, (void**) &place);

			place->SetObjectRects(lprcPosRect, lprcPosRect);

			place->Release();

			return S_OK;
		}
	}
}

