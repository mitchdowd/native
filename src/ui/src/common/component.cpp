// Module Dependencies
#include "../../include/component.h"

namespace native
{
	namespace ui
	{
		Component::Component() : _adapter(nullptr)
		{
		}

		Component::Component(IComponentAdapter* adapter) : _adapter(adapter)
		{
		}

		Component::~Component()
		{
			delete _adapter;
		}
	}
}

