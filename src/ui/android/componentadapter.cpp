// External Dependencies
#include "../../../lib/jnipp/jnipp.h"
#include "../../core/include/exception.h"
#include "../../core/include/system.h"

// Module Dependencies
#include "../include/app.h"
#include "../include/button.h"
#include "../include/componentadapter.h"
#include "../include/inputcomponent.h"
#include "../include/inputevent.h"

// Local Dependencies
#include "componentadapterproperties.h"
#include "componentevent.h"

/** Just a shortcut so I don't have to keep doing those casts. */
#define HANDLE_OBJ ((jni::Object*) getHandle())

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
            if (parent == nullptr)
                throw new InvalidArgumentException();

            jni::Object* ph = (jni::Object*) ((ComponentAdapter*) parent)->getHandle();
            ph->call<void>("addView(Landroid/view/View;)V", HANDLE_OBJ);
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
            jni::Class("libnative/ui/ViewExtensions").call<void>("setArea(Landroid/view/View;IIII)V", HANDLE_OBJ, area.x, area.y, area.width, area.height);
		}

		Rectangle ComponentAdapter::getArea() const
		{
			return { HANDLE_OBJ->call<int>("getLeft"), HANDLE_OBJ->call<int>("getTop"), HANDLE_OBJ->call<int>("getWidth"), HANDLE_OBJ->call<int>("getHeight") };
		}

		Rectangle ComponentAdapter::getContentArea() const
		{
            return _component->getArea().getSize().scale(System::getDisplayScale());
		}

		void ComponentAdapter::setText(const String& text)
        {
			throw NotSupportedException("Only text Components can have their text set.");
		}

        void ComponentAdapter::setFont(const Font& font)
        {
            throw NotSupportedException("Only text Components can have their font set.");
        }

		void ComponentAdapter::doInput(const InputEvent& event)
		{
			if (!event.nativeEvent)
				return;

			// Call super.onTouchEvent().
			jni::Class super = jni::Class(HANDLE_OBJ->getClass()).getParent();
			auto method = super.getMethod("onTouchEvent", "(Landroid/view/MotionEvent;)Z");
			super.call<bool>(HANDLE_OBJ, method, jni::jobject(event.nativeEvent->arg));
		}

		void ComponentAdapter::doPaint(Canvas& canvas)
		{
            // Call super.onDraw().
            jni::Class super = jni::Class(HANDLE_OBJ->getClass()).getParent();
            auto method = super.getMethod("onDraw", "(Landroid/graphics/Canvas;)V");
            super.call<void>(HANDLE_OBJ, method, (jni::Object*) canvas.getHandle());
		}

		void ComponentAdapter::invokeAsync(const Function<void>& func)
		{
            ((jni::Object*) App::getAppHandle())->call<void>("invokeAsync", int64_t(new Function<void>(func)));
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
                case ComponentEvent::onInput:
                    {
                        jni::Object motionEvent = jni::jobject(event.arg);
                        InputEvent inputEvent;

                        switch (motionEvent.call<int>("getActionMasked"))
                        {
                            case 0: inputEvent.action = InputEvent::Press;   break;
                            case 1: inputEvent.action = InputEvent::Release; break;
                            case 2: inputEvent.action = InputEvent::Motion;  break;
                            default:
                                throw InvalidArgumentException("Unsupported input event");
                        }

                        // Check if it is a mouse event.
                        if (motionEvent.call<int>("getToolType", 0) == 3) {
                            if (inputEvent.action == InputEvent::Motion)
                                inputEvent.source = InputEvent::Mouse;
                            else
                                inputEvent.source = InputEvent::LeftButton;	// Android only handles left button clicks.
                        }
                        else {
                            inputEvent.source = InputEvent::Touch;
                        }

                        inputEvent.x = (coord_t) motionEvent.call<float>("getX");
                        inputEvent.y = (coord_t) motionEvent.call<float>("getY");
                        inputEvent.nativeEvent = &event;
                        _component->dispatchInputEvent(inputEvent);
                        break;
                    }
                case ComponentEvent::onPaint:
                    {
                        Canvas canvas = jni::jobject(event.arg);
                        _component->dispatchPaintEvent(canvas);
                        break;
                    }

                case ComponentEvent::onSize:
                    {
                        Size size = ((Size*) event.arg)->scale(1.0f / System::getDisplayScale());
                        _component->_area.setSize(size);
                        _component->onSize(size);
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

        void WindowAdapter::setArea(const Rectangle& area)
        {
            // This does nothing for Android. Window area is defined by the screen size.
        }

		void WindowAdapter::setText(const String& text)
		{
			jni::Object* activity = (jni::Object*) App::getAppHandle();

			activity->call<void>("setTitle(Ljava/lang/CharSequence;)V", text);
		}

		/*
			TextComponentAdapter Functions
		 */
		
		TextComponentAdapter::TextComponentAdapter(TextComponent* component) : ComponentAdapter({ component, "libnative/ui/TextComponent" })
		{
		}

        void TextComponentAdapter::setText(const String& text)
        {
            HANDLE_OBJ->call<void>("setText(Ljava/lang/CharSequence;)V", text.toArray());
        }

        void TextComponentAdapter::setFont(const Font& font)
        {
            HANDLE_OBJ->call<void>("setTypeface(Landroid/graphics/Typeface;)V", (jni::Object*) font.getHandle());
            HANDLE_OBJ->call<void>("setTextSize", font.getSize());
        }

        /*
            ButtonAdapter Functions
         */

        ButtonAdapter::ButtonAdapter(Button* button) : ComponentAdapter({ button, "libnative/ui/Button" })
        {
        }

        void ButtonAdapter::setText(const String& text)
        {
            HANDLE_OBJ->call<void>("setText(Ljava/lang/CharSequence;)V", text.toArray());
        }

        void ButtonAdapter::setFont(const Font& font)
        {
            HANDLE_OBJ->call<void>("setTypeface(Landroid/graphics/Typeface;)V", (jni::Object*) font.getHandle());
            HANDLE_OBJ->call<void>("setTextSize", font.getSize());
        }

		/*
			InputAdapter Functions
		 */

		InputAdapter::InputAdapter(InputComponent* input) : ComponentAdapter({ input, "libnative/ui/InputComponent" })
		{
		}
	}
}

// Namespace Usage
using namespace native;
using namespace native::ui;

extern "C"
{
    uint8_t Java_libnative_ui_ViewExtensions_onInput(_JNIEnv*, jni::jobject, jni::jobject view, jni::jobject motionEvent) {
        ComponentEvent event = { ComponentEvent::onInput, motionEvent };
        ComponentAdapter* adapter = ComponentAdapter::fromHandle(view);

        if (adapter)
            adapter->onEvent(event);
        return 1;
    }

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

    void Java_libnative_ui_NativeRunnable_onRun(_JNIEnv*, jni::jobject, int64_t funcPtr)
    {
        if (funcPtr)
        {
            Function<void>* function = (Function<void>*) funcPtr;
            function->invoke();
            delete function;
        }
    }
}
