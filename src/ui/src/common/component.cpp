// Module Dependencies
#include "../../include/component.h"

namespace native
{
	namespace ui
	{
		Component::Component() : _adapter(nullptr)
		{
		}

		Component::Component(ComponentAdapter* adapter) : _adapter(adapter)
		{
		}

		Component::~Component()
		{
			delete _adapter;
		}
	}
}

