#pragma once

#include "Graphics.h"

namespace Omega::Graphics
{
	struct Vertex
	{
		Omega::Math::Vector3 position;
		Omega::Graphics::Color color;
	};

	struct Mesh
	{
		std::vector<Vertex> mVertices;
		std::vector<uint32_t> mIndices;
	};

	class MeshBuffer
	{
	public:
		void Initialize(Vertex* vertices, UINT vertexCount, uint32_t* indices, UINT indexCount);
		void Terminate();

		void Draw();
	private:
		UINT mIndiceCount = 0;
		ID3D11Buffer* mVertexBuffer = nullptr;
		ID3D11Buffer* mIndexBuffer = nullptr;
	};
}