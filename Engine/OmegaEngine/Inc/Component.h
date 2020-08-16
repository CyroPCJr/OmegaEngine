#pragma once

namespace Omega
{
	class GameObject;

	class Component
	{
	public:
		Component() = default;

		Component(const Component&) = delete;
		Component& operator=(const Component&) = delete;

		virtual ~Component() = default;

		virtual void Initialize() {}
		virtual void Terminate() {}

		virtual void Update(float deltaTime) {}
		virtual void Render() {}
		virtual void DebugUI() {}

		GameObject& GetOwner() { return *mOwner; }
		const GameObject& GetOwner() const { return *mOwner; }

	private:
		friend class GameObject;
		GameObject* mOwner = nullptr;
	};

}