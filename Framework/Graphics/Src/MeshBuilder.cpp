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

MeshPX MeshBuilder::CreatePlanePX(int row, int col)
{
	OMEGAASSERT((row > 1 && col > 1), "[PlanePX] To create plane, width and height should be more than 1.");
	MeshPX mesh;
	Math::Vector3 offset = { static_cast<float>(row) * -0.5f, static_cast<float>(col) * -0.5f ,0.0f };
	for (int y = 0; y < col; ++y)
	{
		for (int x = 0; x < row; ++x)
		{
			float du = static_cast<float>(x) / static_cast<float>(row - 1);
			float dv = static_cast<float>(y) / static_cast<float>(col - 1);
			VertexPX vertex;
			vertex.position = { offset.x + static_cast<float>(x), offset.y - static_cast<float>(y), offset.z };
			vertex.u = du;
			vertex.v = dv;

			mesh.vertices.push_back(vertex);

			if ((y != col - 1) && (x != row - 1))
			{
				//		Indices read to anti-clockwise ->
				//		2|-------------|3
				//		 |			   |
				//		 |			   |
				//		0|-------------|1

				mesh.indices.push_back(static_cast<size_t>(y * row + x));
				mesh.indices.push_back(static_cast<size_t>((y + 1) * row + x + 1));
				mesh.indices.push_back(static_cast<size_t>((y + 1) * row + x));

				mesh.indices.push_back(static_cast<size_t>(y * row + x));
				mesh.indices.push_back(static_cast<size_t>(y * row + x + 1));
				mesh.indices.push_back(static_cast<size_t>((y + 1) * row + x + 1));
			}

		}
	}

	return mesh;
}

MeshPX MeshBuilder::CreateCylinderPX(float radius, int rings, int slices)
{


	MeshPX mesh;
	const float height = 3.0f;
	const float heightStep = height / static_cast<float>(rings - 1);
	const float angleStep = Math::Constants::TwoPi / static_cast<float>(slices);
	const float uStep = 1.0f / static_cast<float>(slices);
	const float vStep = 1.0f / static_cast<float>((rings - 1));

	for (int j = 0; j <= slices; ++j)
	{
		mesh.vertices.emplace_back(VertexPX{ { 0.0f, (height * -0.5f), 0.0f }, j * uStep, 0.0f });
	}

	for (int i = 0; i < rings; ++i)
	{
		for (int j = 0; j <= slices; ++j)
		{
			float angle = angleStep * j;
			float x = cosf(angle) * radius;
			float z = sinf(angle) * radius;
			float y = (height * -0.5f) + (heightStep * i);
			mesh.vertices.emplace_back(VertexPX{ { x, y, z }, j * uStep, 1.0f - i * vStep });
		}
	}

	for (int j = 0; j <= slices; ++j)
	{
		mesh.vertices.emplace_back(VertexPX{ { 0.0f, (height * 0.5f), 0.0f }, j * uStep, 1.0f });
	}

	for (int i = 0; i + 1 < rings + 2; ++i)
	{
		for (unsigned int j = 0; j < slices; ++j)
		{
			mesh.indices.push_back((j + 0) + ((i + 0) * (slices + 1)));
			mesh.indices.push_back((j + 0) + ((i + 1) * (slices + 1)));
			mesh.indices.push_back((j + 1) + ((i + 1) * (slices + 1)));

			mesh.indices.push_back((j + 0) + ((i + 0) * (slices + 1)));
			mesh.indices.push_back((j + 1) + ((i + 1) * (slices + 1)));
			mesh.indices.push_back((j + 1) + ((i + 0) * (slices + 1)));
		}
	}
	return mesh;
}

MeshPX MeshBuilder::CreateSpherePX(float radius, int rings, int slices, bool isSpace)
{
	MeshPX mesh;
	const float thetaStep = Math::Constants::Pi / (rings - 1);
	const float phiStep = Math::Constants::TwoPi / slices;
	const float uStep = 1.0f / slices;
	const float vStep = 1.0f / (rings - 1);

	for (int i = 0; i < rings; ++i)
	{
		for (int j = 0; j <= slices; ++j)
		{
			float theta = thetaStep * i;
			float phi = phiStep * j;
			float r = sinf(theta);
			float x = cosf(phi) * r * radius;
			float z = sinf(phi) * r * radius;
			float y = -cosf(theta) * radius;

			Math::Vector3 position = { x, y, z };
			float u = j * uStep;
			float v = 1.0f - i * vStep;

			mesh.vertices.emplace_back(VertexPX{ position, u,v });
		}
	}

	uint32_t a, b, c, d;

	for (int x = 0; x < rings; ++x)
	{
		for (int y = 0; y <= slices; ++y)
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

MeshPX MeshBuilder::CreateNDCQuad()
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
	const float phiSteps = (Constants::Pi / static_cast<float>(rings));
	const float thetaSteps = (Constants::TwoPi / static_cast<float>(slices));
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

Mesh MeshBuilder::CreatePlane(float size, uint32_t row, uint32_t column)
{
	Mesh mesh;
	const float xStep = size / (row - 1);
	const float zStep = size / (column - 1);
	const float uStep = row / static_cast<float>(row - 1);
	const float vStep = column / static_cast<float>(column - 1);

	Math::Vector3 offset = { size * -0.5f, 0.0f, size * -0.5f };

	for (uint32_t z = 0; z < row; ++z)
	{
		for (uint32_t x = 0; x < column; ++x)
		{
			float xx = xStep * x;
			float zz = zStep * z;
			Math::Vector3 position = { xx, 0.0f, zz };
			Math::Vector3 normal = Math::Vector3::YAxis;
			Math::Vector3 tangent = Math::Vector3::XAxis;
			Math::Vector2 uv = { x * uStep, 1.0f - z * vStep };
			mesh.vertices.emplace_back(Vertex{ position + offset, normal, tangent, uv });

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

void MeshBuilder::ComputeNormals(Mesh& mesh)
{
	std::vector<Math::Vector3> vecNormals{};
	const size_t indiceSize = mesh.indices.size();
	const size_t vertexSize = mesh.vertices.size();
	vecNormals.resize(vertexSize);
	for (size_t i = 0; i < indiceSize; i += 3)
	{
		uint32_t idx_0 = mesh.GetIndices(i + 0);
		uint32_t idx_1 = mesh.GetIndices(i + 1);
		uint32_t idx_2 = mesh.GetIndices(i + 2);

		const auto& v_0 = static_cast<Vertex>(mesh.GetVertex(idx_0));
		const auto& v_1 = static_cast<Vertex>(mesh.GetVertex(idx_1));
		const auto& v_2 = static_cast<Vertex>(mesh.GetVertex(idx_2));

		Math::Vector3 crossNormalized = Math::Normalize(Cross(v_1.position - v_0.position, v_2.position - v_0.position));

		vecNormals[idx_0] += crossNormalized;
		vecNormals[idx_1] += crossNormalized;
		vecNormals[idx_2] += crossNormalized;
	}

	for (size_t i = 0; i < vertexSize; ++i)
	{
		mesh.vertices[i].normal = vecNormals[i];
	}
}