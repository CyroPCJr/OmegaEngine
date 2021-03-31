#pragma once

#include <OmegaEngine\Inc\Omega.h>

namespace FSM
{
	class GameState : public Omega::AppState
	{
	public:
		void Initialize() override;
		void Terminate() override;

		void Update(float deltaTime) override;
		void Render() override;
		void DebugUI() override;
	private:
		void DrawScene();
	};
}