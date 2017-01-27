// External Dependencies
#include "../../../core/include/exception.h"

// Module Dependencies
#include "../../include/component.h"
#include "../../include/layoutcomponent.h"

namespace native
{
	namespace ui
	{
		Component::Component()
			: _adapter(nullptr)
			, _parent(nullptr)
		{
		}

		Component::Component(IComponentAdapter* adapter)
			: _adapter(adapter)
			, _parent(nullptr)
		{
		}

		Component::~Component()
		{
			delete _adapter;
		}

		void Component::setParent(LayoutComponent* parent)
		{
			if (parent != _parent)
			{
				if (parent) {
					parent->addChild(this);
				}
				else if (_adapter != nullptr) {
					// Converting to a popup Component.
					if (_parent)
						_parent->removeChild(this);

					_parent = nullptr;
					_adapter->setParent(nullptr);
				}
				else {
					// Can't pop up a Component without an adapter.
					throw InvalidArgumentException();
				}
			}
		}

		void Component::setParentAdapter(IComponentAdapter* parent)
		{
			if (_adapter)
				_adapter->setParent(parent);
		}
	}
}

