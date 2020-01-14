#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace Omega::Graphics;
using namespace Omega::Math;

MeshPX MeshBuilder::CreateCubePX()
{
	MeshPX mesh;
	// Front
	mesh.vertices.emplace_back(VertexPX{ Vector3{ -1.0f,  1.0f, -1.0f }, 0.0f, 0.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{  1.0f,  1.0f, -1.0f }, 1.0f, 0.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{ -1.0f, -1.0f, -1.0f }, 0.0f, 1.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{  1.0f, -1.0f, -1.0f }, 1.0f, 1.0f });
	// Right
	mesh.vertices.emplace_back(VertexPX{ Vector3{  1.0f,  1.0f, -1.0f }, 0.0f, 0.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{  1.0f,  1.0f,  1.0f }, 1.0f, 0.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{  1.0f, -1.0f, -1.0f }, 0.0f, 1.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{  1.0f, -1.0f,  1.0f }, 1.0f, 1.0f });
	// Back
	mesh.vertices.emplace_back(VertexPX{ Vector3{  1.0f,  1.0f,  1.0f }, 0.0f, 0.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{ -1.0f,  1.0f,  1.0f }, 1.0f, 0.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{  1.0f, -1.0f,  1.0f }, 0.0f, 1.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{ -1.0f, -1.0f,  1.0f }, 1.0f, 1.0f });
	// Left
	mesh.vertices.emplace_back(VertexPX{ Vector3{  -1.0f,  1.0f,  1.0f }, 0.0f, 0.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{  -1.0f,  1.0f, -1.0f }, 1.0f, 0.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{  -1.0f, -1.0f,  1.0f }, 0.0f, 1.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{  -1.0f, -1.0f, -1.0f }, 1.0f, 1.0f });
	// Top
	mesh.vertices.emplace_back(VertexPX{ Vector3{ -1.0f,  1.0f,  1.0f }, 0.0f, 0.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{  1.0f,  1.0f,  1.0f }, 1.0f, 0.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{  1.0f,  1.0f, -1.0f }, 0.0f, 1.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{ -1.0f,  1.0f, -1.0f }, 1.0f, 1.0f });
	// Botton
	mesh.vertices.emplace_back(VertexPX{ Vector3{  1.0f, -1.0f, -1.0f }, 0.0f, 0.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{ -1.0f, -1.0f, -1.0f }, 1.0f, 0.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{ -1.0f, -1.0f,  1.0f }, 0.0f, 1.0f });
	mesh.vertices.emplace_back(VertexPX{ Vector3{  1.0f, -1.0f,  1.0f }, 1.0f, 1.0f });
	// Front
	mesh.indices.push_back(0);
	mesh.indices.push_back(1);
	mesh.indices.push_back(2);
	mesh.indices.push_back(1);
	mesh.indices.push_back(3);
	mesh.indices.push_back(2);
	// Right
	mesh.indices.push_back(4);
	mesh.indices.push_back(5);
	mesh.indices.push_back(6);
	mesh.indices.push_back(5);
	mesh.indices.push_back(7);
	mesh.indices.push_back(6);
	// Back
	mesh.indices.push_back(8);
	mesh.indices.push_back(9);
	mesh.indices.push_back(10);
	mesh.indices.push_back(9);
	mesh.indices.push_back(11);
	mesh.indices.push_back(10);
	// Left
	mesh.indices.push_back(12);
	mesh.indices.push_back(13);
	mesh.indices.push_back(14);
	mesh.indices.push_back(13);
	mesh.indices.push_back(15);
	mesh.indices.push_back(14);
	// Top
	mesh.indices.push_back(16);
	mesh.indices.push_back(17);
	mesh.indices.push_back(18);
	mesh.indices.push_back(17);
	mesh.indices.push_back(18);
	mesh.indices.push_back(16);
	// Botton
	mesh.indices.push_back(21);
	mesh.indices.push_back(20);
	mesh.indices.push_back(22);
	mesh.indices.push_back(20);
	mesh.indices.push_back(22);
	mesh.indices.push_back(21);

	return mesh;
}

MeshPX MeshBuilder::CreatePlanePX(uint32_t row, uint32_t col)
{
	OMEGAASSERT((row > 1 && col > 1), "To create plane, width and height should be more than 1.");
	MeshPX mesh;
	const float du = 1.0f / (row - 1.0f);
	const float dv = 1.0f / (col - 1.0f);

	for (float y = 0.0f; y < col; ++y)
	{
		for (float x = 0.0f; x < row; ++x)
		{
			mesh.vertices.emplace_back(VertexPX{ Vector3{ x, y, 0.0f} ,
										1.0f - x * du , 1.0f - y * dv });
		}
	}

	for (unsigned int y = 0; y < col - 1; ++y)
	{
		for (unsigned int x = 0; x < row - 1; ++x)
		{
			/*

			Indices read to anti-clockwise ->
			2|-------------|3
			 |			   |
			 |			   |
			0|-------------|1

			*/

			// get the corrnes
			mesh.indices.push_back(y * col + x);
			mesh.indices.push_back((y + 1) * col + x);
			mesh.indices.push_back(y * col + (x + 1));

			mesh.indices.push_back((y + 1) * col + x);
			mesh.indices.push_back((y + 1) * col + (x + 1));
			mesh.indices.push_back(y * col + (x + 1));
		}
	}


	return mesh;
}

