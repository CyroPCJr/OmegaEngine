#pragma once

#include <OmegaEngine\Inc\Omega.h>

namespace Steering
{
	class Carrier final: public Omega::AI::Agent
	{
	public:

		enum class Behaviours
		{
			Seek,
			Arrive,
			ObstacleAvoidance,
			WallAvoidance,
			PathFollowing,
		};

		Carrier(Omega::AI::AIWorld& world);
		~Carrier() override = default;

		void Load();
		void Unload() noexcept;

		void Update(float deltaTime);
		void Render();

		void SwitchBehaviour(const Behaviours& behaviours, bool active = true) const;
		void SetSlowRadius(float slowRadius) noexcept { Entity::radius = slowRadius; }

		bool isDebugShowDraw = true;
	private:

		std::unique_ptr<Omega::AI::SteeringModule> mSteeringModule = nullptr;
		std::array<Omega::Graphics::TextureId, 32> mTexturesIds{0};
	};

}