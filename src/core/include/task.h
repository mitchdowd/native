#ifndef _NATIVE_TASK_H_
#define _NATIVE_TASK_H_ 1

// Module Dependencies
#include "function.h"
#include "thread.h"

namespace native
{
	namespace internal
	{
		// Forward Declarations
		template <class TOutput> struct TaskDetail;
	}

	/**
		A Task can be used to perform asynchronouse processing in a background
		worker thread, then have its result returned once complete.
	 */
	template <class TOutput>
	class Task
	{
		// Prevent Copying
		Task(const Task<TOutput>&) = delete;

	public:
		/**
			Creates a Task which executes the given function. Execution begins
			as soon as a worker thread is available.
			\param function The Function to execute.
		 */
		Task(const Function<TOutput>& function);

		/** Destructor. This does not end the Task. */
		virtual ~Task();

		/**
			Pauses execution until this Task has finished. This is just like the
			getResult() function, but does not give an output.
		 */
		void join() const;

		/**
			Gets the result from this Task. This will block until the result is
			available.
			\return The result of the execution.
		 */
		TOutput getResult() const;

	private:
		// Instance Variables
		internal::TaskDetail<TOutput>* _details;
	};

	namespace internal
	{
		template <class TOutput>
		struct TaskDetail
		{
			TaskDetail(const Function<TOutput>& func) 
				: referenceCount(1), func(func), result(nullptr), thread(Function<void>(this, &TaskDetail::execute)) 
			{
			}

			~TaskDetail() { if (result) delete result; }

			void execute()
			{
				result = new TOutput(std::move(func()));

				if (Atomic::decrement(referenceCount) < 1)
					delete this;
			}

			volatile int referenceCount;
			Function<TOutput> func;
			TOutput* result;
			Thread   thread;
		};

		template <>
		struct TaskDetail<void>
		{
			TaskDetail(const Function<void>& func) 
				: referenceCount(1), func(func), thread(Function<void>(this, &TaskDetail::execute)) 
			{
			}

			void execute()
			{
				func();

				if (Atomic::decrement(referenceCount) < 1)
					delete this;
			}

			volatile int referenceCount;
			Function<void> func;
			Thread   thread;
		};
	}

	template <class TOutput>
	Task<TOutput>::Task(const Function<TOutput>& function) : _details(new internal::TaskDetail<TOutput>(function))
	{
		Atomic::increment(_details->referenceCount);
	}

	template <class TOutput>
	Task<TOutput>::~Task()
	{
		if (Atomic::decrement(_details->referenceCount) < 1)
			delete _details;
	}

	template <class TOutput>
	void Task<TOutput>::join() const
	{
		_details->thread.join();
	}

	template <class TOutput>
	TOutput Task<TOutput>::getResult() const
	{
		join();
		return *_details->result;
	}
}

#endif // _NATIVE_TASK_H_

