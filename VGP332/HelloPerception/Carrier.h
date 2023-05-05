#pragma once

#include <OmegaEngine\Inc\Omega.h>

namespace HelloPerception
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

		Carrier(Omega::AI::AIWorld& world);
		~Carrier() override = default;

		void Load();
		void Unload();

		void Update(float deltaTime);
		void Render();

		void SwitchBehaviour(const Behaviours& behaviours, bool active = true) const;
		void SetSlowRadius(float radius) { mSlowRadius = radius; }

		void SetDebugDraw(bool show) { mDebugShowDraw = show; }
		bool IsDebugDraw() const { return mDebugShowDraw; }

	private:
		std::unique_ptr<Omega::AI::PerceptionModule> mPerceptionModule = nullptr;
		std::unique_ptr<Omega::AI::SteeringModule> mSteeringModule = nullptr;
		Omega::AI::VisualSensor* mVisualSensor = nullptr;
		std::array<Omega::Graphics::TextureId, 32> mTexturesIds;
		float mSlowRadius = 100.0f;
		bool mDebugShowDraw = true;
	};

}