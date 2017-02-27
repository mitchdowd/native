#ifndef _NATIVE_UI_SIZE_H_
#define _NATIVE_UI_SIZE_H_ 1

// External Modules
#include "../../core/include/types.h"

namespace native
{
	namespace ui
	{
		/**
			Represents a rectangular size, without a corresponding position.
		 */
		class Size
		{
		public:
			coord_t width;		///< The width.
			coord_t height;		///< The height.

			/** Creates an empty Size, of zero width and height. */
			Size() noexcept;

			/**
				Creates a Size item with the given dimensions.
				\param width The width to set.
				\param height The height to set.
			 */
			Size(coord_t width, coord_t height) noexcept;

			/**
				Sets the dimensions of this Size.
				\param width The width to set.
				\param height The height to set.
			 */
			void set(coord_t width, coord_t height) noexcept;

			/**
				Returns a Size which is large enough to contain the both this Size
				and the supplied Size. This is equivalent to width being assigned
				Math::max(width, other.width), and the same pattern for height.
				\param other The Size to combine with.
			 */
			Size combine(const Size& other) const noexcept;

			/**
				Gets a scaled copy of this Size.
				\param factor The factor to multiply by.
				\return The scaled version.
			 */
			Size scale(float factor) const noexcept { return Size(coord_t(width * factor), coord_t(height * factor)); }

			/**
				Indicates whether the two Size objects are the same dimensions.
				\param other The Size to compare with.
				\return `true` if equal, `false` otherwise.
			 */
			bool operator==(const Size& other) const noexcept { return width == other.width && height == other.height; }

			/**
				Indicates whether the two Size objects have different dimensions.
				\param other The Size to compare with.
				\return `true` if different, `false` if equal.
			*/
			bool operator!=(const Size& other) const noexcept { return width != other.width || height != other.height; }
		};
	}
}

#endif // _NATIVE_UI_SIZE_H_

