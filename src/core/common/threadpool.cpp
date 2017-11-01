// Module Dependencies
#include "../include/lockscope.h"
#include "../include/threadpool.h"

namespace native
{
	Queue<Function<void>> ThreadPool::_tasks;
	List<Thread*> ThreadPool::_threads;
	Mutex ThreadPool::_lock;
	ConditionVariable ThreadPool::_taskAvailable = _lock;
	bool ThreadPool::_terminate = false;

	void ThreadPool::enqueue(const Function<void>& task)
	{
		LockScope lock(_lock);

		if (_tasks.getSize() > 0 || _threads.getLength() == 0)
		{
			_threads.add(new Thread([&]() {
				while (!_terminate)
				{
					Function<void> task;

					{
						LockScope lock(_lock);

						// Wait for the next task in the queue.
						while (_tasks.getSize() == 0)
							_taskAvailable.wait();

						task = _tasks.pop();
					}

					task.invoke();
				}
			}));
		}

		_tasks.push(task);
		_taskAvailable.signalOne();
	}
}

