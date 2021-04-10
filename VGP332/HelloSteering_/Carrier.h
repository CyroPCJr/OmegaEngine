#pragma once

#include <AI.h>

#include <Agent.h>

namespace Steering
{
	class AIWorld;

	class Carrier : public AI::Agent
	{
	public:
		Carrier(AI::AIWorld& world);
		~Carrier() override = default;

		void Load();
		void Unload();

		void Update(float deltaTime);
		void Render();

		void DebugUI();
	private:
		std::unique_ptr<AI::SteeringModule> mSteeringModule = nullptr;
		std::array<X::TextureId, 32> mTexturesIds;


		int mActive = 0;
		float mWidth = 0.0f;
		float mHeight = 0.0f;
	};



}