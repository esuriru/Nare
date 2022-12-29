#pragma once

#include "Event.h"
#include <functional>

namespace Nare
{
	class EventDispatcher
	{
		template<typename T>
		using EventCallback = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : event_(event) {}

		template<typename T>
		bool Dispatch(EventCallback<T> callback)
		{
			if (event_.GetEventType() == T::GetStaticType())
			{
				event_.handled_ = callback(*(T*)&event_);
				return true;
			}
			return false;
		}

	private:
		Event& event_;

	};
	
}

