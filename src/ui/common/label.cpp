// Module Dependencies
#include "../include/app.h"
#include "../include/label.h"

namespace native
{
    namespace ui
    {
        Label::Label() : TextComponent()
        {
            setMargins(coord_t(2 * App::getDisplayScale()), 0, coord_t(2 * App::getDisplayScale()), 0);
        }

        Label::Label(const String& text) : TextComponent(text)
        {
			setMargins(coord_t(2 * App::getDisplayScale()), 0, coord_t(2 * App::getDisplayScale()), 0);
        }
    }
}