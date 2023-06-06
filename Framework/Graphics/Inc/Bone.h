#pragma once

#include "Common.h"

namespace Omega::Graphics
{
	struct Bone
	{
		std::string name;
		int index = 0;

		Bone* parent = nullptr;
		int parentIndex = -1;

		std::vector<Bone*> children;
		std::vector<uint32_t> childIndices;

		Math::Matrix4 toParentTransform = Math::Matrix4::Identity;
		Math::Matrix4 offsetTransform = Math::Matrix4::Identity;
	};

}