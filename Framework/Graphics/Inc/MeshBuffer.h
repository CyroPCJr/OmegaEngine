#pragma once

#include "Mesh.h"

namespace Omega::Graphics
{
	class MeshBuffer
	{
	public:
		template<class MeshType>
		void Initialize(const MeshType& mesh)
		{
			Initialize(mesh.vertices.data(),
				static_cast<int>(mesh.vertices.size()),
				mesh.indices.data(),
				static_cast<int>(mesh.indices.size())
			);
		}
		
		template<class VertexType>
		void Initialize(const VertexType* vertices, int vertexCount, const uint32_t* indices, int indexCount)
		{
			Initialize(vertices, sizeof(VertexType), vertexCount, indices, indexCount);
		}

		void Terminate();

		void Draw() const;

	private:
		void Initialize(const void* vertices, int vertexSize,  int vertexCount, const uint32_t* indices, int indexCount);
		ID3D11Buffer* mVertexBuffer = nullptr;
		ID3D11Buffer* mIndexBuffer = nullptr;
		int mVertexSize = 0;
		int mIndiceCount = 0;
	};
}