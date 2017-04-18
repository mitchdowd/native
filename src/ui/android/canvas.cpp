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

		Canvas::~Canvas()
		{
			delete (jni::Object*) _handle;
		}

		void Canvas::drawText(const String& text, const Font& font, const Point& point)
        {
        	if (text.getLength() > 0)
        	{
	            // Calculate the real co-ordinates.
	            float x = float(_offset.x + point.x) * System::getDisplayScale();
	            float y = float(_offset.y + point.y + font.getSize()) * System::getDisplayScale();

	            // Set up the paint to draw the text with.
	            Brush brush = Color();
	            jni::Object* paint = (jni::Object*) brush.getHandle();
	            paint->call<void>("setTextSize", font.getSize() * System::getDisplayScale());
	            paint->call<jni::Object>("setTypeface(Landroid/graphics/Typeface;)Landroid/graphics/Typeface;", (jni::Object*) font.getHandle());

	            HANDLE_OBJ->call<void>("drawText(Ljava/lang/String;FFLandroid/graphics/Paint;)V", text.toArray(), x, y, paint);
	        }
        }

		void Canvas::drawRectangle(const Rectangle& rect, const Pen& pen)
		{
			jni::Object* penObj = (jni::Object*) pen.getHandle();
			Rectangle area = rect.offset(_offset).deflate(pen.getThickness() / 2).scale(System::getDisplayScale());

			HANDLE_OBJ->call<void>("drawRect(FFFFLandroid/graphics/Paint;)V", float(area.x), float(area.y), float(area.x + area.width), float(area.y + area.height), penObj);
		}

		void Canvas::fillRectangle(const Rectangle& rect, const Brush& brush)
		{
            Rectangle area = rect.offset(_offset).scale(System::getDisplayScale());
            HANDLE_OBJ->call<void>("drawRect(FFFFLandroid/graphics/Paint;)V", float(area.x), float(area.y), float(area.x + area.width), float(area.y + area.height), (jni::Object*) brush.getHandle());
		}
	}
}

