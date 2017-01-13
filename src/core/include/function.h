#ifndef _NATIVE_FUNCTION_H_
#define _NATIVE_FUNCTION_H_ 1

// Module Dependencies
#include "atomic.h"

namespace native
{
	namespace internal
	{
		// Storages internal data for class Function.
		struct FunctionData
		{
			FunctionData() : invoker(nullptr), referenceCount(1) {}
			virtual ~FunctionData() {}

			typedef void (*func_ptr)(void*);

			func_ptr invoker;				///< Static, typed function to call the stored function pointer.
			volatile int referenceCount;	///< Reference count.
		};

		// Function data for unbound (lambda or static) functions.
		template <class TFunc>
		struct UnboundFunctionData : public FunctionData
		{
			UnboundFunctionData(TFunc func) : func(func) {}

			TFunc func;
		};

		// Function data for bound (member) functions.
		template <class TObj, class TFunc>
		struct BoundFunctionData : public FunctionData
		{
			BoundFunctionData(TObj* obj, TFunc func) : func(func), obj(obj) {}

			TObj* obj;
			TFunc func;
		};
	}

	/**
		Holds various forms of Function pointers in a type-safe manner so they
		can be called at a later point in time.
	 */
	template <class TReturn, class... TArgs>
	class Function
	{
	public:
		/** Default constructor. */
		Function() : _func(new internal::FunctionData())
		{
		}

		/**
			Constructor for Function from an unbound function, or lambda.
			\param func The function pointer.
		 */
		template <typename TFunc>
		Function(TFunc func)
		{
			_func = new internal::UnboundFunctionData<TFunc>(func);
			_func->invoker = internal::FunctionData::func_ptr(&invoker<internal::UnboundFunctionData<TFunc> >);
		}

		/**
			Creates a Function from a bound member function pointer.
			\param obj The object to bind to.
			\param func The function pointer.
		*/
		template <class TObj, class TFunc>
		Function(TObj* obj, TFunc func)
		{
			_func = new internal::BoundFunctionData<TObj, TFunc>(obj, func);
			_func->invoker = internal::FunctionData::func_ptr(&memberCaller<internal::BoundFunctionData<TObj, TFunc> >);
		}

		/**
			Creates a Function from a bound member function pointer.
			\param obj The object to bind to.
			\param func The function pointer.
		 */
		template <class TObj, class TFunc>
		Function(TObj& obj, TFunc func)
		{
			_func = new internal::BoundFunctionData<TObj, TFunc>(&obj, func);
			_func->invoker = internal::FunctionData::func_ptr(&memberCaller<internal::BoundFunctionData<TObj, TFunc> >);
		}

		/**
			Copy constructor.
			\param other The Function to copy.
		 */
		Function(const Function<TReturn, TArgs...>& other) noexcept : _func(other._func)
		{
			Atomic::increment(_func->referenceCount);
		}

		/** Destroys the Function. */
		virtual ~Function() { if (Atomic::decrement(_func->referenceCount) < 1) delete _func; }

		/**
			Copy assignment operator.
			\param other The Function to copy.
			\return The copied Function.
		 */
		Function<TReturn, TArgs...>& operator=(const Function<TReturn, TArgs...>& other) noexcept
		{
			if (other._func != _func)
			{
				if (Atomic::decrement(_func->referenceCount) < 1)
					delete _func;
				_func = other._func;
				Atomic::increment(_func->referenceCount);
			}
			return *this;
		}

		/**
			Invokes, or calls the function with the necessary set of arguments.
			\param args The set of types arguments.
			\return The return value.
		 */
		TReturn invoke(TArgs... args) const { return invoker_t(_func->invoker)(_func, args...); }
		TReturn operator()(TArgs... args) const { return invoke(args...); }

	private:
		template <class TImpl>
		static TReturn invoker(TImpl* impl, TArgs... args)
		{
			/* 
				Getting a compiler error?
				If it's pointing you here, then your function pointer doesn't match
				the Function type arguments.
			*/
			return impl->func(args...);
		}

