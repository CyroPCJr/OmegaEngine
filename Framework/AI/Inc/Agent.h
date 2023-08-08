#pragma once

#include "Entity.h"

namespace Omega::AI
{
	
	class Agent;
	using AgentList = std::vector<Agent*>;

	class Agent: public AI::Entity
	{
	public:
		Agent(AIWorld& world, uint32_t typeId) noexcept;
		~Agent() override = default;

		Agent* threat = nullptr;
		AgentList neighbors;
		Omega::Math::Vector2 velocity = Omega::Math::Vector2::Zero;
		Omega::Math::Vector2 destination = Omega::Math::Vector2::YAxis;
		float maxSpeed = 1.0f;
		float mass = 1.0f;
	};

}