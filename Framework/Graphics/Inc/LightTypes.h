#pragma once

#include "Colors.h"

namespace Omega::Graphics
{
	// This need to be 16 bytes aligned to be HLSL compliant
	struct DirectionalLight
	{
		// <--      16      -->
		// [direction][padding]
		// [     ambient      ] 
		// [     diffuse      ] 
		// [     specular     ] 
		Math::Vector3 direction;
		float padding;
		Color ambient;
		Color diffuse;
		Color specular;
	};

}