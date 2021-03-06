// External Dependencies
#include <core.h>
#include <test.h>
#include <ui.h>

// Local Dependencies
#include "mockcomponentadapter.h"

// Namespace Usage
using namespace native::test;
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

TEST(Component_setParentToNull)
{
	MockComponentAdapter* parentAdapter = new MockComponentAdapter();
	MockComponentAdapter* childAdapter = new MockComponentAdapter();

	LayoutComponent parent(parentAdapter);
	Component child(childAdapter);
	Component childWithoutAdapter;

	parent.addChild(child);
	parent.addChild(childWithoutAdapter);

	ASSERT(childAdapter->getParent() == parentAdapter);

	child.setParent(nullptr);

	ASSERT(childAdapter->getParent() == nullptr);
	ASSERT_THROWS(childWithoutAdapter.setParent(nullptr), native::InvalidStateException);
}

TEST(Component_destructorRemovesFromParent)
{
	LayoutComponent parent;

	{
		Component child;

		parent.addChild(child);
	}

	ASSERT(parent.getChildren().getLength() == 0);
}

TEST(Component_defaultConstructorHasNoAdapter)
{
	Component component;

	ASSERT(component.getAdapter() == nullptr);
}

TEST(Component_allocateAreaChecksMargin)
{
	Component component;

	component.setMargins({ 10, 20, 30, 40 });
	component.setAlignment(Align::Fill);
	component.allocateArea({ 100, 100, 100, 100 });
	Rectangle area = component.getArea();

	ASSERT(area.x == 140);
	ASSERT(area.y == 110);
	ASSERT(area.width == 40);
	ASSERT(area.height == 60);
}

TEST(Component_setAreaIgnoresMargin)
{
	Component component;

	component.setMargins({ 10, 20, 30, 40 });

	component.setArea({ 100, 100, 100, 100 });
	Rectangle area = component.getArea();

	ASSERT(area.x == 100);
	ASSERT(area.y == 100);
	ASSERT(area.width == 100);
	ASSERT(area.height == 100);
}

