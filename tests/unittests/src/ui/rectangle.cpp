// External Dependencies
#include <core.h>
#include <test.h>
#include <ui.h>

// Namespace Usage
using namespace native;
using namespace native::ui;

TEST(Rectangle_containsPoint)
{
	Rectangle rect(100, 100, 100, 100);

	ASSERT(rect.containsPoint(Point(100, 100)));
	ASSERT(!rect.containsPoint(Point(200, 200)));
}

TEST(Rectangle_inflate)
{
	Rectangle rect(100, 100, 100, 100);

	rect = rect.inflate(10);

	ASSERT(rect.x == 90 && rect.y == 90);
	ASSERT(rect.width == 120 && rect.height == 120);
}

TEST(Rectangle_deflate)
{
	Rectangle rect(100, 100, 100, 100);

	rect = rect.deflate(10);

	ASSERT(rect.x == 110 && rect.y == 110);
	ASSERT(rect.width == 80 && rect.height == 80);
}

TEST(Rectangle_offset)
{
	Rectangle rect(100, 100, 100, 100);

	rect = rect.offset(10, 10);

	ASSERT(rect.x == 110 && rect.y == 110);
	ASSERT(rect.width == 100 && rect.height == 100);
}

