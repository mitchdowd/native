// External Dependencies
#include <test.h>
#include <ui.h>

// Local Dependencies
#include "mockcomponentadapter.h"

// Namespace Usage
using namespace native::test;
using namespace native::ui;

TEST(LayoutComponent_addChildAddsToChildren)
{
	LayoutComponent parent;
	Component child;

	parent.addChild(child);

	ASSERT(parent.getChildren()[0] == &child);
}

TEST(LayoutComponent_addChildUpdatesAdapterParent)
{
	MockComponentAdapter* parentAdapter = new MockComponentAdapter();
	MockComponentAdapter* childAdapter = new MockComponentAdapter();

	LayoutComponent parent(parentAdapter);
	LayoutComponent mid;
	Component child(childAdapter);

	mid.addChild(child);

	ASSERT(childAdapter->getParent() == nullptr);

	parent.addChild(mid);

	ASSERT(childAdapter->getParent() == parentAdapter);
}

TEST(LayoutComponent_addChildRemovesFromPreviousParent)
{
	LayoutComponent firstParent, secondParent;
	Component child;

	firstParent.addChild(child);
	secondParent.addChild(child);

	ASSERT(firstParent.getChildren().getLength() == 0);
}

