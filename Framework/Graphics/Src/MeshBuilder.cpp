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
	const float du = 1.0f / static_cast<float>(row - 1.0f);
	const float dv = 1.0f / static_cast<float>(col - 1.0f);

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

Mesh MeshBuilder::CreatePlane(float size, int row, int column)
{
	Mesh mesh;
	const float xStep = size / (row - 1);
	const float zStep = size / (column - 1);
	const float uStep = row / static_cast<float>(row - 1);
	const float vStep = column / static_cast<float>(column - 1);

	Math::Vector3 offset = { size * -0.5f, 0.0f, size * -0.5f };

	for (int z = 0; z < row; ++z)
	{
		for (int x = 0; x < column; ++x)
		{
			float xx = xStep * x;
			float zz = zStep * z;
			float y = 0.0f;
			Math::Vector3 position = { xx, 0.0f, zz };
			Math::Vector3 normal = Math::Vector3::YAxis;
			Math::Vector3 tangent = Math::Vector3::XAxis;
			Math::Vector2 uv = { x * uStep, 1.0f - z * vStep };
			mesh.vertices.emplace_back(Vertex{ position + offset, normal, tangent, uv });
		}
	}

	for (int z = 0; z < row; ++z)
	{
		for (int x = 0; x < column; ++x)
		{
			mesh.indices.push_back((x + 0) + ((z + 0) * column));
			mesh.indices.push_back((x + 0) + ((z + 1) * column));
			mesh.indices.push_back((x + 1) + ((z + 1) * column));

			mesh.indices.push_back((x + 0) + ((z + 0) * column));
			mesh.indices.push_back((x + 1) + ((z + 1) * column));
			mesh.indices.push_back((x + 1) + ((z + 0) * column));
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
			cosf(theta)* radius
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
				mesh.indices.push_back(y * row);
				mesh.indices.push_back(y * row + x);
				mesh.indices.push_back(y * row + x + 1);
			}

			mesh.indices.push_back(y * row + x);
			mesh.indices.push_back((y + 1) * row + x + 1);
			mesh.indices.push_back((y + 1) * row + x);

			mesh.indices.push_back(y * row + x);
			mesh.indices.push_back(y * row + x + 1);
			mesh.indices.push_back((y + 1) * row + x + 1);
		}
	}

	/*
	// x
		float initY = height * 0.5f;

	for (uint32_t i = 0, n = sides - 1; i < sides; i++)
	{
		// Set vertices
		float ratio = (float)i / n;
		float r = ratio * (Math::Pi * 2.0f);
		float x = cosf(r) * radius;
		float z = sinf(r) * radius;
		vertices.push_back({ {0.0f, initY, 0.0f }, {ratio, 1.0f} });	// center of top
		vertices.push_back({ {x, initY, z},{ratio, 0.0f} });			// side of top
		vertices.push_back({ {0.0f, -initY, 0.0f }, {ratio, 0.0f} });	// center of base
		vertices.push_back({ {x, -initY, z}, {ratio, 1.0f} });			// side of base
		// Set indices
		uint32_t offset = i * 4;
		indices.push_back(offset);		//
		indices.push_back(offset + 5);	//
		indices.push_back(offset + 1);	// top
		indices.push_back(offset + 5);	//
		indices.push_back(offset + 7);	//
		indices.push_back(offset + 1);	// right side triangle
		indices.push_back(offset + 1);	//
		indices.push_back(offset + 7);	//
		indices.push_back(offset + 3);	// left side triangle
		indices.push_back(offset + 7);	//
		indices.push_back(offset + 2);	//
		indices.push_back(offset + 3);	// base
	}

	*/

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
		for (float theta = 0.0f; theta < Constants::TwoPi; theta += thetaSteps)
		{
			auto vec = Vector3
			{
				sinf(phi) * cosf(theta) * radius,
				cosf(phi) * radius,
				sinf(phi) * sinf(theta) * radius
			};
			Vector3 normal = Normalize(vec);
			Vector3 normalTangent = { -normal.z ,0.0f, normal.x };
			mesh.vertices.emplace_back(
				Vertex
				{ vec,
				  normal, // vector normalized
				 normalTangent , // tangent
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



MeshPX Omega::Graphics::MeshBuilder::CreateNDCQuad()
{
	MeshPX mesh;
	mesh.vertices.emplace_back(VertexPX{ {-1.0f, -1.0f, 0.0f },  0.0f, 1.0f });
	mesh.vertices.emplace_back(VertexPX{ {-1.0f, +1.0f, 0.0f },  0.0f, 0.0f });
	mesh.vertices.emplace_back(VertexPX{ {+1.0f, +1.0f, 0.0f },  1.0f, 0.0f });
	mesh.vertices.emplace_back(VertexPX{ {+1.0f, -1.0f, 0.0f },  1.0f, 1.0f });

	mesh.indices.emplace_back(0);
	mesh.indices.emplace_back(1);
	mesh.indices.emplace_back(2);

	mesh.indices.emplace_back(0);
	mesh.indices.emplace_back(2);
	mesh.indices.emplace_back(3);

	return mesh;
}
