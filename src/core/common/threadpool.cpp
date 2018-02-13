// Module Dependencies
#include "../include/lockscope.h"
#include "../include/threadpool.h"

namespace native
{
	Queue<Function<void>> ThreadPool::_tasks;
	List<Thread*> ThreadPool::_threads;
	Mutex ThreadPool::_lock;
	ConditionVariable ThreadPool::_taskAvailable(_lock);
	bool ThreadPool::_terminate = false;

	void ThreadPool::enqueue(const Function<void>& task)
	{
		LockScope lock(_lock);

		if (_threads.getLength() == 0 || (_tasks.getSize() > 0 && _threads.getLength() < 8))	// TODO: Something less arbitrary.
		{
			_threads.add(new Thread([&]() {
				while (!_terminate)
				{
					Function<void> t;

					{
						LockScope l(_lock);

						// Wait for the next task in the queue.
						while (_tasks.getSize() == 0)
							_taskAvailable.wait();

						t = _tasks.pop();
					}

					t.invoke();
				}
			}));
		}

		_tasks.push(task);
		_taskAvailable.signalOne();
	}
}

