#ifndef _NATIVE_UI_COLOR_H_
#define _NATIVE_UI_COLOR_H_ 1

// External Dependencies
#include "../../core/include/types.h"

namespace native
{
	namespace ui
	{
		/**
			Color is a structure which defines a 32-bit, paintable color.
		 */
		class Color
		{
		public:
			// Public Properties
			byte_t red;				///< Red component of the color.
			byte_t green;			///< Green component of the color.
			byte_t blue;			///< Blue component of the color.
			byte_t alpha;			///< Opacity of the color.

			/** Default constructor. Creates the color black. */
			Color();

			/**
				Creates a Color from a set of ARGB values.
				\param alpha The alpha channel.
				\param red The amount of red.
				\param green The amount of green.
				\param blue The amount of blue.
			 */
			Color(byte_t alpha, byte_t red, byte_t green, byte_t blue);

			/**
				Creates a Color with the given RGB elements.
				\param red The amount of red.
				\param green The amount of green.
				\param blue The amount of blue.
			 */
			Color(byte_t red, byte_t green, byte_t blue);

			/**
				Converts to an integral RGB value.
				\return The RGB value.
			 */
			uint32_t toRgb() const;

			/**
				Creates a Color from an RBG quad value.
				\param rgb The encoded RGB value.
				\return The resulting Color.
			 */
			static Color fromRgb(uint32_t rgb);

			/**
				Creates a Color from an ARBG quad value.
				\param argb The encoded ARGB value.
				\return The resulting Color.
			 */
			static Color fromArgb(uint32_t argb);

			/**
				Converts to an integral ARGB value.
				\return The ARGB value.
			 */
			uint32_t toArgb() const;

			/**
				Creates a Color which is darker by the given percentage. 100%
				will make black.
				\param percentage The percentage to darken by.
				\return The darkened Color.
			 */
			Color darken(float percentage) const;

			/**
				Creates a Color which is lighter by the given percentage. 100%
				will make it white.
				\param percentage The percentage to lighten by.
				\return The ligtened Color.
			 */
			Color lighten(float percentage) const;
		};
	}
}

#endif // _NATIVE_UI_COLOR_H_

