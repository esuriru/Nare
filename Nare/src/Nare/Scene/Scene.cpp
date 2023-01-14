#include "Scene.h"
#include "Transform.h"

namespace Nare
{
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

    void Scene::Init()
    {
        auto& coordinator = Coordinator::Instance();

        renderSystem_ = coordinator.RegisterSystem<RenderSystem>();
        transformSystem_ = coordinator.RegisterSystem<TransformSystem>();

        Signature render_signature;
        render_signature.set(coordinator.GetComponentType<Transform>());
        render_signature.set(coordinator.GetComponentType<RenderMesh>());
        coordinator.SetSystemSignature<RenderSystem>(render_signature);

        Signature transform_signature;
        transform_signature.set(coordinator.GetComponentType<Transform>());
        coordinator.SetSystemSignature<TransformSystem>(transform_signature);
    }

    void Scene::FixedUpdate()
    {

    }

    void Scene::Update(double dt)
    {

        transformSystem_->CalculateMatrices();
        renderSystem_->Render();
    }

    void Scene::PostUpdate()
    {

    }
}
