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
				static_cast<int>(mesh.vertices.size()),
				mesh.indices.data(),
				static_cast<int>(mesh.indices.size()),
				dynamic
			);
		}

		template<class VertexType>
		void Initialize(const VertexType* vertices, int vertexCount, bool dynamic = false)
		{
			Initialize(vertices, sizeof(VertexType), vertexCount, nullptr, 0, dynamic);
		}
		
		template<class VertexType>
		void Initialize(const VertexType* vertices, int vertexCount, const uint32_t* indices, int indexCount, bool dynamic = false)
		{
			Initialize(vertices, sizeof(VertexType), vertexCount, indices, indexCount, dynamic);
		}

		void SetTopology(Topology topology);
		void Update(const void* vertexData, uint32_t numVertices);
		void Terminate();
		void Draw() const;

	private:
		void Initialize(const void* vertices, int vertexSize,  int vertexCount, const uint32_t* indices, int indexCount, bool dynamic);

		ID3D11Buffer* mVertexBuffer = nullptr;
		ID3D11Buffer* mIndexBuffer = nullptr;
		//D3D11_PRIMITIVE_TOPOLOGY mTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		D3D11_PRIMITIVE_TOPOLOGY mTopology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		int mVertexSize = 0;
		int mIndiceCount = 0;
		int mVertexCount = 0;
	};
}