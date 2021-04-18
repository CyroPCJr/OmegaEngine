#include "Precompiled.h"
#include "PursuitBehaviour.h"
#include "Agent.h"

using namespace AI;
using namespace Omega::Graphics;
using namespace Omega::Math;

Vector2 PursuitBehaviour::Calculate(AI::Agent& agent)
{
	if (!agent.threat)
	{
		return Vector2::Zero;
	}

	Vector2 toEvader = agent.threat->position - agent.position;
	float relativeHeading = Dot(agent.heading, agent.threat->heading);

	if (Dot(toEvader, agent.heading) > 0.0f && relativeHeading < -0.95f)
	{
		return mTargetDebug = Seek(agent, agent.threat->position);
	}

	float lookAheadTime = Magnitude(toEvader) / (agent.maxSpeed + Magnitude(agent.threat->velocity));
	lookAheadTime += TurnAroundTime(agent, agent.threat->position);
	// Seek formula
	return mTargetDebug = Seek(agent, agent.threat->position + agent.threat->velocity * lookAheadTime);
}

void AI::PursuitBehaviour::ShowDebugDraw(const Agent& agent)
{
	SimpleDraw::AddScreenLine(agent.position, agent.threat->position, Colors::Red);

}

float AI::PursuitBehaviour::TurnAroundTime(const AI::Agent& agent, const Vector2& targetPosition)
{
	Vector2 targetPos = Normalize(targetPosition - agent.position);
	const float dot = Dot(agent.heading, targetPos);
	const float coeficient = 0.5f;
	return (dot - 1.0f) * -coeficient;
}
