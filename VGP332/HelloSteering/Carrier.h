#pragma once

#include <OmegaEngine\Inc\Omega.h>

namespace Steering
{
	class Carrier : public Omega::AI::Agent
	{
	public:

		enum class Behaviours
		{
			Seek,
			Arrive,
			ObstacleAvoidance
		};

		Carrier(Omega::AI::AIWorld& world) noexcept;
		~Carrier() override = default;

		void Load();
		void Unload();

		void Update(float deltaTime);
		void Render();

		void SwitchBehaviour(const Behaviours& behaviours, bool active = true) const;
		void SetSlowRadius(float radius) { mSlowRadius = radius; }

		bool isDebugShowDraw = true;
	private:
		std::unique_ptr<Omega::AI::SteeringModule> mSteeringModule = nullptr;
		std::array<Omega::Graphics::TextureId, 32> mTexturesIds;
		float mSlowRadius = 100.0f;
	};

}