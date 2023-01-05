#include "Scene.h"

namespace Nare
{
	Scene::Scene()
	{
		coordinator_.reset(Coordinator::Instance());

	}

	Scene::~Scene()
	{
		coordinator_->Destroy();
	}
}
