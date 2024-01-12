#include <Precompiled.h>
#include <Agent.h>
#include <AIWorld.h>
#include <WallAvoidanceBehaviour.h>

using namespace Omega::AI;
using namespace Omega::Math;
using namespace Omega::Graphics;

Vector2 WallAvoidanceBehaviour::Calculate(AI::Agent& agent)
{
	return WallAvoidance(agent, agent.destination);
}

Vector2 WallAvoidanceBehaviour::WallAvoidance(const AI::Agent& agent, Vector2& destination)
{
	// Access the world throught the agent
	const auto& wallList = agent.world.GetWalls();
	if (wallList.empty())
	{
		return Vector2::Zero;
	}

	CreateFeelers(agent);

	float distance = 0.0f;
	float closestDistance = std::numeric_limits<float>::max();
	////this will hold an index into the vector of walls
	int closestWallIndex = -1;
	Vector2 steeringForce{};
	Vector2	point{};         //used for storing temporary info
	Vector2	closestPoint{}; //holds the closest intersection point
	//examine each feeler in turn
	for (size_t flr = 0, size = mFeelers.size(); flr < size; ++flr)
	{
		Vector2 feeler = mFeelers[flr];
		//run through each wall checking for any intersection points
		for (int w = 0, total = wallList.size(); w < total; ++w)
		{
			if (Intersect(agent.position, feeler, wallList[w].from, wallList[w].to, distance, closestPoint))
			{
				//keep a record of the intersection data
				if (distance < closestDistance)
				{
					closestDistance = distance;
					closestWallIndex = w;

					point = closestPoint;
				}
			}

		}//next wall

		if (closestWallIndex >= 0)
		{
			//calculate the magnitude the agent
			//will overshoot the wall by
			Vector2 over = feeler - point;

			//create a wall avoidance force
			//scaled by the overshoot
			destination = Normal(wallList[closestWallIndex].from, wallList[closestWallIndex].to) * Magnitude(over);
			// seek formula
			Vector2 diseredVel = Normalize(destination - agent.position) * agent.maxSpeed;
			steeringForce = diseredVel - agent.velocity;
			return steeringForce;
		}

	} // next Feelers

	return steeringForce;
}

void WallAvoidanceBehaviour::ShowDebugDraw(const Agent& agent)
{
	SimpleDraw::AddScreenLine(agent.position, mFeelers[0], Colors::Yellow);
	SimpleDraw::AddScreenLine(agent.position, mFeelers[1], Colors::Red);
	SimpleDraw::AddScreenLine(agent.position, mFeelers[2], Colors::Blue);
}

void WallAvoidanceBehaviour::CreateFeelers(const AI::Agent& agent)
{
	//const Vector2 posFeelerLength = agent.position + mDetectionFeelerLength;

	// feelers point straight to front
	mFeelers[0] = agent.position + mDetectionFeelerLength * agent.heading;

	// feelers point straight to left 45º
	Vector2 temp = Rotate(agent.heading, 0.7f);
	mFeelers[1] = agent.position + mDetectionFeelerLength * 0.5f * temp;

	// feelers point straight to right -45º
	temp = Rotate(agent.heading, -0.7f);
	mFeelers[2] = agent.position + mDetectionFeelerLength * 0.5f * temp;
}