		template <class TImpl>
		static TReturn memberCaller(TImpl* impl, TArgs... args)
		{
			/* 
				Getting a compiler error?
				If it's pointing you here, then your function pointer doesn't match
				the Function type arguments.
			*/
			return (impl->obj->*impl->func)(args...);
		}

		// Type Definitions
		typedef TReturn (*invoker_t)(void*, TArgs...);

		// Instance Variables
		internal::FunctionData* _func;
	};

	/**
		A template specialisation of the Function class, allowing Functions with void
		return types to accept functions with return types as input.
	 */
	template <class... TArgs>
	class Function<void, TArgs...>
	{
	public:
		/** Default constructor. */
		Function() : _func(new internal::FunctionData())
		{
		}

		/**
			Constructor for Function from an unbound function, or lambda.
			\param func The function pointer.
		 */
		template <typename TFunc>
		Function(TFunc func)
		{
			// Would be good to remove the operator new overhead...
			_func = new internal::UnboundFunctionData<TFunc>(func);
			_func->invoker = internal::FunctionData::func_ptr(&invoker<internal::UnboundFunctionData<TFunc> >);
		}

		/**
			Creates a Function from a bound member function pointer.
			\param obj The object to bind to.
			\param func The function pointer.
		 */
		template <class TObj, class TFunc>
		Function(TObj* obj, TFunc func)
		{
			_func = new internal::BoundFunctionData<TObj, TFunc>(obj, func);
			_func->invoker = internal::FunctionData::func_ptr(&memberCaller<internal::BoundFunctionData<TObj, TFunc> >);
		}

		/**
			Creates a Function from a bound member function pointer.
			\param obj The object to bind to.
			\param func The function pointer.
		 */
		template <class TObj, class TFunc>
		Function(TObj& obj, TFunc func)
		{
			_func = new internal::BoundFunctionData<TObj, TFunc>(&obj, func);
			_func->invoker = internal::FunctionData::func_ptr(&memberCaller<internal::BoundFunctionData<TObj, TFunc> >);
		}

		/**
			Copy constructor.
			\param other The Function to copy.
		 */
		Function(const Function<void, TArgs...>& other) noexcept : _func(other._func)
		{
			Atomic::increment(_func->referenceCount);
		}

		/** Destroys the Function. */
		virtual ~Function() { if (Atomic::decrement(_func->referenceCount) < 1) delete _func; }

		/**
			Copy assignment operator.
			\param other The Function to copy.
			\return The copied Function.
		 */
		Function<void, TArgs...>& operator=(const Function<void, TArgs...>& other) noexcept
		{
			if (other._func != _func)
			{
				if (Atomic::decrement(_func->referenceCount) < 1)
					delete _func;
				_func = other._func;
				Atomic::increment(_func->referenceCount);
			}
			return *this;
		}

		/**
			Invokes (or calls) the Function with the necessary arguments.
			\param args Set of typed arguments.
		 */
		void invoke(TArgs... args) const { invoker_t(_func->invoker)(_func, args...); }
		void operator()(TArgs... args) const { invoke(args...); }

	private:
		template <class TImpl>
		static void invoker(TImpl* impl, TArgs... args)
		{
			/*
				Getting a compiler error?
				If it's pointing you here, then your function pointer doesn't match
				the Function type arguments.
			*/
			impl->func(args...);
		}

		template <class TImpl>
		static void memberCaller(TImpl* impl, TArgs... args)
		{
			/* 
				Getting a compiler error?
				If it's pointing you here, then your function pointer doesn't match
				the Function type arguments.
			*/
			(impl->obj->*impl->func)(args...);
		}

		// Type Definitions
		typedef void (*invoker_t)(void*, TArgs...);

		// Instance Variables
		internal::FunctionData* _func;
	};
}

#endif // _NATIVE_FUNCTION_H_

