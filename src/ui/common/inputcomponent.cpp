// Module Dependencies
#include "../include/componentadapter.h"
#include "../include/inputcomponent.h"

namespace native
{
	namespace ui
	{
		InputComponent::InputComponent() : TextComponent(new InputAdapter(this))
		{
		}
	}
}

