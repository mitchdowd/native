// External Dependencies
#include <core.h>
#include <test.h>
#include <ui.h>


// Namespace Usage
using namespace native;
using namespace native::ui;

TEST(Color_toRgb)
{
    Color color(0x55, 0x66, 0x77);

    ASSERT(color.toRgb() == 0x00556677);
}

TEST(Color_toArgb)
{
    Color color(0x44, 0x55, 0x66, 0x77);

    ASSERT(color.toArgb() == 0x44556677);
}

TEST(Color_darken)
{
    Color color(0x80, 0x40, 0x20);

    ASSERT(color.darken(50).toRgb() == 0x00402010);
}

TEST(Color_lighten)
{
    Color color(0, 0, 0);

    ASSERT(color.lighten(50).toRgb() == 0x007F7F7F);
}

TEST(Color_fromRgb)
{
    Color color1(0x12, 0x34, 0x56);
    Color color2 = Color::fromRgb(color1.toRgb());

    ASSERT(color1.toRgb() == color2.toRgb());
}

