#ifndef _NATIVE_UI_SCROLL_VIEW_H_
#define _NATIVE_UI_SCROLL_VIEW_H_ 1

// Local Dependencies
#include "layoutcomponent.h"

namespace native
{
    namespace ui
    {
        class ScrollView : public LayoutComponent
        {
        public:
            ScrollView();

		protected:
			virtual void onSize(const Size& size) override;
        };
    }
}

#endif // _NATIVE_UI_SCROLL_VIEW_H_

