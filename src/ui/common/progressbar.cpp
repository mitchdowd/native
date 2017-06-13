// Local Dependencies
#include "../include/app.h"
#include "../include/componentadapter.h"
#include "../include/progressbar.h"

namespace native
{
    namespace ui
    {
        ProgressBar::ProgressBar() : Component(new ProgressBarAdapter(this)), _min(0), _max(100), _progress(0)
        {
            setMargins(coord_t(2 * App::getDisplayScale()), 0, coord_t(2 * App::getDisplayScale()), 0);
        }

        void ProgressBar::setRange(int min, int max)
        {
			_min = min;
			_max = max;

            ((ProgressBarAdapter*) getAdapter())->setMax(max - min);
        }

        void ProgressBar::setProgress(int progress)
        {
			_progress = progress;

            ((ProgressBarAdapter*) getAdapter())->setProgress(progress - _min);
        }

        Size ProgressBar::getPreferredSize() const
        {
#ifdef NATIVE_FORM_MOBILE
            return Size(coord_t(100 * App::getDisplayScale()), coord_t(10 * App::getDisplayScale()));
#else
            return Size(coord_t(160 * App::getDisplayScale()), coord_t(15 * App::getDisplayScale()));
#endif // NATIVE_FORM_*
        }

		void ProgressBar::onSize(const Size& size)
		{
			setProgress(_progress);

			Component::onSize(size);
		}
    }
}

