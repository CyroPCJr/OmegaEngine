#pragma once

#include "Mesh.h"

namespace Omega::Graphics
{
	class MeshBuilder
	{
	public:
		static MeshPX CreateCubePX();
		static MeshPX CreatePlanePX(uint32_t row, uint32_t col);
		static MeshPX CreateCylinderPX(uint32_t row, uint32_t col, float radius);
		static MeshPX CreateSpherePX(float radius, int rings , int slices , bool isSpace = false);

		static MeshPN CreateaSpherePN(float radius, int rings = 12, int slices = 36 , bool isSpace = false);
	};
}