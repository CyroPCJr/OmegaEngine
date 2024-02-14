#pragma once

namespace Omega
{
	class AppState
	{
	public:
		virtual ~AppState() = default;

		virtual void Initialize() {}
		virtual void Terminate() {}

		virtual void Update([[maybe_unused]] float deltaTime) {}
		virtual void Render() {}
		virtual void DebugUI() {}
	};

}