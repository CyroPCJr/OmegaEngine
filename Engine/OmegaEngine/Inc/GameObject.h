
#pragma once

namespace Omega
{
	class Component;
	class GameObject;
	class GameWorld;

	using GameObjectAllocator = Core::TypedAllocator<GameObject>;
	using GameObjectHandle = Core::Handle<GameObject>;
	using GameObjectHandlePool = Core::HandlePool<GameObject>;

	class GameObject final
	{
	public:
		META_CLASS_DECLARE

		GameObject() = default;
		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;

		void Initialize();
		void Terminate();

		void Update(float deltaTime);
		void Render();
		void DebugUI();

		Component* AddComponent(const Core::Meta::MetaClass* metaClass);

		template <class ComponentType>
		ComponentType* AddComponent()
		{
			static_assert(std::is_base_of_v<Component, ComponentType>,
				"[GameObject] -- Cannot add type ComponentType which is not derived from Component.");
			OMEGAASSERT(!mInitialized, "[GameObject] -- Cannot add new components once the game object is already initialized.");
			auto& newComponent = mComponents.emplace_back(std::make_unique<ComponentType>());
			newComponent->mOwner = this;
			return static_cast<ComponentType*>(newComponent.get());
		}

		template <class ComponentType>
		const ComponentType* GetComponent() const
		{
			for (auto& component : mComponents)
			{
				if (component->GetMetaClass() == ComponentType::StaticGetMetaClass())
				{
					return static_cast<const ComponentType*>(component.get());
				}
			}
			return nullptr;
		}

		template <class ComponentType>
		ComponentType* GetComponent()
		{
			auto constMe = static_cast<const GameObject*>(this);
			return const_cast<ComponentType*>(constMe->GetComponent<ComponentType>());
		}

		GameWorld& GetWorld() { return *mWorld; }
		const GameWorld& GetWorld() const { return *mWorld; }

		void SetName(const char* name) { mName = name; }
		std::string& GetName() { return mName; }

		GameObjectHandle GetHandle() const { return mHandle; }
	private:
		friend class GameWorld;

		using Components = std::vector<std::unique_ptr<Component>>;

		GameWorld* mWorld = nullptr;
		std::string mName = "NoName";
		GameObjectHandle mHandle;
		Components mComponents;
		bool mInitialized = false;
	};
}