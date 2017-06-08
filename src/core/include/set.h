#ifndef _NATIVE_SET_H_
#define _NATIVE_SET_H_ 1

// Module Dependencies
#include "array.h"
#include "collection.h"
#include "exception.h"
#include "hash.h"

namespace native
{
	// Forward Declarations
	template <class TValue> class SetIterator;

	/**
		A Set is a Collection of unique items. A Set will not contain more than
		one of a single value.
	 */
	template <class TValue>
	class Set : public Collection< SetIterator<TValue> >
	{
	public:
		/**
			Creates a Set with the given hash-table size. Generally prime numbers
			are recommended for hash sizes, with larger numbers used for Sets which
			are expected to hold more elements.
			\param tableSize The Set's hash-table size.
		 */
		Set(size_t tableSize = 17);

		/**
			Copies the given Set to this one. This is a shallow copy operation
			whenever possible.
			\param other The Set to copy.
		 */
		Set(const Set<TValue>& other);

		/**
			Moves the contents of the given Set to this one.
			\param other The Set to move.
		 */
		Set(Set<TValue>&& other) noexcept;

		/**
			Creates a Set from a compiler-generated initializer_list.
			\param init The initializer list.
		 */
		Set(std::initializer_list<TValue> init);

		/** Destroys the Set and all the values it contains. */
		~Set();

		/**
			Assigns the contents of another Set to this one. The previous contents
			are lost. This is a shallow copy operation when possible.
			\param other The Set to copy.
			\return This Set.
		 */
		Set<TValue>& operator=(const Set<TValue>& other);

		/**
			Adds the given value to the Set. If it already exists within the Set,
			no action is taken.
			\param value The value to add.
		 */
		void add(const TValue& value) override;

		/**
			Removes the given value from the Set.
			\param value The value to remove.
		 */
		void remove(const TValue& value);

		/** Empties the Set. */
		void clear() override;

		/**
			Checks if the given value is already in the Set.
			\param value The value to search for.
			\return true or false.
		 */
		bool contains(const TValue& value) const;

		/**
			Returns the number of values in the Set.
			\return The Set's length.
		 */
		size_t getLength() const noexcept override;

		/**
			Returns an Iterator positioned at the first value in this Set.
			\return An Iterator.
		 */
		SetIterator<TValue> begin() const override;

		/**
			Returns an Iterator positioned past the last value in the Set.
			\return An Iterator.
		 */
		SetIterator<TValue> end() const override;

	private:
		// Class Friendships
		friend class SetIterator<TValue>;

		// Type Definitions
		typedef typename internal::LinkedValue<TValue> Link;

		// Instance Variables
		Array<Link*> _table;
		size_t _length;
	};

	/**
		Used to iterate through a Set.
	 */
	template <class TValue>
	class SetIterator : public Iterator< TValue, SetIterator<TValue> >
	{
	public:
		/**
			Increments the SetIterator forward to the next value in the Set.
			\return The Iterator.
		 */
		SetIterator<TValue>& operator++() override;

		/**
			Returns the current value in iteration.
			\return The current value in iteration.
		 */
		const TValue& operator*() const override;

		/**
			Tests iterators for inequality.
			\param other The SetIterator to compare with.
			\return true if different, false if the same.
		 */
		bool operator!=(const SetIterator<TValue>& other) const override;

	private:
		// Class Friendships
		friend class Set<TValue>;

		// Type Definitions
		typedef typename internal::LinkedValue<TValue> Link;

		/** Constructor. Used by class Set. */
		SetIterator(const Set<TValue>& set, size_t index, Link* link);

	private:
		// Instance Variables
		const Array<Link*>& _table;
		size_t _index;
		Link* _link;
	};

	template <class TValue>
	Set<TValue>::Set(size_t tableSize) : _table(tableSize), _length(0)
	{
		if (tableSize < 1)
			throw InvalidArgumentException();

		// Initialise to nulls.
		for (size_t i = 0; i < tableSize; i++)
			_table.set(i, nullptr);
	}

