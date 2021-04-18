#include "Precompiled.h"
#include "WanderBehaviour.h"
#include "Agent.h"

//#include <XEngine.h>

using namespace AI;
using namespace Omega::Graphics;
using namespace Omega::Math;

Vector2 WanderBehaviour::Calculate(Agent& agent)
{
	// Create local target over the circle, moving randomly
	mLocalTarget += Random::RandomUnitCircle() * mSettings.jitter;
	mLocalTarget = Normalize(mLocalTarget) * mSettings.radius;

	auto wanderTarget = mLocalTarget + Vector2{ 0.0f, mSettings.distance };
	mCircleJitter = TransformCoord(wanderTarget, agent.LocalToWorld());

	Vector2 center = wanderTarget - mLocalTarget;
	mCircleProjection = TransformCoord(center, agent.LocalToWorld());

	return Seek(agent, mCircleJitter);
}

void AI::WanderBehaviour::ShowDebugDraw(const Agent& agent)
{
	// Create circle ahead toward the agent
	SimpleDraw::AddScreenCircle(mCircleProjection, mSettings.radius, Colors::BlueViolet);
	// Just draw the target over the circle
	SimpleDraw::AddScreenCircle(mCircleJitter, mSettings.radius * 0.25f, Colors::Yellow);
}
