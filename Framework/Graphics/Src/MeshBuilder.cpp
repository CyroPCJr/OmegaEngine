#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace Omega::Graphics;
using namespace Omega::Math;

MeshPX MeshBuilder::CreateCubePX()
{
	MeshPX mMesh;
	mMesh.vertices.emplace_back(VertexPX{ Vector3{  0.0f,  0.5f,  -0.5f }, 0.0f, 1.0f });
	mMesh.vertices.emplace_back(VertexPX{ Vector3{  0.5f,  0.0f,  -0.5f }, 0.0f, 0.0f });
	mMesh.vertices.emplace_back(VertexPX{ Vector3{ -0.5f,  0.0f,  -0.5f }, 1.0f, 1.0f });
	mMesh.vertices.emplace_back(VertexPX{ Vector3{  0.0f, -0.5f,  -0.5f }, 1.0f, 0.0f });

	mMesh.vertices.emplace_back(VertexPX{ Vector3{  0.0f,  0.5f,  0.5f }, 1.0f, 0.0f });
	mMesh.vertices.emplace_back(VertexPX{ Vector3{  0.5f,  0.0f,  0.5f }, 0.0f, 0.0f });
	mMesh.vertices.emplace_back(VertexPX{ Vector3{ -0.5f,  0.0f,  0.5f }, 1.0f, 1.0f });
	mMesh.vertices.emplace_back(VertexPX{ Vector3{  0.0f, -0.5f,  0.5f }, 1.0f, 0.0f });

	// Front
	mMesh.indices.push_back(0);
	mMesh.indices.push_back(1);
	mMesh.indices.push_back(2);
	mMesh.indices.push_back(1);
	mMesh.indices.push_back(3);
	mMesh.indices.push_back(2);
	// Right
	mMesh.indices.push_back(4);
	mMesh.indices.push_back(6);
	mMesh.indices.push_back(5);
	mMesh.indices.push_back(6);
	mMesh.indices.push_back(7);
	mMesh.indices.push_back(5);
	// Back
	mMesh.indices.push_back(4);
	mMesh.indices.push_back(5);
	mMesh.indices.push_back(0);
	mMesh.indices.push_back(0);
	mMesh.indices.push_back(5);
	mMesh.indices.push_back(1);
	// Left
	mMesh.indices.push_back(2);
	mMesh.indices.push_back(3);
	mMesh.indices.push_back(6);
	mMesh.indices.push_back(6);
	mMesh.indices.push_back(3);
	mMesh.indices.push_back(7);
	// Top
	mMesh.indices.push_back(4);
	mMesh.indices.push_back(0);
	mMesh.indices.push_back(6);
	mMesh.indices.push_back(6);
	mMesh.indices.push_back(0);
	mMesh.indices.push_back(2);
	// Botton
	mMesh.indices.push_back(1);
	mMesh.indices.push_back(5);
	mMesh.indices.push_back(3);
	mMesh.indices.push_back(3);
	mMesh.indices.push_back(5);
	mMesh.indices.push_back(7);

	return mMesh;
}