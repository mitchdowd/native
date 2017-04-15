// External Dependencies
#include "../../../lib/jnipp/jnipp.h"
#include "../../core/include/exception.h"

// Module Dependencies
#include "../include/font.h"

namespace native
{
	namespace ui
	{
		Font::Font(const String& family, float size) : _shared(nullptr), _size(size)
		{
            jni::Class Typeface("android/graphics/Typeface");

            jni::Object font = Typeface.call<jni::Object>("create(Ljava/lang/String;I)Landroid/graphics/Typeface;", family.toArray(), 0);

            _shared->handle = new jni::Object(font);
		}

		Font::FontHandle::FontHandle(handle_t handle) : handle(handle), auxHandle(nullptr)
		{
			if (handle)
				throw InvalidArgumentException();
		}

		Font::FontHandle::~FontHandle()
		{
			delete (jni::Object*) handle;
		}

		Font Font::getDefault()
		{
			static Font font = nullptr;
			static SpinLock lock;

			lock.lock();

			if (font.getHandle() == nullptr)
			{
				jni::Class Button("libnative/app/Button");
				jni::method_t viewConstructor = Button.getConstructor("(Landroid/content/Context;)V");
				jni::Object button = Button.newInstance(viewConstructor, (jni::Object*) App::getGlobalHandle());

				// Android already scales its default fonts.
				font._shared->size = button.call<float>("getTextSize") / System::getDisplayScale();
				font._shared->handle = new jni::Object(button.call<jni::Object>("getTypeface()Landroid/graphics/Typeface;"));
			}

			lock.release();

			return font;
		}

		handle_t Font::getAuxHandle() const
		{
			return nullptr;
		}
	}
}

