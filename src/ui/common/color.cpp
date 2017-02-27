// Module Dependencies
#include "../include/color.h"

namespace native
{
    namespace ui
    {
        Color::Color() : alpha(0xFF), red(0), green(0), blue(0)
        {
        }

        Color::Color(byte_t a, byte_t r, byte_t g, byte_t b)
                : alpha(a), red(r), green(g), blue(b)
        {
        }

        Color::Color(byte_t r, byte_t g, byte_t b) : alpha(0xFF), red(r), green(g), blue(b)
        {
        }

        uint32_t Color::toRgb() const
        {
            return uint32_t(blue) + (uint32_t(green) << 8) + (uint32_t(red) << 16);
        }

        Color Color::fromRgb(uint32_t rgb)
        {
            Color color;

            color.red   = byte_t(rgb >> 16);
            color.green = byte_t(rgb >> 8);
            color.blue  = byte_t(rgb);

            return color;
        }

        Color Color::fromArgb(uint32_t argb)
        {
            Color color;

            color.alpha = byte_t(argb >> 24);
            color.red   = byte_t(argb >> 16);
            color.green = byte_t(argb >> 8);
            color.blue  = byte_t(argb);

            return color;
        }

        uint32_t Color::toArgb() const
        {
            return uint32_t(blue) + (uint32_t(green) << 8) + (uint32_t(red) << 16) + (uint32_t(alpha) << 24);
        }

        Color Color::darken(float percentage) const
        {
            if (percentage < 0)
                return lighten(-percentage);

            return Color(
                    alpha,
                    byte_t(red   * ((100 - percentage) / 100)),
                    byte_t(green * ((100 - percentage) / 100)),
                    byte_t(blue  * ((100 - percentage) / 100))
            );
        }

        Color Color::lighten(float percentage) const
        {
            static const byte_t max = byte_t(~0);

            if (percentage < 0)
                return darken(-percentage);

            return Color(
                    alpha,
                    byte_t(red   + ((max - red)   * percentage / 100)),
                    byte_t(green + ((max - green) * percentage / 100)),
                    byte_t(blue  + ((max - blue)  * percentage / 100))
            );
        }
    }
}

