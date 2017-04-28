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
		struct BrowserData : public IOleClientSite, public IOleInPlaceSite
		{
			// Constructor
			BrowserData(HWND hwnd);
			~BrowserData();

			// Helper Functions
			void setSize(const Size& size);
			void navigate(const String& url);

			// IUnknown Functions
			virtual HRESULT QueryInterface(REFIID riid, void** ppvObject) override;
			virtual ULONG AddRef()  override { return 1; }	// Unneeded
			virtual ULONG Release() override { return 1; }	// Unneeded

			// IOleClientSite Functions
			virtual HRESULT SaveObject() override { return E_NOTIMPL; }
			virtual HRESULT GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker** ppmk) override { return E_NOTIMPL; }
			virtual HRESULT GetContainer(IOleContainer** ppContainer) override { return E_NOINTERFACE; }
			virtual HRESULT ShowObject() override { return S_OK; }
			virtual HRESULT OnShowWindow(BOOL fShow) override { return E_NOTIMPL; }
			virtual HRESULT RequestNewObjectLayout() override { return E_NOTIMPL; }

			// IOleWindow Functions
			virtual HRESULT GetWindow(HWND* phwnd) override;
			virtual HRESULT ContextSensitiveHelp(BOOL fEnterMode) override { return E_NOTIMPL; }

			// IOleInPlaceSite Functions
			virtual HRESULT CanInPlaceActivate() override { return S_OK; }
			virtual HRESULT OnInPlaceActivate()  override { return S_OK; }
			virtual HRESULT OnUIActivate() override { return S_OK; }
			virtual HRESULT GetWindowContext(IOleInPlaceFrame** ppFrame, IOleInPlaceUIWindow** ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo) override;
			virtual HRESULT Scroll(SIZE scrollExtant) override { return E_NOTIMPL; }
			virtual HRESULT OnUIDeactivate(BOOL fUndoable) override { return S_OK; }
			virtual HRESULT OnInPlaceDeactivate() override { return S_OK; }
			virtual HRESULT DiscardUndoState() override { return E_NOTIMPL; }
			virtual HRESULT DeactivateAndUndo() override { return E_NOTIMPL; }
			virtual HRESULT OnPosRectChange(LPCRECT lprcPosRect) override;

			// Instance Variables
			IStorage*   storage;
			IOleObject* webObject;
			HWND        hwnd;
		};

		/*
			WebView Functions
		 */

		WebView::WebView() : Component(new WebViewAdapter(this))
		{
			setAlignment(Align::Fill);
		}

		void WebView::navigate(const String& url)
		{
			BrowserData* browser = ((WebViewAdapter*) getAdapter())->getBrowserData();

			browser->navigate(url);
		}

		void WebView::onSize(const Size& size)
		{
			BrowserData* browser = ((WebViewAdapter*) getAdapter())->getBrowserData();

			browser->setSize(size);
		}

		/*
			WebViewAdapter Functions
		*/

		WebViewAdapter::WebViewAdapter(WebView* view) : ComponentAdapter({ view, nullptr, WS_CHILD | WS_VISIBLE, 0 })
		{
			_browser = new BrowserData(HWND(getHandle()));
		}

		WebViewAdapter::~WebViewAdapter()
		{
			delete _browser;
		}

		/*
			BrowserData Functions
		*/

		BrowserData::BrowserData(HWND hwnd) : hwnd(hwnd)
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

		BrowserData::~BrowserData()
		{
			if (storage)   storage->Release();
			if (webObject) webObject->Release();
		}

		void BrowserData::setSize(const Size& size)
		{
			IWebBrowser2* browser = nullptr;

			webObject->QueryInterface(IID_IWebBrowser2, (void**) &browser);

			browser->put_Width(size.width);
			browser->put_Height(size.height);

			browser->Release();
		}

		void BrowserData::navigate(const String& url)
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

		HRESULT BrowserData::QueryInterface(REFIID riid, void** ppvObject)
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

		HRESULT BrowserData::GetWindow(HWND* phwnd)
		{
			*phwnd = hwnd; 
			return S_OK;
		}

		HRESULT BrowserData::GetWindowContext(IOleInPlaceFrame** ppFrame, IOleInPlaceUIWindow** ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo)
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

		HRESULT BrowserData::OnPosRectChange(LPCRECT lprcPosRect)
		{
			IOleInPlaceObject* place = nullptr;

			webObject->QueryInterface(IID_IOleInPlaceObject, (void**) &place);

			place->SetObjectRects(lprcPosRect, lprcPosRect);

			place->Release();

			return S_OK;
		}
	}
}

