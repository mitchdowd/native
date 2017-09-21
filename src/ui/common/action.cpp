// External Dependencies
#include "../../core/include/map.h"
#include "../../core/include/spinlock.h"

// Module Dependencies
#include "../include/action.h"

namespace native
{
	namespace ui
	{
		static Map<int32_t, Action*> _actionMap;
		static int32_t _nextId = 100;
		static SpinLock _lock;

		ActionListener::~ActionListener()
		{
			// Remove from Action's subscriber lists.
			for (auto action : _actions)
				action->_listeners.remove(this);
		}

		Action::Action() : _handle(nullptr)
		{
			_lock.lock();
			_actionMap.add(_id = ++_nextId, this);
			_lock.release();
		}

		Action::~Action()
		{
			_lock.lock();
			_actionMap.remove(_id);
			_lock.release();

			// Trigger the callbacks in the ActionHosts.
			for (auto listener : _listeners)
			{
				listener->_actions.remove(this);
				listener->onActionDestroyed(this);
			}
		}

		void Action::setText(const String& text)
		{
			_text = text;

			// Trigger the callbacks in the listeners.
			for (auto listener : _listeners)
				listener->onActionUpdated(this);
		}

		void Action::addListener(ActionListener* listener)
		{
			if (listener)
			{
				_listeners.add(listener);
				listener->_actions.add(this);
			}
		}

		Action* Action::fromId(int32_t id)
		{
			_lock.lock();
			Action* action = _actionMap[id];
			_lock.release();

			return action;
		}
	}
}

