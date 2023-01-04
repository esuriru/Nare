#pragma once

#include "nrpch.h"

#include "ComponentManager.h"
#include "SystemManager.h"
#include "Entity.h"

namespace Nare
{
	class Coordinator
	{
	public:
		void Init();

		Entity CreateEntity();

		void DestroyEntity(Entity entity);

#pragma region TEMPLATE_FUNCTIONS
		template<typename T>
		inline void RegisterComponent() const
		{
			componentManager_->RegisterComponent<T>();
		}

		template<typename T>
		inline void AddComponent(Entity entity, T component)
		{
			componentManager_->AddComponent<T>(entity, component);

			auto signature = entityManager_->GetSignature(entity);
			signature.set(componentManager_->GetComponentType<T>, false);
			entityManager_->SetSignature(entity, signature);

			systemManager_->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		inline void RemoveComponent(Entity entity)
		{
			componentManager_->RemoveComponent<T>(entity);

			auto signature = entityManager_->GetSignature(entity);
			signature.set(componentManager_->GetComponentType<T>(), false);
			entityManager_->SetSignature(entity, signature);

			systemManager_->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		inline T& GetComponent(Entity entity)
		{
			return componentManager_->GetComponent<T>(entity);
		}

		template<typename T>
		inline ComponentType GetComponentType()
		{
			return componentManager_->GetComponentType<T>();
		}

		template<typename T>
		inline std::shared_ptr<T> RegisterSystem()
		{
			return systemManager_->RegisterSystem<T>();
		}

		template<typename T>
		inline void SetSystemSignature(Signature signature)
		{
			systemManager_->SetSignature<T>(signature);
		}
#pragma endregion TEMPLATE_FUNCTIONS
	private:
		std::unique_ptr<EntityManager> entityManager_;
		std::unique_ptr<ComponentManager> componentManager_;
		std::unique_ptr<SystemManager> systemManager_;

	};
}