#pragma once

namespace Omega::Graphics::AnimationUtil
{

	void RunFABRIK(std::vector<Omega::Math::Vector3>& points, const Omega::Math::Vector3& target, int maxIteration = 5, float errorThreshold = 0.00001f);
	void RunFABRIK(std::vector<Omega::Math::Vector3>& points, const Omega::Math::Vector3& target, std::vector<float>& lengths, int maxIteration =5, float errorThreshold = 0.00001f);
}