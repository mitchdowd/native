#ifndef _NATIVE_SHARED_H_
#define _NATIVE_SHARED_H_ 1

// Module Dependencies
#include "atomic.h"

namespace native
{
	/**
		Provides a way to pass around a non-copyable object by value, using
		reference counting. This is, for all intents and purposes, just like
		passing a pointer to the value around, except you don't have to worry
		about deleting the value when you're finished with it. This means that
		a change to the value in one Shared instance will also update the value
		in other Shared instances which reference the same value.
	 
		For multi-threaded environments, care should be taken to mutually
		exclude access to the _underyling value_, not just to each instance of
		class Shared.
	 */
	template <class TValue>
	class Shared
	{
	public:
		/**
			Constructs the underyling value using the arguments provided.
			\param args Variadic arguments to pass to the contained value's constructor.
		 */
		template <class... TArgs>
		Shared(TArgs... args) : _data(new Data(args...)) {}

		/**
			Copy constructor. This Shared will share the same data with the
			"copied" instance of Shared.
			\param other The instance to share data with.
		 */
		Shared(const Shared<TValue>& other);

		/**
			Move constructor. This will leave the other Shared in an unusable
			state, and will steal its reference to its contained value.
			\param other The instance to move.
		 */
		Shared(Shared<TValue>&& other);

		/** Destructor. Release's this reference to the shared value. */
		virtual ~Shared() { release(); }

		/**
			Assignment operator. Releases the previous value and shared data
			with the provided Shared instance.
			\param other The instance to share a value with.
			\return This instance.
		 */
		Shared<TValue>& operator=(const Shared<TValue>& other);

		/**
			Gets a reference to the stored value.
			\return The stored value.
		 */
		TValue& get() const { return _data->value; }
		TValue& operator*() const { return _data->value; }

		/**
			Retrieves a pointer to the shared value.
			\return The shared value.
		 */
		TValue* operator->() const { return &get(); }

	protected:
		/**
			Releases this reference on the shared value. This instance will no
			longer be usable until a new value is assigned to it.
			\return `true` if this was the last reference, `false` otherwise.
		 */
		bool release();

	private:
		/**
			Contains the shared data. Reference counted, and can be used by
			more than one Shared instance. 
		 */
		struct Data
		{
			template <class... TArgs>
			Data(TArgs... args) : value(args...), refCount(1) {}

			TValue value;
			volatile int refCount;
		};

		// Instance Variables
		Data* _data;
	};

	/**
		A smart-pointer implementation, where a value is allocated on the heap
		and then automatically deleted when there are no more SharedPtrs that
		reference it.
		As with class Shared, care must be taken in multi-threaded environments
		to apply mutual exclusion mechanisms to the *value* that is stored, not
		just to the SharedPtr instances.
	 */
	template <class TValue>
	class SharedPtr : public Shared<TValue*>
	{
	public:
		/**
			Creates a SharedPtr containing the given value. This value *must* be
			allocated with operator new, as it will be deleted using the delete
			operator when it is no longer refrenced by a SharedPtr.
			\param pointer The pointer to store.
		 */
		SharedPtr(TValue* pointer = nullptr) : Shared<TValue*>(pointer) {}

		/**
			Releases this reference on the contained value. If it is no longer
			referenced, it will be deleted.
		 */
		~SharedPtr();

		/**
			Releases the previous stored pointer and accepts a new one.
			\param pointer The pointer to assign.
			\return This instance.
		 */
		SharedPtr<TValue>& operator=(TValue* pointer);

		/**
			Gets a reference to the stored value (as opposed to its pointer).
			\return The stored value.
		 */
		TValue& operator*() const { return *Shared<TValue*>::get(); }

		/**
			Gets the stored pointer.
			\return The stored pointer.
		 */
		TValue* operator->() const { return Shared<TValue*>::get(); }
	};

	template <class TValue>
	Shared<TValue>::Shared(const Shared<TValue>& other) : _data(other._data)
	{
		Atomic::increment(_data->refCount);
	}

	template <class TValue>
	Shared<TValue>::Shared(Shared<TValue>&& other) : _data(other._data)
	{
		other._data = nullptr;
	}

	template <class TValue>
	Shared<TValue>& Shared<TValue>::operator=(const Shared<TValue>& other)
	{
		if (_data != other._data)
		{
			// Release the previous data.
			if (_data && Atomic::decrement(_data->refCount) < 1)
				delete _data;

			// Assign the new data.
			_data = other._data;
			Atomic::increment(_data->refCount);
		}

		return *this;
	}

	template <class TValue>
	bool Shared<TValue>::release()
	{
		if (_data && Atomic::decrement(_data->refCount) < 1)
		{
			delete _data;
			_data = nullptr;
			return true;
		}

		_data = nullptr;
		return false;
	}

	template <class TValue>
	SharedPtr<TValue>::~SharedPtr()
	{
		TValue* ptr = Shared<TValue*>::get();

		if (Shared<TValue*>::release())
			delete ptr;
	}

	template <class TValue>
	SharedPtr<TValue>& SharedPtr<TValue>::operator=(TValue* pointer)
	{
		TValue* existing = Shared<TValue*>::get();

		if (pointer != existing)
		{
			if (Shared<TValue*>::release())
				delete existing;

			Shared<TValue*>::operator=(pointer);
		}

		return *this;
	}
}

#endif // _NATIVE_SHARED_H_

