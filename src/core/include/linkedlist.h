#ifndef _NATIVE_LINKED_LIST_H_
#define _NATIVE_LINKED_LIST_H_ 1

// Module Dependencies
#include "collection.h"
#include "exception.h"

namespace native
{
	// Forward Declarations
	template <class TValue> class LinkedListIterator;

	/**
		A LinkedList. A LinkedList has true constant-time insertion, but you can't
		access items by index.
		This is currently only a singly-linked list until I find a reason to iterate
		backwards.
	 */
	template <class TValue>
	class LinkedList : public Collection< LinkedListIterator<TValue> >
	{
		// Prevent Copying... for now
		LinkedList(const LinkedList<TValue>& other) = delete;
		LinkedList<TValue>& operator=(const LinkedList<TValue>& other) = delete;

	public:
		/** Creates an empty LinkedList. */
		LinkedList();

		/**
			Performs a move operation, destroying the other List and moving
			its contents to this List.
			\param other The List to move.
		 */
		LinkedList(LinkedList<TValue>&& other);

		/**
			Creates a List from a compiler-generated initializer_list.
			\param init The initializer list.
		 */
		LinkedList(std::initializer_list<TValue> init);

		/** Destroys the LinkedList and the values it contains. */
		~LinkedList() { clear(); }

		/**
			Appends a single value to the end of the LinkedList.
			\param value The value to append.
		 */
		void append(const TValue& value);
		void add(const TValue& value) override { append(value); }

		/**
			Prepends a single value to the beginning of the LinkedList.
			\param value The value to prepend.
		 */
		void prepend(const TValue& value);

		/**
			Inserts the given value before the given iterator position in the list.
			\param insertBefore The value to insert before in the list.
			\param value The value to insert.
		 */
		void insert(const LinkedListIterator<TValue>& insertBefore, const TValue& value);

		/**
			Removes the item from the LinkedList identified by the given Iterator.
			\param item The item to remove.
		 */
		void remove(LinkedListIterator<TValue>& item);

		/** Removes all items from the LinkedList. */
		void clear() override;

		/**
			The length is the number of values in the LinkedList.
			\return The current length.
		 */
		size_t getLength() const noexcept override { return _length; }

		/**
			Obtains an Iterator positioned at the first value in this LinkedList.
			\return An iterator for this LinkedList.
		 */
		LinkedListIterator<TValue> begin() const override { return LinkedListIterator<TValue>(nullptr, _first); }

		/**
			Obtains an Iterator just beyond the last value in theLinked List.
			\return An Iterator for the LinkedList.
		 */
		LinkedListIterator<TValue> end() const override { return LinkedListIterator<TValue>(_last, nullptr); }

	private:
		// Type Definitions
		typedef internal::LinkedValue<TValue> Link;

		// Instance Variables
		size_t _length;
		Link*  _first;
		Link*  _last;
	};

	/**
		An Iterator specifically for iterating through a LinkedList.
	 */
	template <class TValue>
	class LinkedListIterator : public Iterator< TValue, LinkedListIterator<TValue> >
	{
	public:
		/**
			Increments the Iterator forward to the next value in the List.
			\return The Iterator.
		 */
		LinkedListIterator<TValue>& operator++() override { _prev = _link; _link = _link->next; return *this; }

		/**
			Returns the current value in iteration.
			\return The current value in iteration.
		 */
		const TValue& operator*() const override { return _link->value; }

		/**
			Tests iterators for inequality.
			\param other The Iterator to compare with.
			\return true if different, false if the same.
		 */
		bool operator!=(const LinkedListIterator<TValue>& other) const override { return _link != other._link; }

	private:
		// Constructor
		LinkedListIterator(internal::LinkedValue<TValue>* prev, internal::LinkedValue<TValue>* link)
			: _prev(prev), _link(link) {}

		// Class Friendships
		friend class LinkedList<TValue>;

		// Instance Variables
		mutable internal::LinkedValue<TValue>* _prev;
		internal::LinkedValue<TValue>* _link;
	};

	template <class TValue>
	LinkedList<TValue>::LinkedList() : _length(0), _first(nullptr), _last(nullptr)
	{
	}

	template <class TValue>
	LinkedList<TValue>::LinkedList(LinkedList<TValue>&& other) : _length(other._length), _first(other._first), _last(other._last)
	{
		other._length = 0;
		other._first = nullptr;
		other._last  = nullptr;
	}

	template <class TValue>
	LinkedList<TValue>::LinkedList(std::initializer_list<TValue> init) : _length(0), _first(nullptr), _last(nullptr)
	{
		for (auto i : init)
			add(i);
	}

	template <class TValue>
	void LinkedList<TValue>::append(const TValue& value)
	{
		Link* link = new Link(value, nullptr);

		if (_first == nullptr)
		{
			_first = _last = link;
		}
		else
		{
			_last->next = link;
			_last = link;
		}

		_length++;
	}

	template <class TValue>
	void LinkedList<TValue>::prepend(const TValue& value)
	{
		Link* link = new Link(value, _first);

		_first = _first ? link : _last = link;
		_length++;
	}

	template <class TValue>
	void LinkedList<TValue>::insert(const LinkedListIterator<TValue>& item, const TValue& value)
	{
		if (_first == nullptr)
			throw InvalidArgumentException();

		Link* link = item._prev = new Link(value, item._link ? item._link->next : nullptr);
		
		if (item._link)
			item._link->next = link;
		else
			_last = link;

		if (item._link == _first)
			_first = link;

		_length++;
	}

	template <class TValue>
	void LinkedList<TValue>::remove(LinkedListIterator<TValue>& item)
	{
		if (!item._link)
			throw InvalidArgumentException();

		if (item._link == _first)
			_first = item._link->next;
		if (item._link == _last)
			_last = item._prev;
		if (item._prev)
			item._prev->next = item._link->next;

		delete item._link;
		item._link = item._link->next;
		--_length;
	}

	template <class TValue>
	void LinkedList<TValue>::clear()
	{
		while (_length > 0) {
			auto pos = begin();
			remove(pos);
		}
	}
}

#endif // _NATIVE_LINKED_LIST_H_

