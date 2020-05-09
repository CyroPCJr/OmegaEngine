#pragma once

#include "Skeleton.h"

namespace Omega::Graphics::SkeletonIO
{
	void Write(FILE* file, const Skeleton& skeleton);
	void Read(FILE* file, Skeleton& skeleton);
}