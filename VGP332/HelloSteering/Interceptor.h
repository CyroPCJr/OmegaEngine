#pragma once

#include <OmegaEngine\Inc\Omega.h>

namespace Steering
{
	

	class Interceptor : public AI::Agent
	{
	public:
		enum class Behaviours
		{
			Alignment,
			Cohesion,
			Separation,
			Evade,
			Flee,
			Hide,
			ObstacleAvoidance,
			Pursuit,
			Wandering,
			Interpose
		};


		Interceptor(AI::AIWorld& world) noexcept;
		~Interceptor() override = default;

		void Load();
		void Unload();

		void Update(float deltaTime);
		void Render();

		bool isDebugShowDraw = true;

		void SwitchBehaviour(const Behaviours& behaviours, bool active = true) const;

	private:

		std::unique_ptr<AI::SteeringModule> mSteeringModule = nullptr;

		std::array<Omega::Graphics::TextureId, 32> mTexturesIds;

		/*float mWidth = 0.0f;
		float mHeight = 0.0f;*/
	};
}