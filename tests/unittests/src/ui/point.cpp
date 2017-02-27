// External Dependencies
#include <core.h>
#include <test.h>
#include <ui.h>

// Namespace Usage
using namespace native;
using namespace native::ui;

TEST(Point_distanceFrom)
{
	Point a(10, 10);
	Point b(10, 20);

	ASSERT(a.distanceFrom(b) == 10);
}

