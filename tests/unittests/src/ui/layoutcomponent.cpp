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

TEST(LayoutComponent_destructorRemovesChildren)
{
	Component child;

	{
		LayoutComponent parent;

		parent.addChild(child);
	}

	ASSERT(child.getParent() == nullptr);
}

TEST(LayoutComponent_childGetsFullContentArea)
{
	LayoutComponent parent;
	Component child;

	parent.addChild(child);
	parent.setArea({ 0, 0, 100, 100 });

	Rectangle area = child.getArea();

	ASSERT(area.width == 100 && area.height == 100);
	ASSERT(area.x == 0 && area.y == 0);
}