MeshPX MeshBuilder::CreateCylinderPX(uint32_t row, uint32_t col, float radius)
{
	const float TwoPIRow = (Constants::TwoPi / row);

	MeshPX mesh;
	for (float y = 0.0f; y < col; ++y)
	{
		for (float x = 0.0f; x <= Constants::TwoPi; x += Constants::TwoPi / row)
		{
			float u = x / Constants::TwoPi;
			float v = 1.0f - (y / col);
			float theta = x * TwoPIRow;

			mesh.vertices.emplace_back(
				VertexPX{ Vector3{ -sinf(theta) * radius , y , cosf(theta) * radius}, u,v }
			);
		}
	}

	const int ringVertexCount = col + 1;
	for (unsigned int y = 0; y + 1 < col; ++y)
	{
		for (unsigned int x = 0; x < row; ++x)
		{
			/*

			Indices read to anti-clockwise ->
			2|-------------|3
			 |			   |
			 |			   |
			0|-------------|1

			*/
			// get the corrnes
			mesh.indices.push_back((y + 1) * ringVertexCount + x);
			mesh.indices.push_back((y + 1) * ringVertexCount + x + 1);
			mesh.indices.push_back(y * ringVertexCount + x);

			mesh.indices.push_back((y + 1) * ringVertexCount + x + 1);
			mesh.indices.push_back(y * ringVertexCount + x + 1);
			mesh.indices.push_back(y * ringVertexCount + x);
		}
	}

	// TopCap
	//TODO: Need to be fixed
	int baseIndex = static_cast<int>(mesh.vertices.size());

	float y = 0.5f * row;

	for (unsigned int i = 0; i <= row; ++i) {
		float x = radius * cosf(i * TwoPIRow);
		float z = radius * sinf(i * TwoPIRow);

		float u = x / col + 0.5f;
		float v = z / col + 0.5f;
		mesh.vertices.emplace_back(VertexPX{ Vector3{x,y,z}, u,v });
	}
	mesh.vertices.emplace_back(VertexPX{ Vector3{0,y,0}, 0.5f,0.5f });
	int centerIndex = baseIndex - 1;

	for (unsigned int i = 0; i < row - 1; i++) {
		mesh.indices.push_back(centerIndex);
		mesh.indices.push_back(baseIndex + i + 1);
		mesh.indices.push_back(baseIndex + i);
	}

	return mesh;
}

MeshPX MeshBuilder::CreateSpherePX(float radius, int rings, int slices)
{
	MeshPX mesh;

	mesh.vertices.emplace_back(VertexPX{ Vector3{0.0f, radius, 0.0f},0.0f,0.0f });

	float phiStep = Constants::Pi / slices;
	float thetaStep = Constants::TwoPi / slices;

	for (int x = 1; x <= rings - 1; ++x)
	{
		float phi = x * phiStep;
		for (int y = 0; y <= slices; ++y)
		{
			float u = x * 1.0f / slices;
			float v = 1.0f - (y / (rings - 1.0f));

			float theta = y * thetaStep;

			mesh.vertices.emplace_back(VertexPX{
				Vector3{
					sinf(phi) * cosf(theta) * radius,
					cosf(phi) * radius,
					sinf(phi) * sinf(theta) * radius
				},
				u, v });
		}
	}
	mesh.vertices.emplace_back(VertexPX{ Vector3{0.0f, -radius,0.0f},0.0f,0.0f });

	for (int i = 1; i <= slices; ++i)
	{
		mesh.indices.push_back(0);
		mesh.indices.push_back(i + 1);
		mesh.indices.push_back(i);
	}
	int baseIndex = 1;
	int ringVertexCount = slices + 1;
	for (int i = 0; i < rings - 2; ++i)
	{
		for (int j = 0; j < slices; ++j)
		{
			mesh.indices.push_back(baseIndex + i * ringVertexCount + j);
			mesh.indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			mesh.indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

			mesh.indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			mesh.indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			mesh.indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
		}
	}
	int southPoleIndex = static_cast<int>(mesh.vertices.size()) - 1;
	baseIndex = southPoleIndex - ringVertexCount;
	for (int i = 0; i < slices; ++i)
	{
		mesh.indices.push_back(southPoleIndex);
		mesh.indices.push_back(baseIndex + i);
		mesh.indices.push_back(baseIndex + i + 1);
	}

	return mesh;
}
