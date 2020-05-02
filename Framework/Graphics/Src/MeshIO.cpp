#include "Precompiled.h"
#include "MeshIO.h"

using namespace Omega::Graphics;

//Referece
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

void MeshIO::Write(FILE* file, const Mesh& mesh)
{
	/*uint32_t numVertices = mesh.vertices.size();
	fprintf_s(file, "%d\n", numVertices);
	for (auto& vertex : mesh.vertices)
	{
		fprintfs_s(file, "?????????", vertex....);
	}*/

	// 100
	// 2.3 4.5 7.9 .....
	// 2.3 4.5 7.9 .....
	// 2.3 4.5 7.9 .....
	// 2.3 4.5 7.9 .....
	// 2.3 4.5 7.9 .....
	// 2.3 4.5 7.9 .....

	uint32_t numVertices = static_cast<uint32_t>(mesh.vertices.size());
	fprintf_s(file, "VerticesCount: %d\n", numVertices);

	for (auto& vertex : mesh.vertices)
	{
		fprintf_s(file, "v %f %f %f %f %f %f %f %f %f %f %f\n",
			vertex.position.x, vertex.position.y, vertex.position.z,
			vertex.normal.x, vertex.normal.y, vertex.normal.z,
			vertex.tangent.x, vertex.tangent.y, vertex.tangent.z,
			vertex.texcoord.x, vertex.texcoord.y);
	}

	fprintf_s(file, "\n\nFaces definition.\n\n");
	uint32_t indicesSize = static_cast<uint32_t>(mesh.indices.size());
	for (uint32_t i = 0; i < indicesSize; i += 3)
	{
		fprintf_s(file, "f %d/%d/%d",
			mesh.indices[i + 0],
			mesh.indices[i + 1],
			mesh.indices[i + 2]);
	}



	// old code
	//const bool containPosition = (mesh.vertices[0].position.x ||
	//	mesh.vertices[0].position.y ||
	//	mesh.vertices[0].position.z) != 0.0f;

	//const bool containNormal = (mesh.vertices[0].normal.x ||
	//	mesh.vertices[0].normal.y ||
	//	mesh.vertices[0].normal.z) != 0.0f;

	//const bool containTextcoord = (mesh.vertices[0].texcoord.x ||
	//	mesh.vertices[0].texcoord.y) != 0.0f;

	//const bool containTangent = (mesh.vertices[0].tangent.x ||
	//	mesh.vertices[0].tangent.y ||
	//	mesh.vertices[0].tangent.z) != 0.0f;


	//if (containPosition)
	//{
	//	for (auto& vertex : mesh.vertices)
	//	{
	//		fprintf_s(file, "v %f %f %f\n", vertex.position.x, vertex.position.y, vertex.position.z);
	//	}
	//}

	//if (containNormal)
	//{
	//	for (auto& vertex : mesh.vertices)
	//	{
	//		fprintf_s(file, "vn %f %f %f\n", vertex.normal.x, vertex.normal.y, vertex.normal.z);
	//	}
	//}

	//if (containTextcoord)
	//{
	//	for (auto& vertex : mesh.vertices)
	//	{
	//		fprintf_s(file, "vt %f %f %f\n", vertex.texcoord.x, vertex.texcoord.y, 0.0f);
	//	}
	//}

	//if (containTangent)
	//{
	//	for (auto& vertex : mesh.vertices)
	//	{
	//		fprintf_s(file, " %f %f %f\n", vertex.tangent.x, vertex.tangent.y, vertex.tangent.z);
	//	}
	//}

	//fprintf_s(file, "\n\nFaces definition.\n\n");
	//uint32_t indicesSize = mesh.indices.size();
	////TODO: ta confuso isso, perguntar para o Peter
	////https://www.braynzarsoft.net/viewtutorial/q16390-22-loading-static-3d-models-obj-format
	//if (containPosition && containTextcoord && containNormal)
	//{
	//	for (uint32_t i = 0; i + 2 < indicesSize; ++i)
	//	{
	//		fprintf_s(file, "f %d/%d/%d", mesh.indices[i], mesh.indices[i + 1], mesh.indices[i + 2]);
	//		fprintf_s(file, " %d/%d/%d", mesh.indices[i + 3], mesh.indices[i + 4], mesh.indices[i + 5]);
	//		fprintf_s(file, " %d/%d/%d\n", mesh.indices[i + 6], mesh.indices[i + 7], mesh.indices[i + 8]);
	//	}
	//}

	//if (containPosition && containNormal)
	//{
	//	for (uint32_t i = 0; i + 2 < indicesSize; ++i)
	//	{
	//		fprintf_s(file, "f %d/%d/%d", mesh.indices[i], mesh.indices[i + 1], mesh.indices[i + 2]);
	//		fprintf_s(file, " %d/%d/%d", mesh.indices[i + 3], mesh.indices[i + 4], mesh.indices[i + 5]);
	//		fprintf_s(file, " %d/%d/%d\n", mesh.indices[i + 6], mesh.indices[i + 7], mesh.indices[i + 8]);
	//	}
	//}

	////%d/%d/%d %d/%d/%d


}

