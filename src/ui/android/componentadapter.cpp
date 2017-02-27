// External Dependencies
#include "../../../lib/jnipp/jnipp.h"
#include "../../core/include/exception.h"

// Module Dependencies
#include "../include/app.h"
#include "../include/componentadapter.h"

// Local Dependencies
#include "componentadapterproperties.h"
#include "componentevent.h"

/** Just a shortcut so I don't have to keep doing those casts. */
#define HANDLE_OBJ ((jni::Object*) _handle)

namespace native
{
	namespace ui
	{
		/*
			ComponentAdapter Functions
		 */

		ComponentAdapter::ComponentAdapter(const ComponentAdapterProperties& props) : _component(props.component)
		{
            if (_component == nullptr)
                throw InvalidArgumentException("Cannot created ComponentAdapter without a Component");

            jni::Class View(props.className);
            jni::method_t viewConstructor = View.getConstructor("(Landroid/content/Context;)V");
            jni::Object view = View.newInstance(viewConstructor, (jni::Object*) App::getAppHandle());

            if (view == nullptr)
                throw UserInterfaceException("Creating android ComponentAdapter");

            _handle = new jni::Object(view);

            // Store this pointer on the View so we can get it back again.
            jni::Class Long("java/lang/Long");
            jni::Object l = Long.newInstance(Long.getConstructor("(J)V"), int64_t(this));
            view.call<void>("setTag(Ljava/lang/Object;)V", l);
		}

		ComponentAdapter::~ComponentAdapter()
		{
			delete HANDLE_OBJ;
		}

		void ComponentAdapter::setParent(IComponentAdapter* parent)
		{
			throw NotImplementedException();
		}

		void ComponentAdapter::setVisible(bool visible)
		{
			throw NotImplementedException();
		}

		bool ComponentAdapter::isVisible() const
		{
			throw NotImplementedException();
		}

		void ComponentAdapter::setArea(const Rectangle& area)
		{
			HANDLE_OBJ->call<void>("setArea", area.x, area.y, area.width, area.height);
		}

		Rectangle ComponentAdapter::getContentArea() const
		{
            return _component->getArea().getSize();
		}

		void ComponentAdapter::setText(const String& text)
		{
			throw NotImplementedException();
		}

		void ComponentAdapter::doPaint(Canvas& canvas)
		{
            if (_component->getBackground().getHandle())
                canvas.fillRectangle(_component->getContentArea().getSize(), _component->getBackground());

            // Call super.onDraw().
            jni::Class super = jni::Class(HANDLE_OBJ->getClass()).getParent();
            auto method = super.getMethod("onDraw", "(Landroid/graphics/Canvas;)V");
            super.call<void>(HANDLE_OBJ, method, (jni::Object*) canvas.getHandle());
		}

		ComponentAdapter* ComponentAdapter::fromHandle(handle_t handle)
		{
            jni::Object view = jni::jobject(handle);
            jni::Object tag  = view.call<jni::Object>("getTag()Ljava/lang/Object;");
            return tag.isNull() ? nullptr : (ComponentAdapter*) tag.call<int64_t>("longValue");
		}

		void ComponentAdapter::onEvent(ComponentEvent& event)
		{
            if (_component)
            {
                switch (event.id)
                {
                    case ComponentEvent::onPaint:
                        {
                            Canvas canvas = jni::jobject(event.arg);
                            _component->dispatchPaintEvent(canvas);
                            break;
                        }

                    case ComponentEvent::onSize:
                        {
                            Rectangle area = _component->getArea();
                            area.setSize(*(Size*) event.arg);
                            _component->updateArea(area);
                            break;
                        }
                }
            }
		}

		/*
			WindowAdapter Functions
		 */

		WindowAdapter::WindowAdapter(Window* window) : ComponentAdapter({ window, "libnative/ui/Window" })
		{
		}

		void WindowAdapter::setText(const String& text)
		{
			jni::Object* activity = (jni::Object*) App::getAppHandle();

			activity->call<void>("setTitle(Ljava/lang/CharSequence;)V", text);
		}

		/*
			TextComponentAdapter Functions
		 */
		
		TextComponentAdapter::TextComponentAdapter() : ComponentAdapter({ /* todo */ })
		{
		}
	}
}

// Namespace Usage
using namespace native;
using namespace native::ui;

extern "C"
{
    void Java_libnative_ui_ViewExtensions_onPaint(_JNIEnv*, jni::jobject, jni::jobject view, jni::jobject canvas)
    {
        ComponentEvent    event   = { ComponentEvent::onPaint, canvas };
        ComponentAdapter* adapter = ComponentAdapter::fromHandle(view);

        if (adapter)
            adapter->onEvent(event);
    }

    void Java_libnative_ui_ViewExtensions_onSize(_JNIEnv*, jni::jobject, jni::jobject view, int width, int height)
    {
        Size              size    = { width, height };
        ComponentEvent    event   = { ComponentEvent::onSize, &size };
        ComponentAdapter* adapter = ComponentAdapter::fromHandle(view);

        if (adapter)
            adapter->onEvent(event);
    }
}
