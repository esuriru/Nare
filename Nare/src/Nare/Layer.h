#pragma once
#include "Timestep.h"

namespace Nare
{
	class Event;

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const
		{
			return debugName_;
		}
	private:
		std::string debugName_;

	};
}