	template <class TValue>
	Set<TValue>::Set(const Set<TValue>& other) : _table(other._table), _length(other._length)
	{
	}

	template <class TValue>
	Set<TValue>::Set(Set<TValue>&& other) noexcept : _table(std::move(other._table)), _length(other._length)
	{
		other._length = 0;
	}

	template <class TValue>
	Set<TValue>::Set(std::initializer_list<TValue> init) : _table(17), _length(0)
	{
		// Initialise to nulls.
		for (size_t i = 0; i < _table.getLength(); i++)
			_table.set(i, nullptr);

		for (auto i : init)
			add(i);
	}

	template <class TValue>
	Set<TValue>::~Set()
	{
		clear();
	}

	template <class TValue>
	Set<TValue>& Set<TValue>::operator=(const Set<TValue>& other)
	{
		_table = other._table;
		_length = other._length;

		return *this;
	}

	template <class TValue>
	void Set<TValue>::add(const TValue& value)
	{
		// Perform the hash.
		size_t hashCode = hash(value) % _table.getLength();

		// Check whether the key already exists.
		for (Link* link = _table[hashCode]; link; link = link->next)
			if (link->value == value)
				return;

		// Add the new link.
		_table.set(hashCode, new Link(value, _table[hashCode]));
		_length++;
	}

	template <class TValue>
	void Set<TValue>::remove(const TValue& value)
	{
		// Perform the hash.
		size_t hashCode = hash(value) % _table.getLength();
		Link* link = _table[hashCode];

		if (link)
		{
			if (link->value == value)
			{
				// It's the first item with that hash code.
				_table.set(hashCode, link->next);
				_length--;
				delete link;
			}
			else
			{
				while (link->next)
				{
					if (link->next->value == value)
					{
						Link* target = link->next;
						link->next = target->next;
						_length--;
						delete target;
						break;
					}

					link = link->next;
				}
			}
		}
	}

	template <class TValue>
	void Set<TValue>::clear()
	{
		// Delete all of the values.
		for (size_t i = 0; i < _table.getLength(); i++)
		{
			Link* link = _table[i];

			while (link)
			{
				Link* target = link;
				link = link->next;
				delete target;
			}
		}

		_length = 0;
	}

	template <class TValue>
	bool Set<TValue>::contains(const TValue& value) const
	{
		// Perform the hash.
		size_t hashCode = hash(value) % _table.getLength();

		// Search for the key.
		for (Link* link = _table[hashCode]; link; link = link->next)
			if (link->value == value)
				return true;

		return false;
	}

	template <class TValue>
	size_t Set<TValue>::getLength() const noexcept
	{
		return _length;
	}

	template <class TValue>
	SetIterator<TValue> Set<TValue>::begin() const
	{
		size_t index;
		Link* link = nullptr;

		// Move to the first valid Link.
		for (index = 0; index < _table.getLength(); ++index)
			if ((link = _table[index]) != nullptr)
				break;

		return SetIterator<TValue>(*this, index, link);
	}

	template <class TValue>
	SetIterator<TValue> Set<TValue>::end() const
	{
		return SetIterator<TValue>(*this, _table.getLength(), nullptr);
	}

	template <class TValue>
	SetIterator<TValue>::SetIterator(const Set<TValue>& set, size_t index, Link* link)
		: _table(set._table), _index(index), _link(link)
	{
	}

	template <class TValue>
	SetIterator<TValue>& SetIterator<TValue>::operator++()
	{
		if (!_link)
			throw InvalidStateException();

		_link = _link->next;

		while (!_link && ++_index < _table.getLength())
			_link = _table[_index];

		return *this;
	}

	template <class TValue>
	const TValue& SetIterator<TValue>::operator*() const
	{
		return _link->value;
	}

	template <class TValue>
	bool SetIterator<TValue>::operator!=(const SetIterator<TValue>& other) const
	{
		return _link != other._link || _index != other._index || &_table != &other._table;
	}
}

#endif // _NATIVE_SET_H_
