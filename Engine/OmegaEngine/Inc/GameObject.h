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

		GameObject() noexcept = default;
		//copy constructor
		GameObject(const GameObject&) = delete;
		//copy assigment
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
			auto& newComponent = mComponents.push_back(std::make_unique<ComponentType>());
			newComponent->mOwner = this;
			return static_cast<ComponentType*>(newComponent.get());
		}

		template <class ComponentType>
		constexpr const ComponentType* GetComponent() const
		{
			for (const auto& component : mComponents)
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

		constexpr GameWorld& GetWorld() noexcept { return *mWorld; }
		constexpr const GameWorld& GetWorld() const noexcept { return *mWorld; }

		void SetName(std::string_view name) noexcept { mName = name; }
		constexpr std::string_view GetName() const noexcept { return mName; }

		GameObjectHandle GetHandle() const noexcept { return mHandle; }
	private:
		friend class GameWorld;

		using Components = std::vector<std::unique_ptr<Component>>;
		Components mComponents;
		std::string_view mName = "NoName";

		GameWorld* mWorld = nullptr;
		GameObjectHandle mHandle;
		bool mInitialized = false;
		char padding[3]{};
	};
}