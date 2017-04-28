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
			ActiveXSite(HWND parent);

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
			virtual HRESULT GetWindow(HWND* phwnd) override { *phwnd = _parent; return S_OK; }
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
			virtual HRESULT OnPosRectChange(LPCRECT lprcPosRect) override { return S_OK; }

		private:
			// Instance Variables
			volatile int _referenceCount;
			HWND _parent;
		};

		WebView::WebView() : Component(new ComponentAdapter({ this, nullptr, WS_CHILD | WS_VISIBLE, 0 }))
		{
			setAlignment(Align::Fill);

			ComponentAdapter* adapter = (ComponentAdapter*) getAdapter();

			ActiveXSite* site = new ActiveXSite(HWND(adapter->getHandle()));
			IStorage* storage = NULL;
			IOleObject* webObject = NULL;
			IWebBrowser2* browser = NULL;

			HRESULT result = ::StgCreateStorageEx(NULL, STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT | STGM_CREATE, STGFMT_STORAGE, 0, NULL, NULL, IID_IStorage, (void**) &storage);

			result = ::OleCreate(CLSID_WebBrowser, IID_IOleObject, OLERENDER_DRAW, NULL, site, storage, (LPVOID*) &webObject);

			::OleSetContainedObject(webObject, TRUE);

			RECT rect = { 0, 0, 300, 300 };

			result = webObject->DoVerb(OLEIVERB_INPLACEACTIVATE, NULL, site, -1, HWND(adapter->getHandle()), &rect);

			result = webObject->QueryInterface(IID_IWebBrowser2, (void**) &browser);

			VARIANT url, empty1, empty2, empty3, empty4;

			url.vt = VT_BSTR;
			url.bstrVal = ::SysAllocString(L"http://www.google.com");

			empty1.vt = empty2.vt = empty3.vt = empty4.vt = VT_EMPTY;

			result = browser->put_Left(rect.left);
			result = browser->put_Top(rect.top);
			result = browser->put_Width(rect.right - rect.left);
			result = browser->put_Height(rect.bottom - rect.top);

			result = browser->Navigate2(&url, &empty1, &empty2, &empty3, &empty4);
		}

		/*
			ActiveXSite Functions
		*/

		ActiveXSite::ActiveXSite(HWND parent) : _referenceCount(0), _parent(parent) 
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

		HRESULT ActiveXSite::GetWindowContext(IOleInPlaceFrame** ppFrame, IOleInPlaceUIWindow** ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo)
		{
			*ppFrame = NULL;
			*ppDoc = NULL;
			lprcPosRect->left = 0;
			lprcPosRect->right = 300;
			lprcPosRect->top = 0;
			lprcPosRect->bottom = 300;
			*lprcClipRect = *lprcPosRect;

			lpFrameInfo->fMDIApp = FALSE;
			lpFrameInfo->hwndFrame = _parent;
			lpFrameInfo->cAccelEntries = 0;

			return S_OK;
		}
	}
}

