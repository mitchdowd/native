// External Dependencies
#include "../../../lib/jnipp/jnipp.h"
#include "../../core/include/system.h"

// Local Dependencies
#include "../include/canvas.h"
#include "../include/component.h"

#define HANDLE_OBJ ((jni::Object*) _handle)

namespace native
{
	namespace ui
	{
		Canvas::Canvas(handle_t handle, handle_t auxHandle)
		{
            _handle = new jni::Object(jni::jobject(handle));

            if (auxHandle != nullptr)
                throw InvalidArgumentException();
		}

        Canvas::Canvas(Component& component)
        {
            throw NotImplementedException();
        }

		Canvas::~Canvas()
		{
			// TODO
		}

		void Canvas::fillRectangle(const Rectangle& rect, const Brush& brush)
		{
            Rectangle area = rect.offset(_offset).scale(System::getDisplayScale());
            HANDLE_OBJ->call<void>("drawRect(FFFFLandroid/graphics/Paint;)V", float(area.x), float(area.y), float(area.x + area.width), float(area.y + area.height), (jni::Object*) brush.getHandle());
		}
	}
}

