#pragma once

#include "Nare/Coordinator.h"
#include "Nare/Entity.h"

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