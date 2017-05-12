#ifndef _NATIVE_FLAGS_H_
#define _NATIVE_FLAGS_H_ 1

// Module Dependencies
#include "types.h"

namespace native
{
	/**
		A Flags is used to provide type-safe masking of enumerated bit flags.
		The type parameter should be an enumeration where the numerical values
		of each enumeration value are powers of 2 (or zero).
	 */
	template <class TEnum>
	class Flags
	{
	public:
		/**
			Creates a Flags with the given flag initially set.
			\param flag The flag to set (defaults to zero-equivalent).
		 */
		inline Flags(TEnum flag = TEnum(0)) noexcept : _mask((uint32_t) flag) {}

		/**
			Copy constructor. Makes a copy of the given Flags.
			\param other The Flags to copy.
		 */
		inline Flags(const Flags<TEnum>& other) noexcept : _mask(other._mask) {}

		/**
			Assigns the given Flags to this one.
			\param other The Flags to assign to this.
			\return This Flags.
		 */
		inline Flags<TEnum>& operator=(const Flags<TEnum>& other) noexcept;

		/**
			Ensures the given flags are set within the Flags.
			\param flags The flags to set.
		 */
		inline void set(Flags<TEnum> flags) noexcept;

		/**
			Ensures the given flag(s) is/are set within the Flags.
			\param flags The flag(s) to set.
			\return The Flags.
		 */
		inline Flags<TEnum>& operator|=(Flags<TEnum> flags) noexcept;

		/**
			Returns a bitwise `or` of this bitmask and another.
			\param flags The flags to `or` with.
			\return The resulting Flags.
		 */
		inline Flags<TEnum> operator|(Flags<TEnum> flags) noexcept;

		/**
			Ensures the given flags are not set within the Flags.
			\param flags The flags to un-set.
		 */
		inline void unSet(Flags<TEnum> flags) noexcept;

		/**
			Removes any items not in the given Flags.
			\param flags The flag(s) to keep set.
			\return The Flags.
		 */
		inline Flags<TEnum>& operator&=(Flags<TEnum> flags) noexcept;

		/**
			Returns a bitwise `and` of this bitmask and another.
			\param flags The flags to `and` with.
			\return The resulting Flags.
		 */
		inline Flags<TEnum> operator&(Flags<TEnum> flags) const noexcept;
		inline Flags<TEnum> operator&(TEnum flags) const noexcept;

		/**
			Checks whether the given flags are set within the Flags.
			\param flags The flags to search for.
			\return true if set, false if not.
		 */
		inline bool isSet(Flags<TEnum> flags) const noexcept;

		/**
			Tells whether there are any flags currently set.
			\return `true` if any non-zero flag is set, `false` otherwise.
		 */
		inline operator bool() const noexcept;

		/**
			Gets the 32-bit value which holds the masked flags.
			\return The underlying 32-bit storage value.
		 */
		uint32_t getData() const noexcept { return _mask; }

	private:
		// Instance Variables
		uint32_t _mask;
	};

	template <class TEnum>
	Flags<TEnum>& Flags<TEnum>::operator=(const Flags<TEnum>& other) noexcept
	{
		_mask = other._mask;
		return *this;
	}

	template <class TEnum>
	void Flags<TEnum>::set(Flags<TEnum> flag) noexcept
	{
		_mask |= flag._mask;
	}

	template <class TEnum>
	Flags<TEnum>& Flags<TEnum>::operator|=(Flags<TEnum> flags) noexcept
	{
		set(flags);
		return *this;
	}

	template <class TEnum>
	Flags<TEnum> Flags<TEnum>::operator|(Flags<TEnum> flags) noexcept
	{
		Flags<TEnum> bm = *this;
		return bm |= flags;
	}

	template <class TEnum>
	void Flags<TEnum>::unSet(Flags<TEnum> flags) noexcept
	{
		_mask &= ~flags._mask;
	}

	template <class TEnum>
	Flags<TEnum>& Flags<TEnum>::operator&=(Flags<TEnum> flags) noexcept
	{
		_mask &= flags._mask;
		return *this;
	}

	template <class TEnum>
	Flags<TEnum> Flags<TEnum>::operator&(Flags<TEnum> flags) const noexcept
	{
		Flags<TEnum> bm = *this;
		return bm &= flags;
	}

	template <class TEnum>
	Flags<TEnum> Flags<TEnum>::operator&(TEnum flags) const noexcept
	{
		Flags<TEnum> bm = *this;
		return bm &= flags;
	}

	template <class TEnum>
	bool Flags<TEnum>::isSet(Flags<TEnum> flag) const noexcept
	{
		return (_mask & flag._mask) == flag._mask;
	}

	template <class TEnum>
	Flags<TEnum>::operator bool() const noexcept
	{
		return _mask != 0;
	}
}

/**
	Declares an enum class which can be combined into a Flags. The numerical
	values of the items in the enum should be powers of two in order for it
	to make much sense.
	\param TEnum The name of the enum type.
 */
#define ENUM_FLAGS(TEnum) \
	enum class TEnum;     \
	inline native::Flags<TEnum> operator|(TEnum lhs, TEnum rhs) noexcept { return native::Flags<TEnum>(lhs) |= rhs; } \
	enum class TEnum

#endif // _NATIVE_FLAGS_H_

