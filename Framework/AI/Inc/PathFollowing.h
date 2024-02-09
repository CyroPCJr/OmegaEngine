#pragma once

#include "Common.h"

namespace Omega::AI
{
	class PathFollowing
	{
	public:

		using WayPoints = std::vector<Omega::Math::Vector2>;
		using CurrentWayPoints = WayPoints;

		PathFollowing(unsigned int numWayPoints) noexcept;
		 
		Omega::Math::Vector2& CurrentWayPoint() const;

		void SetNextWaypoint();

		WayPoints createRandomPath(unsigned int NumWaypoints, const Omega::Math::Vector2& pointsMin, const Omega::Math::Vector2& pointsMax);

		bool isFinished() const;

		bool IsLooped() const;
		void SetLooped(bool active);

		void SetPath(const WayPoints& newPath);
		void SetPath(PathFollowing& path);

		void Clear();

		WayPoints& GetPath();

	private:

		WayPoints mWayPoints{};
		CurrentWayPoints::iterator mCurrentWaypoint = mWayPoints.begin();
		unsigned int mNumWaypoints = 0;
		float radius = 10.0f;
		bool mIsLooped = false;
	};

}
