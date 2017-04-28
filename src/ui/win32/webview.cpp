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
		class ActiveXSite : public IOleClientSite, public IOleInPlaceSite
		{
		public:
			// Constructor
			ActiveXSite(WebViewDetail* detail);

			// IUnknown Functions
			virtual HRESULT QueryInterface(REFIID riid, void** ppvObject) override;
			virtual ULONG AddRef()  override { return Atomic::increment(_referenceCount); }
			virtual ULONG Release() override { return Atomic::decrement(_referenceCount); }

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

		private:
			// Instance Variables
			volatile int _referenceCount;
			WebViewDetail* _detail;
		};

		struct WebViewDetail
		{
			WebViewDetail() : site(nullptr), storage(nullptr), webObject(nullptr), browser(nullptr), hwnd(NULL) {}
			~WebViewDetail();

			// Instance Variables
			ActiveXSite*  site;
			IStorage*     storage;
			IOleObject*   webObject;
			IWebBrowser2* browser;
			HWND          hwnd;
		};

		WebView::WebView() : Component(new ComponentAdapter({ this, nullptr, WS_CHILD | WS_VISIBLE, 0 })), _detail(new WebViewDetail)
		{
			setAlignment(Align::Fill);

			ComponentAdapter* adapter = (ComponentAdapter*) getAdapter();

			_detail->hwnd = HWND(adapter->getHandle());
			_detail->site = new ActiveXSite(_detail);

			HRESULT result = ::StgCreateStorageEx(NULL, STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT | STGM_CREATE | STGM_DELETEONRELEASE, STGFMT_STORAGE, 0, NULL, NULL, IID_IStorage, (void**) &_detail->storage);

			result = ::OleCreate(CLSID_WebBrowser, IID_IOleObject, OLERENDER_DRAW, NULL, _detail->site, _detail->storage, (LPVOID*) &_detail->webObject);

			::OleSetContainedObject(_detail->webObject, TRUE);

			RECT rect = { 0 };

			result = _detail->webObject->DoVerb(OLEIVERB_INPLACEACTIVATE, NULL, _detail->site, -1, HWND(adapter->getHandle()), &rect);

			result = _detail->webObject->QueryInterface(IID_IWebBrowser2, (void**) &_detail->browser);

			VARIANT url, empty1, empty2, empty3, empty4;

			url.vt = VT_BSTR;
			url.bstrVal = ::SysAllocString(L"http://www.google.com");

			empty1.vt = empty2.vt = empty3.vt = empty4.vt = VT_EMPTY;

			result = _detail->browser->put_Left(rect.left);
			result = _detail->browser->put_Top(rect.top);
			result = _detail->browser->put_Width(rect.right - rect.left);
			result = _detail->browser->put_Height(rect.bottom - rect.top);
			result = _detail->browser->Navigate2(&url, &empty1, &empty2, &empty3, &empty4);
		}

		WebView::~WebView()
		{
			delete _detail;
		}

		void WebView::onSize(const Size& size)
		{
			_detail->browser->put_Width(size.width);
			_detail->browser->put_Height(size.height);
		}

		/*
			ActiveXSite Functions
		*/

		ActiveXSite::ActiveXSite(WebViewDetail* detail) : _referenceCount(0), _detail(detail) 
		{
			static bool isOleInitialized = false;
			static SpinLock lock;

			lock.lock();

			if (!isOleInitialized)
			{
				isOleInitialized = true;

				::OleInitialize(NULL);

				System::onExit([]() { ::OleUninitialize(); });
			}

			lock.release();
		}

		HRESULT ActiveXSite::QueryInterface(REFIID riid, void** ppvObject)
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

		HRESULT ActiveXSite::GetWindow(HWND* phwnd)
		{
			*phwnd = _detail->hwnd; 
			return S_OK;
		}

		HRESULT ActiveXSite::GetWindowContext(IOleInPlaceFrame** ppFrame, IOleInPlaceUIWindow** ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo)
		{
			*ppFrame = NULL;
			*ppDoc = NULL;
			*lprcPosRect = { 0 };
			*lprcClipRect = *lprcPosRect;

			lpFrameInfo->fMDIApp = FALSE;
			lpFrameInfo->hwndFrame = _detail->hwnd;
			lpFrameInfo->cAccelEntries = 0;

			return S_OK;
		}

		HRESULT ActiveXSite::OnPosRectChange(LPCRECT lprcPosRect)
		{
			IOleInPlaceObject* place = nullptr;

			_detail->webObject->QueryInterface(IID_IOleInPlaceObject, (void**) &place);

			place->SetObjectRects(lprcPosRect, lprcPosRect);

			place->Release();

			return S_OK;
		}

		/*
			WebViewDetail Functions
		*/

		WebViewDetail::~WebViewDetail()
		{
			delete site;
			
			if (storage) storage->Release();
			if (webObject) webObject->Release();
			if (browser) browser->Release();
		}
	}
}

