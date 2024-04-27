#include "Precompiled.h"
#include "AnimationUtil.h"

using namespace Omega::Math;
using namespace Omega::Graphics;

void AnimationUtil::RunFABRIK(std::vector<Vector3>& points, const Vector3& target, unsigned int maxIteration, float errorThreshold)
{
	OMEGAASSERT(points.size() >= 2u, "Not enought points to run FABRIK!");
	std::vector<float> lengths;
	lengths.reserve(points.size() - 1u);
	
	// Record the current point distances, we want to maintain this values when running IK (inverse Kinematic)
	for (size_t i{ 0 }, size = points.size(); i + 1u < size; ++i)
	{
		lengths.emplace_back(Magnitude(points[i + 1] - points[i]));
	}

	RunFABRIK(points, target, lengths, maxIteration, errorThreshold);
}

void AnimationUtil::RunFABRIK(std::vector<Vector3>& points, const Vector3& target, const std::vector<float>& lengths,  unsigned int maxIteration, float errorThreshold)
{
	OMEGAASSERT(points.size() >= 2u, "Not enought points to run FABRIK!");
	const size_t pointSize = points.size();
	// Record the orgin
	const Vector3 origin = points.front();

	// Loop until we are close enought, or have used all iteration
	for (size_t i{ 0 }; i < maxIteration; ++i)
	{
		if (MagnitudeSqr(points.back() - target) < Sqr(errorThreshold))
		{
			break;
		}
		// Run forward pass
		points.back() = target;
		for (size_t j{ pointSize - 2u }; j > 0; --j)
		{
			Vector3 direction = Normalize(points[j + 1] - points[j]);
			points[j] = points[j + 1] - (direction * lengths[j]);
		}

		// Run backward pass
		points.front() = origin;
		for (size_t k{ 0 }; k + 1 < pointSize; ++k)
		{
			Vector3 direction = Normalize(points[k + 1] - points[k]);
			points[k + 1] = points[k] + (direction * lengths[k]);
		}
	}
}
