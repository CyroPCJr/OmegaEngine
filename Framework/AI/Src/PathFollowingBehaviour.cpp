#include "Precompiled.h"
#include <Agent.h>
#include <PathFollowingBehaviour.h>

using namespace Omega::AI;
using namespace Omega::Math;
using namespace Omega::Graphics;

Vector2 PathFollowingBehaviour::Calculate(AI::Agent& agent)
{
	if (mPaths.empty())
	{
		return Vector2::Zero;
	}
	FollowPath(agent);
	return ArriveBehaviour::Calculate(agent);
}

void PathFollowingBehaviour::ShowDebugDraw(const Agent& agent)
{
	SimpleDraw::AddScreenLine(agent.position, agent.destination, Colors::Azure);
}

void PathFollowingBehaviour::SetPaths(const std::vector<Omega::Math::Vector2>& paths)
{
	mPaths = paths;
}

Vector2 PathFollowingBehaviour::PredictFutureLoc(const Agent& agent) const
{
	constexpr float possibleDistanceInFuture = 125.0f;
	Vector2 vel = Normalize(agent.velocity);
	vel *= possibleDistanceInFuture;
	return agent.position + vel;
}

void PathFollowingBehaviour::FollowPath(AI::Agent& agent)
{
	float currentClosest = 100000.0f;
	///closestToShipPointOnPath = normal point is the point on the path, perpendicular to ship (thus closest to the ship) - so its finding point of the pathLine, that is closest to the future location:

	for (size_t i = 0, size = mPaths.size(); i < size; ++i)
	{
		const Vector2 roadBegin = mPaths[i];
		const Vector2 roadEnd = mPaths[(i + 1u) % size]; ///key idea is the wrap around points

		const Vector2 futureLocPoint = PredictFutureLoc(agent);
		///estimate normal point:
		Vector2 normalPoint = GetNormalPoint(futureLocPoint, roadBegin, roadEnd);

		///checking if closestToFuturePointOnPath is on the path (if its not extrapolating beyond path's length):
		///creating temporary QLineF to use QLineF::contains(QPointF) method
		if (const LineSegment tempLine = { roadBegin , roadEnd };
			!Intersect(tempLine, normalPoint))
		{
			normalPoint = roadEnd;
		}

		if (const float distance = Distance(normalPoint, futureLocPoint);
			distance < currentClosest) {
			currentClosest = distance;

			Vector2 pointAheadNormalPoint = roadEnd - roadBegin;
			pointAheadNormalPoint = Normalize(pointAheadNormalPoint);
			pointAheadNormalPoint *= 20.0f;
			agent.destination = normalPoint + pointAheadNormalPoint;
		}
	}
}

Vector2 PathFollowingBehaviour::GetNormalPoint(const Vector2& predictionLocation, const Vector2& pointBegin, const Vector2& pointEnd)
{
	///scalar projection is the length of the vector projection
	///vectorProjected is a vector that starts from roadBegin and ends at ships' future location
	const Vector2 vectorProjected = predictionLocation - pointBegin;
	const Vector2 pathVec = pointEnd - pointBegin;
	Vector2 scalarProjectionVec = Normalize(pathVec);

	/// dotProduct gives the length of the shadow (scalarProjection vector) cast
	const float dotProduct = Dot(vectorProjected, scalarProjectionVec);
	scalarProjectionVec *= dotProduct;

	scalarProjectionVec += pointBegin;
	return scalarProjectionVec;
}
