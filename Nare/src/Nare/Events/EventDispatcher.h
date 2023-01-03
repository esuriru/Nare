#pragma once

#include "Event.h"
#include <functional>

namespace Nare
{
	class EventDispatcher
	{
		// TODO: Lambdas can be compiled into std::functions. Look up whether they can be compiled into function ptrs instead to save overhead
		template<typename T>
		using EventHandler = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : event_(event) {}

		template<typename T>
		bool Dispatch(EventHandler<T> callback)
		{
			if (event_.GetEventType() == T::GetStaticType())
			{
				// Use the handler argument to handle the event.
				event_.Handled = callback(*(T*)&event_);
				return true;
			}
			return false;
		}

	private:
		Event& event_;

	};
	
}

