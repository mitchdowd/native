// Module Dependencies
#include "../../include/componentadapter.h"

// Local Dependencies
#include "componentadapterproperties.h"
#include "../../../core/include/exception.h"

namespace native
{
	namespace ui
	{
		ComponentAdapter::ComponentAdapter(const ComponentAdapterProperties& properties)
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

		void ComponentAdapter::onEvent(ComponentEvent& event)
		{
			throw NotImplementedException();
		}

		WindowAdapter::WindowAdapter() : ComponentAdapter({ /* todo */ })
		{
		}
	}
}

