// External Dependencies
#include "../../../lib/jnipp/jnipp.h"
#include "../../core/include/exception.h"
#include "../../core/include/spinlock.h"
#include "../../core/include/system.h"

// Module Dependencies
#include "../include/app.h"
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

        Size Font::measureText(const String& text) const
        {
            jni::Object paint = jni::Class("android/graphics/Paint").newInstance();

            paint.call<jni::Object>("setTypeface(Landroid/graphics/Typeface;)Landroid/graphics/Typeface;", (jni::Object*) getHandle());
            paint.call<void>("setTextSize", _size);

            return { paint.call<float>("measureText(Ljava/lang/String;)F", text.toArray()), _size };
        }

		Font Font::getDefault()
		{
			static Font font;
			static SpinLock lock;

			lock.lock();

			if (font.getHandle() == nullptr)
			{
				jni::Class Button("libnative/ui/TextComponent");
				jni::method_t viewConstructor = Button.getConstructor("(Landroid/content/Context;)V");
				jni::Object button = Button.newInstance(viewConstructor, (jni::Object*) App::getAppHandle());

				// Android already scales its default fonts.
				font._size = button.call<float>("getScaledTextSize");
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

