// Module Dependencies
#include "../include/label.h"

namespace native
{
    namespace ui
    {
        Label::Label() : TextComponent()
        {
        }

        Label::Label(const String& text) : TextComponent(text)
        {
        }
    }
}