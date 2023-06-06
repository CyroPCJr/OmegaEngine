#pragma once

#include "Mesh.h"

namespace Omega::Graphics
{
	class MeshBuffer
	{
	public:
		enum class Topology
		{
			Lines,
			Triangles
		};

		template<class MeshType>
		void Initialize(const MeshType& mesh, bool dynamic = false)
		{
			Initialize(mesh.vertices.data(),
				static_cast<unsigned int>(mesh.vertices.size()),
				mesh.indices.data(),
				static_cast<unsigned int>(mesh.indices.size()),
				dynamic
			);
		}

		template<class VertexType>
		void Initialize(const VertexType* vertices, unsigned int vertexCount, bool dynamic = false)
		{
			Initialize(vertices, sizeof(VertexType), vertexCount, nullptr, 0, dynamic);
		}
		
		template<class VertexType>
		void Initialize(const VertexType* vertices, unsigned int vertexCount, const uint32_t* indices, unsigned int indexCount, bool dynamic = false)
		{
			Initialize(vertices, sizeof(VertexType), vertexCount, indices, indexCount, dynamic);
		}

		void SetTopology(Topology topology);
		void Update(const void* vertexData, uint32_t numVertices);
		void Terminate();
		void Draw() const;

	private:
		void Initialize(const void* vertices, unsigned int vertexSize, unsigned int vertexCount, const uint32_t* indices, unsigned int indexCount, bool dynamic);

		ID3D11Buffer* mVertexBuffer = nullptr;
		ID3D11Buffer* mIndexBuffer = nullptr;
		D3D11_PRIMITIVE_TOPOLOGY mTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		unsigned int mVertexSize = 0;
		unsigned int mIndiceCount = 0;
		unsigned int mVertexCount = 0;
	};
}