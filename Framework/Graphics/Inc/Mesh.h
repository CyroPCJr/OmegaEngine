#pragma once

#include "VertexTypes.h"

namespace Omega::Graphics
{
	template<class VertexTypes>
	struct MeshBase
	{
		std::vector<VertexTypes> vertices;
		std::vector<uint32_t> indices;
	};

	using MeshPC = MeshBase<VertexPC>;
	using MeshPX = MeshBase<VertexPX>;
	using MeshPN = MeshBase<VertexPN>;
}