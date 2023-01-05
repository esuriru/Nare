#pragma once

#include "Nare/Scene/Coordinator.h"
#include "Nare/Scene/Entity.h"

namespace Nare
{
	class Scene
	{
	public:
		Scene();
		~Scene();


	private:
		std::vector<Entity> entities_;

		std::shared_ptr<Coordinator> coordinator_;

	};
}