#ifndef _NATIVE_UI_PROGRESS_BAR_H_
#define _NATIVE_UI_PROGRESS_BAR_H_

// Local Dependencies
#include "component.h"

namespace native
{
    namespace ui
    {
        /**
            ProgressBar is a Component which displays a loading progress or
            percentage value by displaying a horizontal bar and filling it
            with the current percentage value.
         */
        class ProgressBar : public Component
        {
        public:
            /**
                Creates a progress bar with a range of 0-100 and a current
                progress value of 0.
             */
            ProgressBar();

            /**
                Sets the valid progress range. Defaults to 0-100.
                \param min The minimum valid value.
                \param max The maximum valid value.
             */
            void setRange(int min, int max);

            /**
                Sets the current progress value.
                \param progress The current progress value.
             */
            void setProgress(int progress);

            /**
                Gets the system-based preferred size of a ProgressBar.
                \return The preferred size.
             */
            virtual Size getPreferredSize() const override;

		protected:
			/** Handles resizing. */
			virtual void onSize(const Size& size) override;

        private:
            // Instance Variables
            int _min, _max, _progress;
        };
    }
}

#endif // _NATIVE_UI_PROGRESS_BAR_H_
