#pragma once
#include "Mesh.h"

namespace Omega::Graphics::MeshIO
{

	void Write(FILE* file, const Mesh& mesh);
	void Read(FILE* file, Mesh& mesh);
}

// For Homework: add MeshIO.cpp and implement Write/Read