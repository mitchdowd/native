#ifndef _NATIVE_SIGNAL_H_
#define _NATIVE_SIGNAL_H_ 1

// Module Dependencies
#include "function.h"
#include "list.h"

namespace native
{
	/**
		A Signal, which can be emitted in order to trigger connected Functions.
		This is used to notify loosely-coupled objects of user-triggered events.
	 */
	template <class... TArgs>
	class Signal
	{
	public:
		/**
			Connects the given Function to this Signal. That Function will be
			called when the Signal is emitted.
			\param function The Function to connect.
		 */
		void connect(const Function<void, TArgs...>& function);

		/**
			Connects the given member function and instance to the Signal.
			\param obj The instance.
			\param func The member function.
		 */
		template <class TReturn, class TInstance, class TBase, class... PArgs>
		void connect(TInstance& obj, TReturn(TBase::*func)(PArgs...))
		{
			_clients.add(Function<void, TArgs...>(obj, func));
		}

		/**
			Connects the given member function and instance to the Signal.
			\param obj The instance.
			\param func The member function.
		 */
		template <class TReturn, class TInstance, class TBase, class... PArgs>
		void connect(TInstance* obj, TReturn(TBase::*func)(PArgs...))
		{
			connect(*obj, func);
		}

		/**
			Connects this Signal to another Signal, causing a Signal chain.
			\param signal The Signal to connect to.
		 */
		void connect(Signal<TArgs...>& signal)
		{
			connect(signal, &Signal<TArgs...>::emit);
		}

		/**
			Emits the Signal with all of its necessary arguments.
			\param args The argument to emit.
		 */
		void emit(TArgs... args);
		void operator()(TArgs... args) { emit(args...); }

	private:
		// Instance Variables
		List< Function<void, TArgs...> > _clients;
	};

	template <class... TArgs>
	void Signal<TArgs...>::emit(TArgs... args)
	{
		for (auto f : _clients)
			f.invoke(args...);
	}

	template <class... TArgs>
	void Signal<TArgs...>::connect(const Function<void, TArgs...>& function)
	{
		_clients.add(function);
	}
}

#endif // _NATIVE_SIGNAL_H_

