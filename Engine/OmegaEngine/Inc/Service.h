#pragma once

namespace Omega
{
	class GameWorld;

	class Service
	{
	public:
		Service() = default;
		virtual ~Service() = default;

		virtual void Initialize() {}
		virtual void Terminate() {}

		virtual void Update(float deltaTime) {}
		virtual void Render() {}
		virtual void DebugUI() {}

		GameWorld& GetWorld() { return *mWorld; }
		const GameWorld& GetWorld() const { return *mWorld; }

	private:
		friend class GameWorld;
		GameWorld* mWorld = nullptr;
	};
}
