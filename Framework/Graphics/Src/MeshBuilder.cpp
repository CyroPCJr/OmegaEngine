#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace Omega::Graphics;
using namespace Omega::Math;

MeshPX MeshBuilder::CreateCubePX()
{
	MeshPX mMesh;
	// Front
	mMesh.vertices.emplace_back(VertexPX{ Vector3{  0.0f,  0.5f,  -0.5f }, 0.0f, 1.0f });
	mMesh.vertices.emplace_back(VertexPX{ Vector3{  0.5f,  0.0f,  -0.5f }, 0.0f, 0.0f });
	mMesh.vertices.emplace_back(VertexPX{ Vector3{ -0.5f,  0.0f,  -0.5f }, 1.0f, 1.0f });
	mMesh.vertices.emplace_back(VertexPX{ Vector3{  0.0f, -0.5f,  -0.5f }, 1.0f, 0.0f });

	// Back
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

MeshPX MeshBuilder::CreatePlanePX(uint32_t width, uint32_t height)
{
	OMEGAASSERT((width > 1 && height > 1), "To create plane, width and height should be more than 1.");
	MeshPX mMesh;
	const float du = 1.0f / (width - 1);
	const float dv = 1.0f / (height - 1);
	for (int y = 0; y < width; ++y)
	{
		for (int x = 0; x < height; ++x)
		{
			mMesh.vertices.emplace_back(VertexPX{
				Vector3{ static_cast<float>(x), static_cast<float>(y), 0.0f}, static_cast<float>(x)*du, static_cast<float>(y)*dv });
			
			// get the corrnes
			mMesh.indices.push_back(y * height + x);
			mMesh.indices.push_back(y * height + (x + 1));
			mMesh.indices.push_back((y + 1)*height + x);

			mMesh.indices.push_back((y + 1) * height + x);
			mMesh.indices.push_back((y * height + (x + 1)));
			mMesh.indices.push_back((y + 1) * height + (x + 1));
		}
	}
	return mMesh;
}
