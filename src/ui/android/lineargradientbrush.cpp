// External Dependencies
#include "../../../lib/jnipp/jnipp.h"

// External Dependencies
#include "../../core/include/exception.h"

// Module Dependencies
#include "../include/lineargradientbrush.h"

namespace native
{
	namespace ui
	{
	    static jni::Object* CreatePaint(Point p0, Point p1, Color c0, Color c1)
        {
            auto constructor = jni::Class("android/graphics/LinearGradient")
                .getConstructor("(FFFFIILandroid/graphics/Shader#TileMode;)V");

            jni::Object shader = jni::Class("android/graphics/LinearGradient").newInstance(
                constructor, float(p0.x), float(p0.y), float(p1.x), float(p1.y),
                int(c0.toArgb()), int(c1.toArgb()), jni::Enum("android/graphics/Shader#TileMode").get("REPEAT"););

            jni::Object paint = jni::Class("android/graphics/Paint").newInstance();

            paint.call<jni::Object>("setShader(Landroid/graphics/Shader;)Landroid/graphics/Shader;", shader);

            return new jni::Object(paint);
        }

		LinearGradientBrush::LinearGradientBrush(Point p0, Point p1, Color c0, Color c1)
		{

		}
	}
}

