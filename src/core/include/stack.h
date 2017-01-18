#ifndef _NATIVE_STACK_H_
#define _NATIVE_STACK_H_ 1

// Module Dependencies
#include "linkedlist.h"

namespace native
{
	/**
		A last-in-first-out list where values are "pushed" onto the Stack, and
		then the most recently added value can be "popped" from the Stack.
	 */
	template <class TValue>
	class Stack
	{
	public:
		/**
			Adds the given value to the Stack.
			\param value The value to add.
		 */
		void push(const TValue& value) { _list.prepend(value); }

		/**
			Removes the value from the top of the Stack and returns it.
			\return The removed value.
		 */
		TValue pop();

		/**
			Gets the number of values in the Stack.
			\return The Stack size.
		 */
		size_t getSize() const noexcept { return _list.getLength(); }

	private:
		// Instance Variables
		LinkedList<TValue> _list;
	};

	template <class TValue>
	TValue Stack<TValue>::pop()
	{
		if (_list.getLength() == 0)
			throw InvalidStateException();

		auto i = _list.begin();
		TValue value = std::move(*i);
		_list.remove(i);
		return value;
	}
}

#endif // _NATIVE_STACK_H_