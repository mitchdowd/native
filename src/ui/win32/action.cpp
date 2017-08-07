// Module Dependencies
#include "../include/action.h"

namespace native
{
	namespace ui
	{
		ActionListener::~ActionListener()
		{
			// Remove from Action's subscriber lists.
			for (auto action : _actions)
				action->_listeners.remove(this);
		}

		Action::Action()
		{
			// TODO: Create resources.
		}

		Action::~Action()
		{
			// TODO: Release resources.

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
	}
}

