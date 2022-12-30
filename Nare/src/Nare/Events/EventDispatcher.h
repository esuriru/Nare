#pragma once

#include "Event.h"
#include <functional>

namespace Nare
{
	class EventDispatcher
	{
		// TODO: Look into whether std::function is the best way to do this. From what I know std::function has overhead.
		template<typename T>
		using EventCallback = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : event_(event) {}

		template<typename T>
		bool Dispatch(EventCallback<T> callback)
		{
			if (event_.GetEventType() == T::GetStaticType())
			{
				// Use the callback provided to handle the event.
				event_.handled_ = callback(*(T*)&event_);
				return true;
			}
			return false;
		}

	private:
		Event& event_;

	};
	
}

