#pragma once

//#define SET_COMPONENT_ID(id)\
//	static uint32_t StaticGetTypeId() {return id;}\
//	uint32_t GetTypeId() const override {return id;}


namespace Omega
{
	class GameObject;

	class Component
	{
	public:
		META_CLASS_DECLARE

		Component() = default;

		Component(const Component&) = delete;
		Component& operator=(const Component&) = delete;

		virtual ~Component() = default;

		//virtual uint32_t GetTypedId() const = 0;

		virtual void Initialize() {}
		virtual void Terminate() {}

		virtual void Update([[maybe_unused]] float deltaTime) {}
		virtual void Render() {}
		virtual void DebugUI() {}

		GameObject& GetOwner() noexcept { return *mOwner; }
		constexpr GameObject& GetOwner() const noexcept { return *mOwner; }

	private:
		friend class GameObject;
		GameObject* mOwner = nullptr;
	};

}