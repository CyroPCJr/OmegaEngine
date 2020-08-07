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
		GameObject() = default;

		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;

		void Initialize();
		void Terminate();

		void Update(float deltaTime);
		void Render();
		void DebugUI();

		template <class T, class = std::void_t<std::is_base_of<Component, T>>>
		T* AddComponent()
		{
			auto& newComponent = mComponents.emplace_back(std::make_unique<T>());
			newComponent->mOwner = this;
			return static_cast<T*>(newComponent.get());
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
	};
}