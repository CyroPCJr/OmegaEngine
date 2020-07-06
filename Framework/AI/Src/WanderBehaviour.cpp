#include "Precompiled.h"
#include "WanderBehaviour.h"
#include "Agent.h"

//#include <XEngine.h>

using namespace AI;
using namespace Omega::Graphics;
using namespace Omega::Math;

Vector2 WanderBehaviour::Calculate(Agent & agent)
{
	// Create circle ahead toward the agent
	Vector2 circle = (agent.heading * mSettings.distance) + agent.position;
	SimpleDraw::AddScreenCircle(circle, mSettings.radius, Colors::BlueViolet);

	// Create local target over the circle, moving randomly
	mLocalTarget += Vector2(Random::RandomFloat(-1.0f, 1.0f) *mSettings.jitter, Random::RandomFloat(-1.0f, 1.0f)*mSettings.jitter);
	mLocalTarget = Normalize(mLocalTarget) * mSettings.radius;

	auto wanderTarget = mLocalTarget + Vector2(0.0f, mSettings.distance);
	auto localToWorld = agent.LocalToWorld();
	Vector2 destination = TransformCoord(wanderTarget, localToWorld);
	agent.destination = destination;
	
	// Just draw the target over the circle
	SimpleDraw::AddScreenCircle(agent.destination, mSettings.radius * 0.25f, Colors::Yellow);
	// call the seek formula
	Vector2 desiredVelocity = Normalize(agent.destination - agent.position) * agent.maxSpeed;
	return (desiredVelocity - agent.velocity);
}