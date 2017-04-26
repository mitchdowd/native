// System Dependencies
#include <windows.h>

// External Dependencies
#include "../../core/include/spinlock.h"
#include "../../core/include/system.h"

// Module Dependencies
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
			virtual HRESULT GetWindowContext(IOleInPlaceFrame** ppFrame, IOleInPlaceUIWindow** ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo) override { return E_NOTIMPL; }
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

		WebView::WebView() : Component()
		{
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
	}
}

