#pragma once

#include <OmegaEngine/Inc/Omega.h>
#include "Carrier.h"

namespace HelloPerception
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

		void InitializeWorld();
		void GeneralDebugUI();


		Omega::Graphics::Camera mCamera;

		Omega::AI::AIWorld::Settings mSettings;
		Omega::AI::AIWorld mAIWorld;

		std::unique_ptr<Carrier> mCarrier = nullptr;
	};

}
