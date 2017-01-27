// External Dependencies
#include <test.h>
#include <ui.h>

// Local Dependencies
#include "mockcomponentadapter.h"

// Namespace Usage
using namespace native::ui;

TEST(Component_setParent)
{
	LayoutComponent parent;
	Component child;

	child.setParent(parent);

	ASSERT(child.getParent() == &parent);
}

TEST(Component_setParentAddsToChildren)
{
	LayoutComponent parent;
	Component child;

	child.setParent(parent);

	ASSERT(parent.getChildren()[0] == &child);
}

