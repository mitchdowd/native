// External Dependencies
#include "../../../core/include/exception.h"

// Module Dependencies
#include "../../include/brush.h"

namespace native
{
	namespace ui
	{
		Brush::BrushHandle::~BrushHandle()
		{
			// TODO
		}

		Brush::Brush(const Color& color) : _shared(nullptr)
		{
			throw NotImplementedException();
		}
	}
}

