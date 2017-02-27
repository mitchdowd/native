// External Dependencies
#include "../../../../lib/jnipp/jnipp.h"
#include "../../../core/include/exception.h"

// Module Dependencies
#include "../../include/app.h"
#include "../../include/componentadapter.h"

// Local Dependencies
#include "componentadapterproperties.h"

namespace native
{
	namespace ui
	{
		/*
			ComponentAdapter Functions
		 */

		ComponentAdapter::ComponentAdapter(const ComponentAdapterProperties& props)
		{
			// TODO
		}

		ComponentAdapter::~ComponentAdapter()
		{
			// TODO
		}

		void ComponentAdapter::setParent(IComponentAdapter* parent_)
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

		void ComponentAdapter::setText(const String& text)
		{
			throw NotImplementedException();
		}

		void ComponentAdapter::doPaint(Canvas& canvas)
		{
			// TODO
		}

		ComponentAdapter* ComponentAdapter::fromHandle(handle_t handle)
		{
			throw NotImplementedException();
		}

		void ComponentAdapter::onEvent(ComponentEvent& event)
		{
			throw NotImplementedException();
		}

		/*
			WindowAdapter Functions
		 */

		WindowAdapter::WindowAdapter(Window* window) : ComponentAdapter({ /* todo */ })
		{
		}

		void WindowAdapter::setText(const String& text)
		{
			jni::Object activity(jni::jobject(App::getAppHandle()));

			activity.call<void>("setTitle(Ljava/lang/CharSequence;)V", text);
		}

		/*
			TextComponentAdapter Functions
		 */
		
		TextComponentAdapter::TextComponentAdapter() : ComponentAdapter({ /* todo */ })
		{
		}
	}
}

