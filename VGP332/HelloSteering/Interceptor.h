#pragma once

#include <OmegaEngine\Inc\Omega.h>

namespace Steering
{

	class Interceptor final: public Omega::AI::Agent
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


		Interceptor(Omega::AI::AIWorld& world);
		~Interceptor() override = default;

		void Load();
		void Unload() noexcept;

		void Update(float deltaTime);
		void Render();

		bool isDebugShowDraw = true;

		void SwitchBehaviour(const Behaviours& behaviours, bool active = true) const;

	private:

		std::unique_ptr<Omega::AI::SteeringModule> mSteeringModule = nullptr;

		std::array<Omega::Graphics::TextureId, 32> mTexturesIds{0};

		/*float mWidth = 0.0f;
		float mHeight = 0.0f;*/
	};
}