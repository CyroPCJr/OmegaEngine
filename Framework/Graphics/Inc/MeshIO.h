#pragma once
#include "Mesh.h"
#include "Material.h"

namespace Omega::Graphics::MeshIO
{
	void Write(FILE* file, const SkinnedMesh& mesh, bool binary = false);
	void Read(FILE* file, SkinnedMesh& mesh, bool binary = false);
	void Write(FILE* file, const Material& material);
	void Read(FILE* file, Material& material);
}