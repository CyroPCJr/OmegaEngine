#pragma once

#include "Colors.h"

namespace Omega::Graphics
{
	struct Material
	{
		Color ambient;
		Color diffuse;
		Color specular;
		float power;
		float padding[3];
	};
}