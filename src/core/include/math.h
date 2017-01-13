#ifndef _NATIVE_MATH_H_
#define _NATIVE_MATH_H_ 1

// Module Dependencies
#include "types.h"

#ifdef min
# undef min
#endif
#ifdef max
# undef max
#endif

namespace native
{
	/**
		Math is a static class that provides basic mathematical functions.
	 */
	class Math
	{
		Math() = delete;

	public:
		/**
			Returns the smaller of two values.
			\param lhs The first value.
			\param rhs The second value.
			\return The smaller of the two values.
		 */
		template <typename T>
		static constexpr T min(T lhs, T rhs) { return rhs < lhs ? rhs : lhs; }

		/**
			Returns the larger of two values.
			\param lhs The first value.
			\param rhs The second value.
			\return The larger of the two values.
		 */
		template <typename T>
		static constexpr T max(T lhs, T rhs) { return rhs > lhs ? rhs : lhs; }

		/**
			Returns the absolute value of the given value.
			\param value A numerical value.
			\return A positive equivalent of the given value.
		 */
		template <typename T>
		static constexpr T abs(T value) { return value < 0 ? -value : value; }

		/**
			Returns the first integer value higher than the specified value.
			\param value A decimal value.
			\return Rounded value.
		 */
		static constexpr double ceiling(double value) 
		{ 
			return double(int64_t(value)) == value ? value : double(int64_t(value) + 1);
		}

		/**
			Returns the first integer value lower than or equal to the specified value.
			\param value A decimal value.
			\return Rounded value.
		 */
		static constexpr double floor(double value) { return double(int64_t(value)); }

		/**
			Calculates the square root of the supplied value.
			\param value A numerical value.
			\return The square root of the supplied value.
		 */
		template <typename T>
		static T squareRoot(T value) { return (T) sqrt((double) value); }

		/**
			Generates a random number in the range [`min`, `outerMax`).
			\param min The inclusive minimum value.
			\param outerMax The exclusive maximum value.
			\return The random number.
		 */
		static long double random(long double min, long double outerMax);
		static double random(double min, double outerMax);
		static float random(float min, float outerMax);
		static int random(int min, int outerMax);

	private:
		// Helper Functions
		static double sqrt(double value);
	};
}

#endif // _NATIVE_MATH_H_

