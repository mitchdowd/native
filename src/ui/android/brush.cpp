// External Dependencies
#include "../../../lib/jnipp/jnipp.h"

// External Dependencies
#include "../../core/include/exception.h"

// Module Dependencies
#include "../include/brush.h"

namespace native
{
	namespace ui
	{
		Brush::BrushHandle::~BrushHandle()
		{
			delete (jni::Object*) handle;
		}

		Brush::Brush(const Color& color) : _shared(nullptr)
		{
			jni::Object paint = jni::Class("android/graphics/Paint").newInstance();

			paint.call<void>("setColor", int(color.toArgb()));

			_shared->handle = new jni::Object(paint);
		}

		Color Brush::getPrimaryColor() const
		{
			jni::Object* paint = (jni::Object*) getHandle();

			return Color::fromArgb(paint->call<int>("getColor"));
		}
	}
}

