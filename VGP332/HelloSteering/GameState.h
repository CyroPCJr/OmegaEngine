#pragma once

#include "Interceptor.h"
#include "Carrier.h"
#include <OmegaEngine/Inc/Omega.h>

namespace Steering
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
		void SettingInit();
		void GeneralDebugUI();

		Omega::Graphics::Camera mCamera;
		std::vector<std::unique_ptr<Interceptor>> mInterceptorList;

		std::unique_ptr<Carrier> mCarrier = nullptr;

		Omega::AI::AIWorld::Settings mSettings;
		Omega::AI::AIWorld mAIWorld;
		const size_t maxInterceptor = 20;
	};
}