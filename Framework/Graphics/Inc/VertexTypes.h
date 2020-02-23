#pragma once

#include "Common.h"
#include "Colors.h"

namespace Omega::Graphics
{
	// Vertex element flags
	constexpr uint32_t VE_Position  = 0x1 << 0; // 0000 0001
	constexpr uint32_t VE_Normal    = 0x1 << 1;	// 0000 0010
	constexpr uint32_t VE_Tangent   = 0x1 << 2;	// 0000 0100
	constexpr uint32_t VE_Color     = 0x1 << 3;	// 0000 1000
	constexpr uint32_t VE_TextCoord = 0x1 << 4;	// 0001 0000

#define VERTEX_FORMAT(fmt)\
	static constexpr uint32_t Format = fmt

	// Position and color;
	struct VertexPC
	{
		VERTEX_FORMAT(VE_Position | VE_Color);
		Math::Vector3 position;
		Color color;
	};
	
	// Position and coordinate
	struct VertexPX
	{
		VERTEX_FORMAT(VE_Position | VE_TextCoord);
		Math::Vector3 position;
		float u, v;
	};

	// Position and Normal
	struct VertexPN
	{
		VERTEX_FORMAT(VE_Position | VE_Normal);
		Math::Vector3 position;
		Math::Vector3 normal;
	};

	struct Vertex
	{
		VERTEX_FORMAT(VE_Position | VE_Normal | VE_Tangent | VE_TextCoord);
		Math::Vector3 position;
		Math::Vector3 normal;
		Math::Vector3 tangent;
		Math::Vector2 texcoord;
	};

}
