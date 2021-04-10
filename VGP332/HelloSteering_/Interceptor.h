#pragma once

#include <AI.h>

#include <Agent.h>

namespace Steering
{
	class AIWorld;

	class Interceptor : public AI::Agent
	{
	public:
		Interceptor(AI::AIWorld& world);
		~Interceptor() override = default;

		void Load();
		void Unload();

		void Update(float deltaTime);
		void Render();
		
	private:

		std::unique_ptr<AI::SteeringModule> mSteeringModule = nullptr;

		std::array<X::TextureId, 32> mTexturesIds;

		float mWidth = 0.0f;
		float mHeight = 0.0f;
	};



}