#pragma once
#include "Interceptor.h"

namespace FinalProject
{
	class Hive
	{
	public:
		void Initialize(AI::AIWorld& world);
		void Terminate();
		void Update(float deltaTime);
		void Render();
	private:
		X::Math::Vector2 position{};
		const int maxInterceptor = 5;
		std::vector<std::unique_ptr<Interceptor>> mInterceptorList;
	};

}