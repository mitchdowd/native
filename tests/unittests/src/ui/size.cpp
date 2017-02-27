// External Dependencies
#include <core.h>
#include <test.h>
#include <ui.h>

// Namespace Usage
using namespace native;
using namespace native::ui;

TEST(Size_combine)
{
	Size size(10, 20);
	Size combination = size.combine(Size(20, 10));

	ASSERT(combination.width == 20 && combination.height == 20);
}

