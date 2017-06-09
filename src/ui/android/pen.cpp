// External Dependencies
#include "../../../lib/jnipp/jnipp.h"

// Module Dependencies
#include "../include/app.h"
#include "../include/pen.h"

namespace native
{
	namespace ui
	{
		Pen::Pen(const Color& color, float thickness) : _shared(nullptr), _thickness(thickness), _color(color)
		{
			jni::Object paint = jni::Class("android/graphics/Paint").newInstance();

			paint.call<void>("setColor", int(color.toArgb()));
            paint.call<void>("setStrokeWidth", thickness * App::getDisplayScale());
            paint.call<void>("setStyle(Landroid/graphics/Paint$Style;)V", jni::Enum("android/graphics/Paint$Style").get("STROKE"));

			_shared->handle = new jni::Object(paint);
		}

		Pen::PenHandle::~PenHandle()
		{
			delete (jni::Object*) handle;
		}
	}
}

