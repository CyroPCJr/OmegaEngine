#include <Precompiled.h>
#include <PathFollowing.h>

using namespace Omega::AI;
using namespace Omega::Math;

PathFollowing::PathFollowing(unsigned int numWayPoints) noexcept:
	mNumWaypoints(numWayPoints), mCurrentWaypoint(mWayPoints.begin())
{}

Vector2& PathFollowing::CurrentWayPoint() const
{
	return *mCurrentWaypoint;
}

void PathFollowing::SetNextWaypoint()
{
	if (++mCurrentWaypoint == mWayPoints.end())
	{
		if (mIsLooped)
		{
			mCurrentWaypoint = mWayPoints.begin();
		}
	}
}

PathFollowing::WayPoints PathFollowing::createRandomPath(unsigned int NumWaypoints, const Vector2& pointsMin, const Vector2& pointsMax)
{
	mWayPoints.clear();

	const float midX = (pointsMax.x + pointsMin.x) * 0.5f;
	const float midY = (pointsMax.y + pointsMin.y) * 0.5f;

	const float smaller = Min(midX, midY);

	const float spacing = Constants::TwoPi / static_cast<float>(NumWaypoints);

	for (size_t i = 0; i < NumWaypoints; ++i)
	{
		const float RadialDist = Random::RandomFloat(smaller * 0.2f, smaller);

		Vector2 temp(RadialDist, 0.0f);

		Rotate(temp, i * spacing);

		temp.x += midX;
		temp.y += midY;

		mWayPoints.push_back(temp);
	}

	mCurrentWaypoint = mWayPoints.begin();

	return mWayPoints;
}

bool Omega::AI::PathFollowing::isFinished() const
{
	return !(mCurrentWaypoint != mWayPoints.end());
}

bool PathFollowing::IsLooped() const
{
	return mIsLooped;
}

void PathFollowing::SetLooped(bool active)
{
	mIsLooped = active;
}

void PathFollowing::SetPath(const WayPoints& newPath)
{
	mWayPoints = newPath;
}

void PathFollowing::SetPath(PathFollowing& path)
{
	mWayPoints = path.GetPath();
}

void PathFollowing::Clear()
{
	mWayPoints.clear();
}

PathFollowing::WayPoints& Omega::AI::PathFollowing::GetPath()
{
	return mWayPoints;
}