void MeshIO::Read(FILE* file, Mesh& mesh)
{
	std::vector<uint32_t> positionIndices, normalIndices, uvIndices;
	std::vector<Math::Vector3> positions;
	std::vector<Math::Vector3> normals;
	std::vector<Math::Vector2> uvs;

	uint32_t numVertices = 0;
	fscanf_s(file, "VerticesCount: %d", &numVertices);
	mesh.vertices.resize(numVertices);
	for (uint32_t i = 0; i < numVertices; ++i)
	{
		char buffer[128];
		int res = fscanf_s(file, "%", static_cast<unsigned int>(std::size(buffer)));
		if (res == EOF)
		{
			break;
		}

		if (strcmp(buffer, "v") == 0)
		{
			Math::Vector3 position;
			fscanf_s(file, "%f %f %f\n", &position.x, &position.y, &position.z);
			positions.push_back(position);
		}
		else if (strcmp(buffer, "vt") == 0)
		{
			Math::Vector2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			uvs.push_back({ uv.x, 1.0f - uv.y });
		}
		else if (strcmp(buffer, "vn") == 0)
		{
			Math::Vector3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normals.push_back(normal);
		}
		else if (strcmp(buffer, "f") == 0)
		{
			uint32_t v[4], t[4], n[4];
			fgets(buffer, static_cast<int>(std::size(buffer)), file);
			if (sscanf_s(buffer, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
				&v[0], &t[0], &n[0],
				&v[1], &t[1], &n[1],
				&v[2], &t[2], &n[2],
				&v[3], &t[3], &n[3]) == 12)
			{
				positionIndices.push_back(v[0]);
				positionIndices.push_back(v[1]);
				positionIndices.push_back(v[2]);

				uvIndices.push_back(t[0]);
				uvIndices.push_back(t[1]);
				uvIndices.push_back(t[2]);

				normalIndices.push_back(n[0]);
				normalIndices.push_back(n[1]);
				normalIndices.push_back(n[2]);

				positionIndices.push_back(v[0]);
				positionIndices.push_back(v[2]);
				positionIndices.push_back(v[3]);

				uvIndices.push_back(t[0]);
				uvIndices.push_back(t[2]);
				uvIndices.push_back(t[3]);

				normalIndices.push_back(n[0]);
				normalIndices.push_back(n[2]);
				normalIndices.push_back(n[3]);
			}
			else if (sscanf_s(buffer, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&v[0], &t[0], &n[0],
				&v[1], &t[1], &n[1],
				&v[2], &t[2], &n[2]) == 9)
			{
				positionIndices.push_back(v[0]);
				positionIndices.push_back(v[1]);
				positionIndices.push_back(v[2]);

				uvIndices.push_back(t[0]);
				uvIndices.push_back(t[1]);
				uvIndices.push_back(t[2]);

				normalIndices.push_back(n[0]);
				normalIndices.push_back(n[1]);
				normalIndices.push_back(n[2]);
			}

		}

		// Reconstruct vertices
		std::vector<Vertex> vertices;
		vertices.reserve(positionIndices.size());
		for (size_t i = 0; i < positionIndices.size(); ++i)
		{
			Vertex vertex;
			vertex.position = positions[positionIndices[i] - 1];
			vertex.normal = normals[normalIndices[i] - 1];
			vertex.texcoord = uvs[uvIndices[i] - 1];
			vertices.emplace_back(vertex);
		}

		std::vector<uint32_t> indices;
		indices.resize(vertices.size());
		std::iota(indices.begin(), indices.end(), 0); // fill 0,1,2,3...

		mesh.vertices = std::move(vertices);
		mesh.indices = std::move(indices);
	}
}