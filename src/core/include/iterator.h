#ifndef _NATIVE_ITERATOR_H_
#define _NATIVE_ITERATOR_H_ 1

// Module Dependencies
#include "atomic.h"

namespace native
{
	/**
		Used to iterate through the values in a Collection.
	 */
	template <class TValue, class TIterator>
	class Iterator
	{
	public:
		/** The type of value being iterated over. */
		typedef TValue Value;

		/** Virtual destructor. */
		virtual ~Iterator() = default;

		/**
			Increments the iterator forward to the next value in the Collection.
			\return The iterator (typed as the concrete type).
		 */
		virtual TIterator& operator++() = 0;

		/**
			Returns the current value in iteration.
			\return The current value in iteration.
		 */
		virtual const TValue& operator*() const = 0;

		/**
			Tests iterators for inequality.
			\param other The iterator to compare with.
			\return true if different, false if the same.
		 */
		virtual bool operator!=(const TIterator& other) const = 0;
	};
}

#endif // _NATIVE_ITERATOR_H_
