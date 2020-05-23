#pragma once

#include "Colors.h"

namespace Omega::Graphics
{
	struct Material
	{
		Color ambient;
		Color diffuse;
		Color specular;
		float power = 0.0f;
		float padding[3]{0.0f};
	};
}