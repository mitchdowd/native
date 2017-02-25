#ifndef _NATIVE_UI_COMPONENT_EVENT_H_
#define _NATIVE_UI_COMPONENT_EVENT_H_ 1

// External Dependencies
#include "../../../core/include/types.h"

namespace native
{
    namespace ui
    {
        /**
            Details of a native event for an Android Component.
         */
        struct ComponentEvent
        {
            enum EventId {
                onInput,
                onPaint,
                onSize
            };

            EventId  id;
            handle_t arg;
        };
    }
}

#endif // _NATIVE_UI_COMPONENT_EVENT_H_


