#pragma once

#include "Event.h"

namespace Nare
{
	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const
		{
			return keycode_;
		}

		NR_EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode) : keycode_(keycode) {}
		int keycode_;

	};
}

