#pragma once

#include "Mesh.h"

namespace Omega::Graphics
{
	class MeshBuilder
	{
	public:
		static MeshPX CreateCubePX();
		static MeshPX CreatePlanePX(uint32_t row, uint32_t col);
		static MeshPX CreateCylinderPX(float radius, int rings = 16, int slices = 16);
		static MeshPX CreateSpherePX(float radius, int rings = 16, int slices = 16, bool isSpace = false);
		static MeshPX CreateNDCQuad();

		static MeshPN CreateSpherePN(float radius, int rings = 12, int slices = 36, bool isSpace = false);

		static Mesh CreateSphere(float radius, int rings = 12, int slices = 36, bool isSpace = false);
		static Mesh CreatePlane(float size, uint32_t row = 16, uint32_t column = 16);
	};
}