#pragma once

#include "Mesh.h"

namespace Omega::Graphics
{
	class MeshBuilder
	{
	public:
		static MeshPX CreateCubePX();
		static MeshPX CreatePlanePX(uint32_t col, uint32_t row);
		static MeshPX CreateCylinderPX();
		static MeshPX CreateSpherePX(float radius, int rings = 16, int slices = 16);
	};
}