// External Dependencies
#include <test.h>
#include <ui.h>

// Local Dependencies
#include "mockcomponentadapter.h"

// Namespace Usage
using namespace native::ui;

TEST(Window_setTitle)
{
	Window window(new native::test::MockComponentAdapter());

	window.setTitle(L"Testing");

	ASSERT_EQUAL(window.getTitle(), L"Testing");
}

