#pragma once

#include <OmegaEngine\Inc\Omega.h>

namespace Steering
{
	class Interceptor : public AI::Agent
	{
	public:
		Interceptor(AI::AIWorld& world);
		~Interceptor() override = default;

		void Load();
		void Unload();

		void Update(float deltaTime);
		void Render();

		void DebugUI();

		bool isDebugShowDraw = true;
	private:

		std::unique_ptr<AI::SteeringModule> mSteeringModule = nullptr;

		std::array<Omega::Graphics::TextureId, 32> mTexturesIds;

		float mWidth = 0.0f;
		float mHeight = 0.0f;
	};
}