// Module Dependencies
#include "../include/componentadapter.h"
#include "../include/button.h"

namespace native
{
    namespace ui
    {
        Button::Button() : TextComponent(new ButtonAdapter(this))
        {
        }
    }
}

