#ifndef _NATIVE_COLLECTION_H_
#define _NATIVE_COLLECTION_H_ 1

// Module Dependencies
#include "iterator.h"

namespace native
{
	/**
		The base class of all multi-valued data structures. This is an interface
		that defines those functions that must be implemented.
	 */
	template <class TIterator>
	class Collection
	{
	public:
		/** Virtual destructor. */
		virtual ~Collection() = default;

		/**
			Adds the given value to the Collection.
			\param value The value to add.
		 */
		virtual void add(const typename TIterator::Value& value) = 0;

		/** Removes all items from the Collection. */
		virtual void clear() = 0;

		/**
			Returns the number of items in the Collection.
			\return The Collection's length.
		 */
		virtual size_t getLength() const noexcept = 0;

		/**
			Obtains an Iterator positioned at the first value in this Collection.
			\return An iterator for this Collection.
		 */
		virtual TIterator begin() const = 0;

		/**
			Returns an Iterator positioned past the last value in the Collection.
			\return An Iterator.
		 */
		virtual TIterator end() const = 0;
	};

	namespace internal
	{
		/** Used to maintain a linked-list chain of values. */
		template <class TValue>
		struct LinkedValue
		{
			LinkedValue(const TValue& value, LinkedValue<TValue>* next) : value(value), next(next) {}
			TValue value;
			LinkedValue<TValue>* next;
		};
	}
}

#endif // _NATIVE_COLLECTION_H_

