#include "Precompiled.h"
#include "AnimationUtil.h"

using namespace Omega::Math;
using namespace Omega::Graphics;

void AnimationUtil::RunFABRIK(std::vector<Omega::Math::Vector3>& points, const Omega::Math::Vector3& target, int maxIteration, float errorThreshold)
{
	OMEGAASSERT(points.size() >= 2, "Not enought points to run FABRIK!");
	std::vector<float> lengths;
	lengths.reserve(points.size() - 1);
	
	// Record the current point distances, we want to maintain this values when running IK (inverse Kinematic)
	for (size_t i = 0; i + 1 < points.size(); ++i)
	{
		lengths.push_back(Magnitude(points[i + 1] - points[i]));
	}

	RunFABRIK(points, target, lengths, maxIteration, errorThreshold);
}

void AnimationUtil::RunFABRIK(std::vector<Vector3>& points, const Vector3& target, std::vector<float>& lengths, int maxIteration, float errorThreshold)
{
	OMEGAASSERT(points.size() >= 2, "Not enought points to run FABRIK!");
	const int pointSize = static_cast<int>(points.size());
	// Record the orgin
	Vector3 origin = points.front();

	// Loop until we are close enought, or have used all iteration
	for (int i = 0; i < maxIteration; ++i)
	{
		if (MagnitudeSqr(points.back() - target) < Sqr(errorThreshold))
		{
			break;
		}
		// Run forward pass
		points.back() = target;
		for (int i = pointSize - 2; i >= 0; --i)
		{
			Vector3 direction = Normalize(points[i + 1] - points[i]);
			points[i] = points[i + 1] - (direction * lengths[i]);
		}

		// Run backward pass
		points.front() = origin;
		for (int i = 0; i + 1 < pointSize; ++i)
		{
			Vector3 direction = Normalize(points[i + 1] - points[i]);
			points[i + 1] = points[i] + (direction * lengths[i]);
		}
	}
}
