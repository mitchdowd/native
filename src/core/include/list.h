#ifndef _NATIVE_LIST_H_
#define _NATIVE_LIST_H_ 1

// Module Dependencies
#include "array.h"
#include "collection.h"

namespace native
{
	// Forward Declarations
	template <class TValue> class ListIterator;

	/**
		An ordered collection of values, maintained as an array.
	 */
	template <class TValue>
	class List : public Collection< ListIterator<TValue> >
	{
	public:
		/** Creates an empty List. */
		List();

		/**
			Creates a copy of the given List.
			\param other The List to copy.
		 */
		List(const List<TValue>& other);

		/**
			Performs a move operation, destroying the other List and moving
			its contents to this List.
			\param other The List to move.
		 */
		List(List<TValue>&& other);

		/**
			Creates a List from a compiler-generated initializer_list.
			\param init The initializer list.
		 */
		List(std::initializer_list<TValue> init);

		/**
			Discards the previous contents and makes a copy of another List.
			\param other The List to copy.
			\return A reference to this List.
		 */
		List<TValue>& operator=(const List<TValue>& other);

		/**
			Appends a single value to the end of the List.
			\param value The value to append.
		 */
		void add(const TValue& value) override;

		/**
			Inserts a value into the List at the given index.
			\param index The index to insert it to.
			\param value The value to insert.
		 */
		void insert(size_t index, const TValue& value);

		/**
			Removes the value at the given index from the List.
			\param index The index of the value to remove.
		 */
		void removeAt(size_t index);

		/**
			Removes all instances of the given value from the List.
			\param value The value to remove.
		 */
		void remove(const TValue& value);

		/** Removes all items from the List. */
		void clear() override;

		/**
			The length is the number of values in the List.
			\return The current length.
		 */
		size_t getLength() const noexcept override { return _length; }

		/**
			Retrieves the value at the given zero-based index in the List.
			\param index The index.
			\return The value at the given index.
		 */
		const TValue& atIndex(size_t index) const;
		const TValue& operator[](size_t index) const { return atIndex(index); }

		/**
			Retrieves a modifiable reference to the value at the given zero-based
			index in the List.
			\param index The index.
			\return The value at the given index.
		 */
		TValue& atIndex(size_t index);
		TValue& operator[](size_t index) { return atIndex(index); }

		/**
			Obtains an Iterator positioned at the first value in this List.
			\return An iterator for this List.
		 */
		ListIterator<TValue> begin() const override;

		/**
			Obtains an Iterator just beyond the last value in the List.
			\return An Iterator for the List.
		 */
		ListIterator<TValue> end() const override;

	private:
		// Type Definitions
		typedef typename internal::ArrayOptimizer<TValue>::TArray TArray;

		// Instance Variables
		TArray _array;
		size_t _length;
	};

	/**
		An Iterator specifically for iterating through a List.
	 */
	template <class TValue>
	class ListIterator : public Iterator< TValue, ListIterator<TValue> >
	{
	public:
		/**
			Creates a ListIterator for the given List.
			\param list The List to iterate.
			\param index The index at which to begin iterating.
		 */
		ListIterator(const List<TValue>& list, size_t index);

		/**
			Increments the Iterator forward to the next value in the List.
			\return The Iterator.
		 */
		ListIterator<TValue>& operator++() override;

		/**
			Decrements the Iterator back to the previous value in the List.
			\return The Iterator.
		 */
		ListIterator<TValue>& operator--();

		/**
			Returns the current value in iteration.
			\return The current value in iteration.
		 */
		const TValue& operator*() const override;

		/**
			Tests iterators for inequality.
			\param other The Iterator to compare with.
			\return true if different, false if the same.
		 */
		bool operator!=(const ListIterator<TValue>& other) const override;

	private:
		// Instance Variables
		const List<TValue>& _list;
		size_t _index;
	};

	template <class TValue>
	List<TValue>::List() : _length(0)
	{
	}

	template <class TValue>
	List<TValue>::List(const List<TValue>& other) : _array(other._array), _length(other._length)
	{
	}

	template <class TValue>
	List<TValue>::List(List<TValue>&& other) : _array(std::move(other._array)), _length(other._length)
	{
		other._length = 0;
	}

	template <class TValue>
	List<TValue>::List(std::initializer_list<TValue> init) : _array((const std::initializer_list<TValue>&) init), _length(init.size())
	{
	}

	template <class TValue>
	List<TValue>& List<TValue>::operator=(const List<TValue>& other)
	{
		_array = other._array;
		_length = other._length;

		return *this;
	}

	template <class TValue>
	void List<TValue>::add(const TValue& value)
	{
		if (_array.getLength() <= getLength())
			_array.setLength(internal::getCapacityForLength(getLength() + 1));

		_array.set(_length++, internal::ArrayOptimizer<TValue>::getValue(value));
	}

	template <class TValue>
	void List<TValue>::insert(size_t index, const TValue& value)
	{
		if (_array.getLength() <= this->getLength())
			_array.setLength(internal::getCapacityForLength(getLength() + 1));

		if (index >= getLength())
			index = getLength();
		else {
			// Move contents to make space for the new value.
			_array.set(index + 1, _array.toArray() + index, getLength() - index);
		}

		_array.set(index, internal::ArrayOptimizer<TValue>::getValue(value));
		++_length;
	}

	template <class TValue>
	void List<TValue>::removeAt(size_t index)
	{
		if (index >= getLength())
			internal::raiseArrayIndexException();

		if (index < getLength() - 1) {
			// Move other values back a step in the Array.
			_array.set(index, _array.toArray() + index + 1, getLength() - index - 1);
		}

		--_length;
	}

	template <class TValue>
	void List<TValue>::remove(const TValue& value)
	{
		const List<TValue>& constRef = *this;

		for (size_t i = 0; i < getLength(); ++i)
		{
			while (constRef.atIndex(i) == value)
				removeAt(i);
		}
	}

	template <class TValue>
	void List<TValue>::clear()
	{
		_length = 0;
		_array.clear();
	}

	template <class TValue>
	const TValue& List<TValue>::atIndex(size_t index) const
	{
		return internal::ArrayOptimizer<TValue>::getValue(_array.atIndex(index));
	}

	template <class TValue>
	TValue& List<TValue>::atIndex(size_t index)
	{
		return internal::ArrayOptimizer<TValue>::getValue(_array.atIndex(index));
	}

	template <class TValue>
	ListIterator<TValue> List<TValue>::begin() const
	{
		return ListIterator<TValue>(*this, 0);
	}

	template <class TValue>
	ListIterator<TValue> List<TValue>::end() const
	{
		return ListIterator<TValue>(*this, getLength());
	}

	template <class TValue>
	ListIterator<TValue>::ListIterator(const List<TValue>& list, size_t index) : _list(list), _index(index)
	{
	}

	template <class TValue>
	ListIterator<TValue>& ListIterator<TValue>::operator++()
	{
		_index++;
		return *this;
	}

	template <class TValue>
	ListIterator<TValue>& ListIterator<TValue>::operator--()
	{
		_index--;
		return *this;
	}

	template <class TValue>
	const TValue& ListIterator<TValue>::operator*() const
	{
		return _list[_index];
	}

	template <class TValue>
	bool ListIterator<TValue>::operator!=(const ListIterator<TValue>& other) const
	{
		return _index != other._index || &_list != &other._list;
	}
}

#endif // _NATIVE_LIST_H_
