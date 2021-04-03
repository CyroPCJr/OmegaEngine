#pragma once
#include "TileMap.h"

#include <OmegaEngine/Inc/Omega.h>

namespace PathFinding
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
		Omega::Graphics::Camera mCamera;

		TileMap mTileMap;
	};
}