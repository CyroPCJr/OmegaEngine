#pragma once

namespace Omega
{
	class GameWorld;

	class Service
	{
	public:
		META_CLASS_DECLARE;

		Service() = default;
		virtual ~Service() = default;

		virtual void Initialize() {}
		virtual void Terminate() {}

		virtual void Update([[maybe_unused]] float deltaTime) {}
		virtual void Render() {}
		virtual void DebugUI() {}

		GameWorld& GetWorld() noexcept { return *mWorld; }
		const GameWorld& GetWorld() const noexcept { return *mWorld; }

	private:
		friend class GameWorld;
		GameWorld* mWorld = nullptr;
	};
}
