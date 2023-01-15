#pragma once

#include "Nare/Scene/Coordinator.h"
#include "Transform.h"
#include "Nare/Scene/Entity.h"
#include "Components.h"
#include "Nare/Renderer/Renderer.h"

namespace Nare
{
    constexpr uint32_t MAX_LIGHTS = 10;

    class RenderSystem : public System
    {
    public:
        inline void Render()
        {
            const auto& coordinator = Coordinator::Instance();
            // Render lights
                
            // Render meshes
            for (const auto& entity : Entities)
                Renderer::RenderMesh(coordinator.GetComponent<RenderMesh>(entity)->mesh, coordinator.GetComponent<Transform>(entity)->worldMatrix);
        }
    };

    class TransformSystem : public System
    {
    public:
        inline void CalculateMatrices()
        {
            const auto& coordinator = Coordinator::Instance();
            for (const auto& entity : Entities)
            {
                const auto& entity_transform = coordinator.GetComponent<Transform>(entity);
                if (entity_transform)
                    calculate_matrices_(entity_transform);
            }
        }

    private:
        inline void calculate_matrices_(Transform* t)
        {
            t->localMatrix = Matrix4x4::TRS(t->position, t->rotation, t->scale);

            const auto& parent_transform = t->parent;
            t->worldMatrix = parent_transform ? parent_transform->worldMatrix * t->localMatrix : t->localMatrix;
            for (const auto& child : t->children)
                calculate_matrices_(child);    
        }

    };

	class Scene
	{
	public:
		Scene();
		~Scene();

        void Init();

        void FixedUpdate();
        void Update(double dt);
        void PostUpdate();
	protected:
		std::vector<Entity> entities_;

        Ref<TransformSystem> transformSystem_;
        Ref<RenderSystem> renderSystem_;

        std::array<Light, MAX_LIGHTS> lights_;
	};

}