#include "Precompiled.h"
#include "MeshIO.h"

using namespace Omega::Graphics;

void MeshIO::Write(FILE* file, const Mesh& mesh)
{
	fprintf_s(file, "VerticesCount: %d\n", static_cast<uint32_t>(mesh.vertices.size()));
	for (auto& vertex : mesh.vertices)
	{
		fprintf_s(file, "%f %f %f %f %f %f %f %f %f %f %f\n",
			vertex.position.x, vertex.position.y, vertex.position.z,
			vertex.normal.x, vertex.normal.y, vertex.normal.z,
			vertex.tangent.x, vertex.tangent.y, vertex.tangent.z,
			vertex.texcoord.x, vertex.texcoord.y);
	}

	uint32_t indicesSize = static_cast<uint32_t>(mesh.indices.size());
	fprintf_s(file, "IndexCount: %d\n", indicesSize);
	for (uint32_t i = 0; i < indicesSize; i += 3)
	{
		fprintf_s(file, "%i %i %i\n",
			mesh.indices[i + 0],
			mesh.indices[i + 1],
			mesh.indices[i + 2]);
	}

	// to write in binary
	//fwrite()
}

void MeshIO::Read(FILE* file, Mesh& mesh)
{
	// to read in binary
	//fread_s()
	
	uint32_t numVertices = 0;
	fscanf_s(file, "VerticesCount: %d\n", &numVertices);
	mesh.vertices.resize(numVertices);
	for (auto& v : mesh.vertices)
	{
		fscanf_s(file, "%f %f %f %f %f %f %f %f %f %f %f\n",
			&v.position.x, &v.position.y, &v.position.z,
			&v.normal.x, &v.normal.y, &v.normal.z,
			&v.tangent.x, &v.tangent.y, &v.tangent.z,
			&v.texcoord.x, &v.texcoord.y);
	}

	uint32_t numIndices = 0;
	fscanf_s(file, "IndexCount: %d\n", &numIndices);
	mesh.indices.resize(numIndices);
	for (uint32_t i = 0; i < numIndices; i += 3)
	{
		uint32_t a, b, c;
		fscanf_s(file, "%i %i %i\n", &a, &b, &c);
		mesh.indices[i + 0] = a;
		mesh.indices[i + 1] = b;
		mesh.indices[i + 2] = c;
	}
}