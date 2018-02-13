#ifndef _NATIVE_VARIANT_H_
#define _NATIVE_VARIANT_H_ 1

// Local Dependencies
#include "string.h"

namespace native
{
	/** Different types of data which can be stored in a Variant. */
	enum class VariantType
	{
		Null   = 0,
		String,
		Int,
		Float
	};

	/**
		A container for holding a generic value, much like value in a dynamically-
		typed programming language. It results in the type being associated with
		the value rather than the variable.
	 */
	class Variant
	{
	public:
		/** Creates an empty Variant, with initial type of Null. */
		Variant() noexcept;

		/**
			Copies another Variant into this Variant.
			\param other The Variant to copy.
		 */
		Variant(const Variant& other);

		/**
			Move constructor.
			\param other The Variant the move.
		 */
		Variant(Variant&& other) noexcept;

		/**
			Creates a Variant of type String.
			\param value The String value to store.
		 */
		Variant(const String& value);
		Variant(const wchar_t* value);
		Variant(const char* value);

		/**
			Creates a Variant of type int.
			\param value The int value to store.
		 */
		Variant(int value) noexcept;

		/**
			Creates a Variant of type float.
			\param value The float value to store.
		 */
		Variant(float value) noexcept;

		/** Destroys the Variant. */
		virtual ~Variant();

		/**
			Copies another Variant into this Variant.
			\param other The Variant to copy.
			\return Reference to this Variant.
		 */
		Variant& operator=(const Variant& other);

		/**
			Determines whether a value has been set for this Variant or not.
			\return `true` if no value has been set, `false` otherwise.
		 */
		bool isNull() const noexcept { return _type == VariantType::Null; }

		/**
			Gets a String representation of the Variant.
			\return The Variant as a String.
		 */
		String toString() const;

		/**
			Gets an `int` representation of the Variant. May result in a FormatException.
			\return The Variant as an `int`.
		 */
		int toInt() const;

		/**
			Gets an `float` representation of the Variant. May result in a FormatException.
			\return The Variant as an `float`.
		 */
		float toFloat() const;

		/**
			Tells what type of value is stored in this Variant.
			\return The current type of Variant stored.
		 */
		VariantType getType() const noexcept { return _type; }

	private:
		// Helper Functions
		static void destroy(Variant* value);
		void set(const Variant* value);

		// Instance Variables
		VariantType _type;

		union {
			String _string;
			int    _int;
			float  _float;
		};
	};
}

#endif // _NATIVE_VARIANT_H_

