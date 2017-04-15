#ifndef _NATIVE_UI_SIZE_H_
#define _NATIVE_UI_SIZE_H_ 1

// External Dependencies
#include "../../core/include/flags.h"
#include "../../core/include/types.h"

namespace native
{
	namespace ui
	{
		/** Maskable alignments. */
		ENUM_FLAGS(Alignment)
		{
			None = 0,

			// Horizontal Alignments
			Left    = 1,
			Right   = 2,
			HCenter = 4,
			HFill   = 8,

			// Vertical Alignments
			Top     = 16,
			Bottom  = 32,
			VCenter = 64,
			VFill   = 128,

			// Combinations
			Fill       = HFill   | VFill,
			Center     = HCenter | VCenter,
			Horizontal = Left | Right  | HCenter | HFill,
			Vertical   = Top  | Bottom | VCenter | VFill
		};

		/** Shorthand for `Alignment`. */
		typedef Alignment Align;

		/** For specifying vertical or horizontal orientation. */
		enum Orientation
		{
			Horizontal = int(Align::Horizontal),
			Vertical   = int(Align::Vertical)
		};

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
				Gets the value which works along the given orientation within this
				Size construct.
				\param orientation Horizontal for width, Vertical for height.
			 */
			coord_t operator[](Orientation orientation) const { return orientation == Horizontal ? width : height; }
			coord_t& operator[](Orientation orientation) { return orientation == Horizontal ? width : height; }

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

