#include "Precompiled.h"
#include "MeshIO.h"

using namespace Omega::Graphics;

void MeshIO::Write(FILE* file, const SkinnedMesh& mesh, bool binary)
{
	if (binary) //TODO: Testing area
	{
		// to write in binary
		for (auto& vertex : mesh.vertices)
		{
			fwrite(&vertex, sizeof(Vertex), 1, file);
		}

		for (uint32_t i = 0; i < mesh.indices.size(); i += 3)
		{
			fwrite(&i + 0, sizeof(uint32_t), 1, file);
			fwrite(&i + 1, sizeof(uint32_t), 1, file);
			fwrite(&i + 2, sizeof(uint32_t), 1, file);
		}
	}
	else
	{
		fprintf_s(file, "VerticesCount: %d\n", static_cast<uint32_t>(mesh.vertices.size()));
		for (auto& vertex : mesh.vertices)
		{
			fprintf_s(file, "%f %f %f %f %f %f %f %f %f %f %f\n",
				vertex.position.x, vertex.position.y, vertex.position.z,
				vertex.normal.x, vertex.normal.y, vertex.normal.z,
				vertex.tangent.x, vertex.tangent.y, vertex.tangent.z,
				vertex.texcoord.x, vertex.texcoord.y);
			/*,
				vertex.boneIndices[0], vertex.boneIndices[1], vertex.boneIndices[2], vertex.boneIndices[3],
				vertex.boneWeights[0], vertex.boneWeights[1], vertex.boneWeights[2], vertex.boneWeights[3]);
				*/
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

	}

}

void MeshIO::Read(FILE* file, SkinnedMesh& mesh, bool binary)
{
	// to read in binary
	//fread_s()
	if (binary) //TODO: Testing area
	{
		uint32_t numVertices = 0;
		fscanf_s(file, "VerticesCount: %d\n", &numVertices);
		mesh.vertices.resize(numVertices);
		for (auto& v : mesh.vertices)
		{
			fread_s(&v, sizeof(Vertex), numVertices, 1, file);
		}

		uint32_t numIndices = 0;
		fscanf_s(file, "IndexCount: %d\n", &numIndices);
		mesh.indices.resize(numIndices);
		for (uint32_t i = 0; i < numIndices; i += 3)
		{
			fread_s(&mesh.indices[i + 0], sizeof(uint32_t), numIndices, 1, file);
			fread_s(&mesh.indices[i + 1], sizeof(uint32_t), numIndices, 1, file);
			fread_s(&mesh.indices[i + 2], sizeof(uint32_t), numIndices, 1, file);
		}

	}
	else
	{
		uint32_t numVertices = 0;
		fscanf_s(file, "VerticesCount: %d\n", &numVertices);
		mesh.vertices.resize(numVertices);
		for (auto& v : mesh.vertices)
		{
			/*uint32_t bIndex1, bIndex2, bIndex3, bIndex4;
			uint32_t wIndex1, wIndex2, wIndex3, wIndex4;*/
			/*fscanf_s(file, "%f %f %f %f %f %f %f %f %f %f %f %d %d %d %d %f %f %f %f\n",
				&v.position.x, &v.position.y, &v.position.z,
				&v.normal.x, &v.normal.y, &v.normal.z,
				&v.tangent.x, &v.tangent.y, &v.tangent.z,
				&v.texcoord.x, &v.texcoord.y,
				&bIndex1, &bIndex2, &bIndex3, &bIndex4,
				&wIndex1, &wIndex2, &wIndex3, &wIndex4);
			v.boneIndices[0] = bIndex1, v.boneIndices[1] = bIndex2, v.boneIndices[2] = bIndex3, v.boneIndices[3] = bIndex4;
			v.boneWeights[0] = wIndex1, v.boneWeights[1] = wIndex2, v.boneWeights[2] = wIndex3, v.boneWeights[3] = wIndex4;*/

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
}

void MeshIO::Write(FILE* file, const Material& material)
{
	fprintf_s(file, "Ambient: %f %f %f %f\n",
		material.ambient.x, material.ambient.y, material.ambient.z, material.ambient.w);
	fprintf_s(file, "Diffuse: %f %f %f %f\n",
		material.diffuse.x, material.diffuse.y, material.diffuse.z, material.diffuse.w);
	fprintf_s(file, "Specular: %f %f %f %f\n",
		material.specular.x, material.specular.y, material.specular.z, material.specular.w);
	fprintf_s(file, "Power: %f\n", material.power);
}

void MeshIO::Read(FILE* file, Material& material)
{
	fscanf_s(file, "Ambient: %f %f %f %f\n",
		&material.ambient.x, &material.ambient.y, &material.ambient.z, &material.ambient.w);
	fscanf_s(file, "Diffuse: %f %f %f %f\n",
		&material.diffuse.x, &material.diffuse.y, &material.diffuse.z, &material.diffuse.w);
	fscanf_s(file, "Specular: %f %f %f %f\n",
		&material.specular.x, &material.specular.y, &material.specular.z, &material.specular.w);
	fscanf_s(file, "Power: %f\n", &material.power);
}
