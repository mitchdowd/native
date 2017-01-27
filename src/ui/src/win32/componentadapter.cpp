// System Dependencies
#include <Windows.h>

// Module Dependencies
#include "../../include/componentadapter.h"

// Local Dependencies
#include "componentadapterproperties.h"

namespace native
{
	namespace ui
	{
		ComponentAdapter::ComponentAdapter(const ComponentAdapterProperties& props)
		{
		}

		void ComponentAdapter::setParent(IComponentAdapter* parent_)
		{
			ComponentAdapter* parent = (ComponentAdapter*) parent_;

			// TODO
		}

		void ComponentAdapter::setText(const String& text)
		{

		}

		WindowAdapter::WindowAdapter() : ComponentAdapter({ /* todo */ })
		{
		}
	}
}

