#pragma once
#include "Mesh.h"
#include "Material.h"

namespace Omega::Graphics::MeshIO
{
	void Write(FILE* file, const Mesh& mesh, bool binary = false);
	void Read(FILE* file, Mesh& mesh, bool binary = false);
	void Write(FILE* file, const Material& material);
	void Read(FILE* file, Material& material);
}