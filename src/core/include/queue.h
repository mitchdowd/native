#ifndef _NATIVE_QUEUE_H_
#define _NATIVE_QUEUE_H_ 1

// Module Dependencies
#include "linkedlist.h"

namespace Native
{
	/**
		A first-in-first-out list where values are "pushed" onto the Queue, and
		then the first added value can be "popped" from the Queue.
	 */
	template <class TValue>
	class Queue
	{
	public:
		/**
			Adds the given value to the Queue.
			\param value The value to add.
		 */
		void push(const TValue& value) { _list.append(value); }

		/**
			Removes the value from the end of the Queue and returns it.
			\return The removed value.
		 */
		TValue pop();

		/**
			Gets the number of values in the Queue.
			\return The Queue size.
		 */
		size_t getSize() const noexcept { return _list.getLength(); }

	private:
		// Instance Variables
		LinkedList<TValue> _list;
	};

	template <class TValue>
	TValue Queue<TValue>::pop()
	{
		if (_list.getLength() == 0)
			throw InvalidStateException();

		auto i = _list.begin();
		TValue value = std::move(*i);
		_list.remove(i);
		return value;
	}
}

#endif // _NATIVE_QUEUE_H_
