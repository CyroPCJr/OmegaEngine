#pragma once

#include "VertexTypes.h"

namespace Omega::Graphics
{
	template<class VertexTypes>
	struct MeshBase
	{
		std::vector<VertexTypes> vertices;
		std::vector<uint32_t> indices;

		constexpr VertexTypes& GetVertex(uint32_t index) 
		{
			return vertices[index];
		}

		constexpr uint32_t GetIndices(uint32_t index) const
		{
			return indices[index];
		}
	};

	using MeshPC = MeshBase<VertexPC>;
	using MeshPX = MeshBase<VertexPX>;
	using MeshPN = MeshBase<VertexPN>;
	using Mesh = MeshBase<Vertex>;
	using SkinnedMesh = MeshBase<BoneVertex>;
}