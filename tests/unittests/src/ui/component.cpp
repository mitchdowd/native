// External Dependencies
#include <test.h>
#include <ui.h>

// Namespace Usage
using namespace native::ui;

TEST(Component_defaultConstructorHasNoAdapter)
{
	Component component;

	ASSERT(component.getAdapter() == nullptr);
}

