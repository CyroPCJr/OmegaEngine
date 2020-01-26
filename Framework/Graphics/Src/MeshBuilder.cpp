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
	const float thetaSteps = (Constants::TwoPi / row);

	MeshPX mesh;
	for (float y = 0.0f; y < col; ++y)
	{
		for (float theta = 0.0f; theta <= Constants::TwoPi; theta += thetaSteps)
		{
			auto vec = Vector3
			{
			-sinf(theta) * radius,
			static_cast<float>(y),
			cosf(theta) * radius
			};

			mesh.vertices.emplace_back(
				VertexPX{ vec, theta / Constants::TwoPi,y / col }
			);
		}
	}

	for (uint32_t y = 0; y <= col; ++y)
	{
		for (uint32_t x = 0; x <= row; ++x)
		{
			if ((y == 0) && (x != 0) && (x != row - 1))
			{
				mesh.indices.push_back(0);
				mesh.indices.push_back(0 + x + 1);
				mesh.indices.push_back(0 + x);
			}
			if ((y == col - 1) && (x != 0) && (x != row - 1))
			{
				mesh.indices.push_back(y*row);
				mesh.indices.push_back(y*row + x);
				mesh.indices.push_back(y*row + x + 1);
			}

			mesh.indices.push_back(y*row + x);
			mesh.indices.push_back((y + 1)*row + x + 1);
			mesh.indices.push_back((y + 1)*row + x);

			mesh.indices.push_back(y*row + x);
			mesh.indices.push_back(y*row + x + 1);
			mesh.indices.push_back((y + 1)*row + x + 1);
		}
	}

	return mesh;
}

MeshPX MeshBuilder::CreateSpherePX(float radius, int rings, int slices, bool isSpace)
{
	MeshPX mesh;
	const float phiSteps = (Constants::Pi / rings);
	const float thetaSteps = (Constants::TwoPi / slices);
	for (float phi = 0; phi < Constants::Pi; phi += phiSteps)
	{
		for (float theta = 0; theta < Constants::TwoPi; theta += thetaSteps)
		{
			auto vec = Vector3
			{
				sinf(phi) * cosf(theta) * radius,
				cosf(phi) * radius,
				sinf(phi) * sinf(theta) * radius
			};

			mesh.vertices.emplace_back(VertexPX{ vec, theta / Constants::TwoPi, phi / Constants::Pi });
		}
	}

	int a, b, c, d;
	for (int y = 0; y < rings; ++y)
	{
		for (int x = 0; x <= slices; ++x)
		{
			a = (x % (slices + 1));
			b = ((x + 1) % (slices + 1));
			c = (y * (slices + 1));
			d = ((y + 1) * (slices + 1));

			if (!isSpace)
			{
				mesh.indices.push_back(a + c);
				mesh.indices.push_back(b + c);
				mesh.indices.push_back(a + d);

				mesh.indices.push_back(b + c);
				mesh.indices.push_back(b + d);
				mesh.indices.push_back(a + d);
			}
			else
			{
				mesh.indices.push_back(a + d);
				mesh.indices.push_back(b + c);
				mesh.indices.push_back(a + c);

				mesh.indices.push_back(a + d);
				mesh.indices.push_back(b + d);
				mesh.indices.push_back(b + c);
			}
		}
	}

	return mesh;
}

MeshPN MeshBuilder::CreateSpherePN(float radius, int rings, int slices, bool isSpace)
{
	MeshPN mesh;
	const float phiSteps = (Constants::Pi / rings);
	const float thetaSteps = (Constants::TwoPi / slices);
	for (float phi = 0; phi < Constants::Pi; phi += phiSteps)
	{
		for (float theta = 0; theta < Constants::TwoPi; theta += thetaSteps)
		{
			auto vec = Vector3
			{
				sinf(phi) * cosf(theta) * radius,
				cosf(phi) * radius,
				sinf(phi) * sinf(theta) * radius
			};
			mesh.vertices.emplace_back(VertexPN{ vec, Normalize(vec) });
		}
	}

	int a, b, c, d;
	for (int y = 0; y < rings; ++y)
	{
		for (int x = 0; x <= slices; ++x)
		{
			a = (x % (slices + 1));
			b = ((x + 1) % (slices + 1));
			c = (y * (slices + 1));
			d = ((y + 1) * (slices + 1));

			if (!isSpace)
			{
				mesh.indices.push_back(a + c);
				mesh.indices.push_back(b + c);
				mesh.indices.push_back(a + d);

				mesh.indices.push_back(b + c);
				mesh.indices.push_back(b + d);
				mesh.indices.push_back(a + d);
			}
			else
			{
				mesh.indices.push_back(a + d);
				mesh.indices.push_back(b + c);
				mesh.indices.push_back(a + c);

				mesh.indices.push_back(a + d);
				mesh.indices.push_back(b + d);
				mesh.indices.push_back(b + c);
			}
		}
	}

	return mesh;
}

Mesh MeshBuilder::CreateSphere(float radius, int rings, int slices, bool isSpace)
{
	Mesh mesh;

	const float phiSteps = (Constants::Pi / rings);
	const float thetaSteps = (Constants::TwoPi / slices);
	for (float phi = 0; phi < Constants::Pi; phi += phiSteps)
	{
		for (float theta = 0; theta < Constants::TwoPi; theta += thetaSteps)
		{
			auto vec = Vector3
			{
				sinf(phi) * cosf(theta) * radius,
				cosf(phi) * radius,
				sinf(phi) * sinf(theta) * radius
			};
			mesh.vertices.emplace_back(
				Vertex
				{ vec,
				  Normalize(vec),
				  0 ,
				{theta / Constants::TwoPi, phi / Constants::Pi}
				}
			);
		}
	}

	int a, b, c, d;
	for (int y = 0; y < rings; ++y)
	{
		for (int x = 0; x <= slices; ++x)
		{
			a = (x % (slices + 1));
			b = ((x + 1) % (slices + 1));
			c = (y * (slices + 1));
			d = ((y + 1) * (slices + 1));

			if (!isSpace)
			{
				mesh.indices.push_back(a + c);
				mesh.indices.push_back(b + c);
				mesh.indices.push_back(a + d);

				mesh.indices.push_back(b + c);
				mesh.indices.push_back(b + d);
				mesh.indices.push_back(a + d);
			}
			else
			{
				mesh.indices.push_back(a + d);
				mesh.indices.push_back(b + c);
				mesh.indices.push_back(a + c);

				mesh.indices.push_back(a + d);
				mesh.indices.push_back(b + d);
				mesh.indices.push_back(b + c);
			}
		}
	}

	return mesh;
}
