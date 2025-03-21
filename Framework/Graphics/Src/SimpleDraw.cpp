#include"Precompiled.h"
#include"SimpleDraw.h"

#include "Camera.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "MeshBuffer.h"
#include "VertexTypes.h"
#include "GraphicsSystem.h"

using namespace Omega;
using namespace Omega::Math;
using namespace Omega::Graphics;
using namespace std;

namespace Omega::Graphics
{
	class SimpleDrawImpl
	{
	public:

		void Initialize(unsigned int maxVertexCount)
		{
			mVertexShader.Initialize("../../Assets/Shaders/SimpleDraw.fx", VertexPC::Format);
			mPixelShader.Initialize("../../Assets/Shaders/SimpleDraw.fx");
			mConstantBuffer.Initialize(sizeof(Matrix4));
			mMeshBuffer.Initialize<VertexPC>(nullptr, maxVertexCount, true);
			mLineVertices = make_unique<VertexPC[]>(maxVertexCount);
			m2DLineVertices = make_unique<VertexPC[]>(maxVertexCount);
			mFillVertices = make_unique<VertexPC[]>(static_cast<size_t>(maxVertexCount * 3));
			mVertexCount = 0u;
			m2DVertexCount = 0u;
			mFillVertexCount = 0u;
			mMaxVertexCount = maxVertexCount;
		}

		void Terminate()
		{
			mVertexShader.Terminate();
			mPixelShader.Terminate();
			mConstantBuffer.Terminate();
			mMeshBuffer.Terminate();
		}

		void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color)
		{
			if (mVertexCount + 2u < mMaxVertexCount)
			{
				mLineVertices[mVertexCount++] = VertexPC{ v0,color };
				mLineVertices[mVertexCount++] = VertexPC{ v1,color };
			}
		}

		void AddFace(const Math::Vector3& v0, const  Math::Vector3& v1, const  Math::Vector3& v2, const Color& color)
		{
			if (mFillVertexCount + 3u < mFillVertexCount)
			{
				mFillVertices[mFillVertexCount++] = VertexPC{ v0, color };
				mFillVertices[mFillVertexCount++] = VertexPC{ v1, color };
				mFillVertices[mFillVertexCount++] = VertexPC{ v2, color };
			}
		}

		void AddDisplacement(float length)
		{
			AddLine(Math::Vector3::Zero, Math::Vector3::XAxis * length, Colors::Red);
			AddLine(Math::Vector3::Zero, Math::Vector3::YAxis * length, Colors::Blue);
			AddLine(Math::Vector3::Zero, Math::Vector3::ZAxis * length, Colors::Green);
		}

		void AddBox(float length, const Color& color)
		{
			AddLine(Math::Vector3{ -length, -length, -length }, Math::Vector3{ length, -length, -length }, color);
			AddLine(Math::Vector3{ -length, -length, -length }, Math::Vector3{ -length, length, -length }, color);
			AddLine(Math::Vector3{ -length, -length, -length }, Math::Vector3{ -length, -length, length }, color);
			AddLine(Math::Vector3{ -length, length, -length }, Math::Vector3{ length, length, -length }, color);
			AddLine(Math::Vector3{ -length, length, -length }, Math::Vector3{ -length, length, length }, color);
			AddLine(Math::Vector3{ length, length, -length }, Math::Vector3{ length, length, length }, color);
			AddLine(Math::Vector3{ length, length, length }, Math::Vector3{ -length, length, length }, color);
			AddLine(Math::Vector3{ length, length, -length }, Math::Vector3{ length, -length, -length }, color);
			AddLine(Math::Vector3{ length, -length, -length }, Math::Vector3{ length, -length, length }, color);
			AddLine(Math::Vector3{ length, length, length }, Math::Vector3{ -length, length, length }, color);
			AddLine(Math::Vector3{ length, length, length }, Math::Vector3{ length, -length, length }, color);
			AddLine(Math::Vector3{ length, -length, length }, Math::Vector3{ -length, -length, length }, color);
			AddLine(Math::Vector3{ -length, -length, length }, Math::Vector3{ -length, length, length }, color);
		}

		void AddSphere(const Math::Vector3& position, float radius, unsigned int rings, unsigned int slices, const Color& color)
		{
			const float x = position.x;
			const float y = position.y;
			const float z = position.z;

			const unsigned int kSlices = Max(3u, slices);
			const unsigned int kRings = Max(2u, rings);
			const unsigned int kLines = (4u * kSlices * kRings) - (2u * kSlices);

			// Check if we have enough space
			if (mVertexCount + kLines <= mMaxVertexCount)
			{
				// Add lines
				const float kTheta = Math::Constants::Pi / static_cast<float>(kRings);
				const float kPhi = Math::Constants::TwoPi / static_cast<float>(kSlices);
				for (unsigned int j = 0; j < kSlices; ++j)
				{
					for (unsigned int i = 0; i < kRings; ++i)
					{
						const float a = static_cast<float>(i) * kTheta;
						const float b = a + kTheta;
						const float ay = radius * cosf(a);
						const float by = radius * cosf(b);

						const float theta = static_cast<float>(j) * kPhi;
						const float phi = theta + kPhi;

						const float ar = sqrt(radius * radius - ay * ay);
						const float br = sqrt(radius * radius - by * by);

						const float x0 = x + (ar * sinf(theta));
						const float y0 = y + (ay);
						const float z0 = z + (ar * cosf(theta));

						const float x1 = x + (br * sinf(theta));
						const float y1 = y + (by);
						const float z1 = z + (br * cosf(theta));

						const float x2 = x + (br * sinf(phi));
						const float y2 = y + (by);
						const float z2 = z + (br * cosf(phi));

						mLineVertices[mVertexCount++] = { Math::Vector3(x0, y0, z0), color };
						mLineVertices[mVertexCount++] = { Math::Vector3(x1, y1, z1), color };

						if (i < kRings - 1)
						{
							mLineVertices[mVertexCount++] = { Math::Vector3(x1, y1, z1), color };
							mLineVertices[mVertexCount++] = { Math::Vector3(x2, y2, z2), color };
						}
					}
				}
			}
		}

		void AddGroundPlane(float size, float sizeCell, const Color& color)
		{
			const float halfSize = size * 0.5f;
			for (float i = -halfSize; i <= halfSize; i += sizeCell)
			{
				AddLine({ i, 0.0f, -halfSize }, { i, 0.0f, halfSize }, color);
				AddLine({ halfSize, 0.0f,  -i }, { -halfSize, 0.0f, -i }, color);
			}
		}

		void AddBone(const Math::Matrix4& transform, const Color& color)
		{
			Math::Vector3 right = Math::GetRight(transform);
			Math::Vector3 up = Math::GetUp(transform);
			Math::Vector3 left = Math::GetLook(transform);
			Math::Vector3 position = Math::GetTranslation(transform);

			auto base = position;
			auto direction = right - position;
			constexpr int sectors = 4;
			auto side = Math::Normalize(Math::Cross(position, direction)) * 1.0f;
			float angle = 0.0f;
			constexpr float angleStep = Math::Constants::TwoPi / sectors;

			for (int i = 0; i < sectors; ++i)
			{
				auto matRot0 = Math::Matrix4::RotationAxis(direction, angle);
				auto matRot1 = Math::Matrix4::RotationAxis(direction, angle + angleStep);
				auto v0 = Math::TransformNormal(side, matRot0);
				auto v1 = Math::TransformNormal(side, matRot1);
				AddLine(position + v0, position + direction, color);
				AddLine(position + v0, position + v1, color);
				angle += angleStep;
			}
		}

		void AddBone(const Math::Vector3& base, const Math::Vector3& direction, float radius, const Color& color, bool fill)
		{
			constexpr int sectors = 4;
			auto side = Math::Normalize(Math::Cross(base, direction)) * radius;
			float angle = 0.0f;
			constexpr float angleStep = Math::Constants::TwoPi / sectors;

			const auto oppDirection = -Normalize(direction) * radius;

			for (int i = 0; i < sectors; ++i)
			{
				const auto matRot0 = Math::Matrix4::RotationAxis(direction, angle);
				const auto matRot1 = Math::Matrix4::RotationAxis(direction, angle + angleStep);
				const auto v0 = Math::TransformNormal(side, matRot0);
				const auto v1 = Math::TransformNormal(side, matRot1);
				const auto tempBase = base + v0;
				if (!fill)
				{
					AddLine(tempBase, base + direction, color);
					AddLine(tempBase, base + oppDirection, color);
					AddLine(tempBase, base + v1, color);
				}
				else
				{
					AddFace(tempBase, base + v1, base + direction, color);
					AddFace(tempBase, base + oppDirection, base + v1, color);
				}
				angle += angleStep;
			}
		}

		void AddTransform(const Math::Matrix4& transform)
		{
			Math::Vector3 right = Math::GetRight(transform);
			Math::Vector3 up = Math::GetUp(transform);
			Math::Vector3 forward = Math::GetForward(transform);
			Math::Vector3 position = Math::GetTranslation(transform);
			AddLine(position, position + right, Colors::Red);
			AddLine(position, position + up, Colors::Green);
			AddLine(position, position + forward, Colors::Blue);
		}

		void AddOBB(const Math::OBB& obb, const Color& color)
		{
			Math::Matrix4 matTrans = Math::Matrix4::Translation(obb.center);
			Math::Matrix4 matRot = Math::Matrix4::RotationQuaternion(obb.rot);
			Math::Matrix4 matScale = Math::Matrix4::Scaling(obb.extend);
			Math::Matrix4 toWorld = matScale * matRot * matTrans;

			Math::Vector3 points[] =
			{
				// Front quad
				Math::Vector3(-1.0f, -1.0f, -1.0f),
				Math::Vector3(-1.0f, +1.0f, -1.0f),
				Math::Vector3(+1.0f, +1.0f, -1.0f),
				Math::Vector3(+1.0f, -1.0f, -1.0f),
				//Back quad
				Math::Vector3(-1.0f, -1.0f, +1.0f),
				Math::Vector3(-1.0f, +1.0f, +1.0f),
				Math::Vector3(+1.0f, +1.0f, +1.0f),
				Math::Vector3(+1.0f, -1.0f, +1.0f),
			};

			for (auto& p : points)
			{
				p = Math::TransformCoord(p, toWorld);
			}

			AddLine(points[0], points[1], color);
			AddLine(points[1], points[2], color);
			AddLine(points[2], points[3], color);
			AddLine(points[3], points[0], color);

			AddLine(points[0], points[4], color);
			AddLine(points[1], points[5], color);
			AddLine(points[2], points[6], color);
			AddLine(points[3], points[7], color);

			AddLine(points[4], points[5], color);
			AddLine(points[5], points[6], color);
			AddLine(points[6], points[7], color);
			AddLine(points[7], points[4], color);
		}

		void AddAABB(const Math::AABB& aabb, const Color& color)
		{
			// Check if we have enough space

			if (mVertexCount + 24u <= mMaxVertexCount)
			{
				float minX = aabb.center.x - aabb.extend.x;
				float minY = aabb.center.y - aabb.extend.y;
				float minZ = aabb.center.z - aabb.extend.z;
				float maxX = aabb.center.x + aabb.extend.x;
				float maxY = aabb.center.y + aabb.extend.y;
				float maxZ = aabb.center.z + aabb.extend.z;


				AddLine(Math::Vector3(minX, minY, minZ), Math::Vector3(minX, minY, maxZ), color);
				AddLine(Math::Vector3(minX, minY, maxZ), Math::Vector3(maxX, minY, maxZ), color);
				AddLine(Math::Vector3(maxX, minY, maxZ), Math::Vector3(maxX, minY, minZ), color);
				AddLine(Math::Vector3(maxX, minY, minZ), Math::Vector3(minX, minY, minZ), color);
				AddLine(Math::Vector3(minX, minY, minZ), Math::Vector3(minX, maxY, minZ), color);
				AddLine(Math::Vector3(minX, minY, maxZ), Math::Vector3(minX, maxY, maxZ), color);
				AddLine(Math::Vector3(maxX, minY, maxZ), Math::Vector3(maxX, maxY, maxZ), color);
				AddLine(Math::Vector3(maxX, minY, minZ), Math::Vector3(maxX, maxY, minZ), color);
				AddLine(Math::Vector3(minX, maxY, minZ), Math::Vector3(minX, maxY, maxZ), color);
				AddLine(Math::Vector3(minX, maxY, maxZ), Math::Vector3(maxX, maxY, maxZ), color);
				AddLine(Math::Vector3(maxX, maxY, maxZ), Math::Vector3(maxX, maxY, minZ), color);
				AddLine(Math::Vector3(maxX, maxY, minZ), Math::Vector3(minX, maxY, minZ), color);
			}

			OMEGAASSERT(mVertexCount < mMaxVertexCount, "[SimpleDraw] Too many vertices!");
		}

		void AddCylinder(const Math::Vector3& base, const Math::Vector3& direction, float height, float radius, const Color& color, bool fill = false)
		{
			const int slices = 16;
			const int rings = 16;
			const float increment = Math::Constants::TwoPi / static_cast<float>(slices);
			const float ringRatio = 1.0f / static_cast<float>(rings);
			std::vector<Math::Vector3> list;

			const Math::Vector3& d = Math::Normalize(direction);
			float angle = acosf(Math::Dot(d, Math::Vector3::YAxis));
			Math::Vector3 rotationAxis = Math::Cross(Math::Vector3::YAxis, d);
			Math::Matrix4 rotationMatrix = Math::Matrix4::RotationAxis(rotationAxis, angle);

			for (int y = 0; y <= rings; ++y)
			{
				for (float theta = 0; theta <= Math::Constants::TwoPi; theta += increment)
				{
					Math::Vector3 vec = Math::TransformNormal(
						Math::Vector3{ sinf(theta) * radius, height * static_cast<float>(y) * ringRatio, cosf(theta) * radius }, rotationMatrix) + base;
					list.push_back(vec);
				}
			}

			int sectorCount = rings + 1;
			for (int y = 0; y <= rings; ++y)
			{
				for (int x = 0; x < slices; ++x)
				{
					if (!fill)
					{
						AddLine(list[y * sectorCount + x], list[y * sectorCount + x + 1], color);
						if (y + 1 <= rings)
							AddLine(list[y * sectorCount + x], list[(y + 1) * sectorCount + x], color);
						if (y == 0 || y == rings)
						{
							Math::Vector3 centerVec =
								Math::TransformNormal(Math::Vector3{ 0.f, height * y * ringRatio, 0.0f }, rotationMatrix) + base;
							AddLine(list[y * sectorCount + x], centerVec, color);
						}
					}
					else
					{
						AddFace(list[(y + 1) * rings + x + 1], list[(y + 1) * rings + x], list[y * rings + x], color);
						AddFace(list[y * rings + x], list[y * rings + x + 1], list[(y + 1) * rings + x + 1], color);
						if (y == 0)
						{
							Math::Vector3 centerVec =
								Math::TransformNormal(Math::Vector3{ 0.0f, height * y * ringRatio, 0.0f }, rotationMatrix) + base;
							AddFace(list[y * sectorCount + x], centerVec, list[y * sectorCount + x + 1], color);
						}
						else if (y == rings)
						{
							Math::Vector3 centerVec =
								Math::TransformNormal(Math::Vector3{ 0.0f, height * y * ringRatio, 0.0f }, rotationMatrix) + base;
							AddFace(list[y * sectorCount + x], list[y * sectorCount + x + 1], centerVec, color);
						}
					}
				}
			}
		}

		void AddCone(float height, float radius, const Color& color, bool fill = false)
		{
			int slices = 16;
			float thetaIncrement = Math::Constants::TwoPi / slices;
			std::vector<Math::Vector3> list;
			for (float theta = 0; theta <= Math::Constants::TwoPi; theta += thetaIncrement)
			{
				list.push_back({ radius * cosf(theta), 0.0f , radius * sinf(theta) });
			}

			if (mVertexCount + list.size() - 1 > mMaxVertexCount)
			{
				return;
			}

			for (size_t i = 0; i < list.size() - 1; ++i)
			{
				if (!fill)
				{
					AddLine(list[i], list[i + 1], color);
					AddLine(list[i], { 0.0f , height , 0.0f }, color);
				}
				else
				{
					AddFace(list[i], { 0.0f , height , 0.0f }, list[i + 1], color);
					AddFace(list[i], list[i + 1], Math::Vector3::Zero, color);
				}
			}
		}

		void AddCone(const Vector3& base, const Vector3& direction, float height, float radius, const Color& color, bool fill = false)
		{
			int slices = 16;
			float thetaIncrement = Math::Constants::TwoPi / slices;
			std::vector<Math::Vector3> list;

			Math::Vector3 d = Math::Normalize(direction);
			float angle = acosf(Math::Dot(Math::Vector3::YAxis, d));
			Math::Vector3 rotationAxis = Math::Cross(Math::Vector3::YAxis, d);
			Math::Matrix4 rotationMatrix = Math::Matrix4::RotationAxis(rotationAxis, angle);

			for (float theta = 0; theta <= Math::Constants::TwoPi; theta += thetaIncrement)
			{
				Math::Vector3 vec3 = Math::TransformNormal(Math::Vector3{ radius * cosf(theta), 0.0f, radius * sinf(theta) }, rotationMatrix) + base;
				list.push_back(vec3);
			}

			if (mVertexCount + list.size() - 1 > mMaxVertexCount)
			{
				return;
			}

			for (size_t i = 0; i < list.size() - 1; i++)
			{
				if (!fill)
				{
					AddLine(list[i], list[i + 1], color);
					Math::Vector3 heightVec = Math::TransformNormal(Math::Vector3{ 0.0f, height, 0.0f }, rotationMatrix) + base;
					AddLine(list[i], heightVec, color);
				}
				else
				{
					Math::Vector3 heightVec = Math::TransformNormal(Math::Vector3{ 0.0f, height, 0.0f }, rotationMatrix) + base;
					AddFace(list[i], heightVec, list[i + 1], color);
					AddFace(list[i], list[i + 1], heightVec, color);
				}
			}
		}


#pragma region 2D Render

		void AddScreenLine(const Vector2& v0, const Vector2& v1, const Color& color)
		{
			if (m2DVertexCount + 2u < mMaxVertexCount)
			{
				m2DLineVertices[m2DVertexCount++] = VertexPC{ Vector3(v0.x, v0.y, 0.0f), color };
				m2DLineVertices[m2DVertexCount++] = VertexPC{ Vector3(v1.x, v1.y, 0.0f), color };

			}
		}

		void AddScreenCircle(const Vector2& center, float radius, const Color& color)
		{
			if (m2DVertexCount + 32u >= mMaxVertexCount) return;
			constexpr int slices = 16;
			constexpr float thetaIncrement = Math::Constants::TwoPi / slices;

			vector<Vector2> list;
			for (float theta = 0.0f; theta <= Math::Constants::TwoPi; theta += thetaIncrement)
			{
				list.push_back(Math::Vector2{ radius * cosf(theta), radius * sinf(theta) } + center);
			}

			for (size_t i = 0, totalSize = list.size() - 1; i < totalSize; ++i)
			{
				AddScreenLine(list[i], list[i + 1], color);
			}
		}

		void AddScreenRect(const Math::Rect& rect, const Color& color)
		{
			// Check if we have enough space
			if (m2DVertexCount + 8 <= mMaxVertexCount)
			{
				const float l = rect.left;
				const float t = rect.top;
				const float r = rect.right;
				const float b = rect.bottom;

				// Add lines

				m2DLineVertices[m2DVertexCount++] = { Math::Vector3(l, t, 0.0f), color };
				m2DLineVertices[m2DVertexCount++] = { Math::Vector3(r, t, 0.0f), color };

				m2DLineVertices[m2DVertexCount++] = { Math::Vector3(r, t, 0.0f), color };
				m2DLineVertices[m2DVertexCount++] = { Math::Vector3(r, b, 0.0f), color };

				m2DLineVertices[m2DVertexCount++] = { Math::Vector3(r, b, 0.0f), color };
				m2DLineVertices[m2DVertexCount++] = { Math::Vector3(l, b, 0.0f), color };

				m2DLineVertices[m2DVertexCount++] = { Math::Vector3(l, b, 0.0f), color };
				m2DLineVertices[m2DVertexCount++] = { Math::Vector3(l, t, 0.0f), color };
			}

			OMEGAASSERT(mVertexCount < mMaxVertexCount, "[SimpleDraw] Too many vertices!");
		}

		void AddScreenArc(const Math::Vector2& center, float radius, float fromAngle, float toAngle, const Math::Vector4& color)
		{
			if (m2DVertexCount + 32 <= mMaxVertexCount)
			{
				const float x = center.x;
				const float y = center.y;
				const float r = radius;

				// Add line
				const float kAngle = (toAngle - fromAngle) / 16.0f;
				for (uint32_t i = 0; i < 16; ++i)
				{
					const float alpha = i * kAngle + fromAngle;
					const float beta = alpha + kAngle;
					const float x0 = x + (r * cos(alpha));
					const float y0 = y + (r * sin(alpha));
					const float x1 = x + (r * cos(beta));
					const float y1 = y + (r * sin(beta));
					m2DLineVertices[m2DVertexCount++] = { Math::Vector3(x0, y0, 0.0f), color };
					m2DLineVertices[m2DVertexCount++] = { Math::Vector3(x1, y1, 0.0f), color };
				}
			}
		}

#pragma endregion

		void Render(const Camera& camera)
		{
			auto matView = camera.GetViewMatrix();
			auto matProj = camera.GetPerspectiveMatrix();
			const auto& transform = Math::Transpose(matView * matProj);
			mConstantBuffer.Update(&transform);
			mConstantBuffer.BindVS(0);

			mVertexShader.Bind();
			mPixelShader.Bind();

			//Draw 3D Lines
			mMeshBuffer.Update(mLineVertices.get(), mVertexCount);
			mMeshBuffer.SetTopology(MeshBuffer::Topology::Lines);
			mMeshBuffer.Draw();

			//Draw 3D Filled
			mMeshBuffer.Update(mFillVertices.get(), mFillVertexCount);
			mMeshBuffer.SetTopology(MeshBuffer::Topology::Triangles);
			mMeshBuffer.Draw();

			//Draw 2D Lines
			const auto& system = GraphicsSystem::Get()->get();
			const uint32_t w = system.GetBackBufferWidth();
			const uint32_t h = system.GetBackBufferHeight();
			Math::Matrix4 screenToNDC
			{
				2.0f / w, 0.0f, 0.0f, 0.0f,
					0.0f, -2.0f / h, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					-1.0f, 1.0f, 0.0f, 1.0f
			};
			auto transposeNDC = Math::Transpose(screenToNDC); // moved to local variable
			mConstantBuffer.Update(&transposeNDC);
			mConstantBuffer.BindVS();

			mMeshBuffer.Update(m2DLineVertices.get(), m2DVertexCount);
			mMeshBuffer.SetTopology(MeshBuffer::Topology::Lines);
			mMeshBuffer.Draw();

			mFillVertexCount = 0;
			mVertexCount = 0;
			m2DVertexCount = 0;
		}

	private:
		Matrix4 mTransform = Matrix4::Identity;

		MeshBuffer mMeshBuffer;
		VertexShader mVertexShader;
		PixelShader mPixelShader;
		ConstantBuffer mConstantBuffer;
		unique_ptr<VertexPC[]> mLineVertices;
		unique_ptr<VertexPC[]> mFillVertices;
		unique_ptr<VertexPC[]> m2DLineVertices;
		uint32_t mVertexCount{ 0u };
		uint32_t m2DVertexCount{ 0u };
		uint32_t mMaxVertexCount{ 0u };
		uint32_t mFillVertexCount{ 0u };
	};

	unique_ptr<SimpleDrawImpl> sInstance{};
}

void SimpleDraw::StaticInitialize(uint32_t maxVertexCount)
{
	sInstance = make_unique<SimpleDrawImpl>();
	sInstance->Initialize(maxVertexCount);
}

void SimpleDraw::StaticTerminate()
{
	sInstance->Terminate();
	sInstance.reset();
}

void SimpleDraw::AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color)
{
	sInstance->AddLine(v0, v1, color);
}

void SimpleDraw::AddFace(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, const Color& color)
{
	sInstance->AddFace(v0, v1, v2, color);
}

void SimpleDraw::AddDisplacement(float length)
{
	sInstance->AddDisplacement(length);
}

void SimpleDraw::AddBox(float length, const Color& color)
{
	sInstance->AddBox(length, color);
}

void SimpleDraw::AddSphere(const Math::Vector3& position, float radius, int rings, int slices, const Color& color)
{
	sInstance->AddSphere(position, radius, rings, slices, color);
}

void SimpleDraw::AddGroundPlane(float size, const Color& color)
{
	sInstance->AddGroundPlane(size, 1.0f, color);
}

void SimpleDraw::AddBone(const Math::Matrix4& transform, const Color& color)
{
	OMEGAASSERT(false, "Implementation is incorrect.");
	sInstance->AddBone(transform, color);
}

void SimpleDraw::AddBone(const Math::Vector3& position, const Math::Vector3& direction, const Color& color, float radius, bool fill)
{
	sInstance->AddBone(position, direction, radius, color, fill);
}

void SimpleDraw::AddTransform(const Math::Matrix4& transform)
{
	sInstance->AddTransform(transform);
}

void SimpleDraw::AddAABB(const Math::AABB& aabb, const Color& color)
{
	sInstance->AddAABB(aabb, color);
}

void SimpleDraw::AddOBB(const Math::OBB& obb, const Color& color)
{
	sInstance->AddOBB(obb, color);
}

void SimpleDraw::AddCylinder(const Math::Vector3& base, const Math::Vector3& direction, float height, float radius, const Color& color, bool fill)
{
	sInstance->AddCylinder(base, direction, height, radius, color, fill);
}

void SimpleDraw::AddCone(float height, float radius, const Color& color, bool fill)
{
	sInstance->AddCone(height, radius, color, fill);
}

void SimpleDraw::AddCone(const Math::Vector3& base, const Math::Vector3& direction, float height, float radius, const Color& color, bool fill)
{
	sInstance->AddCone(base, direction, height, radius, color, fill);
}

void SimpleDraw::AddScreenRect(const Math::Rect& rect, const Color& color)
{
	sInstance->AddScreenRect(rect, color);
}

void SimpleDraw::AddScreenRect(const Math::Vector2& min, const Math::Vector2& max, const Color& color)
{
	Math::Rect rect(min.x, min.y, max.x, max.y);
	sInstance->AddScreenRect(rect, color);
}

void SimpleDraw::AddScreenRect(float left, float top, float right, float bottom, const Color& color)
{
	Math::Rect rect(left, top, right, bottom);
	sInstance->AddScreenRect(rect, color);
}

void SimpleDraw::AddScreenArc(const Math::Vector2& center, float radius, float fromAngle, float toAngle, const Math::Vector4& color)
{
	sInstance->AddScreenArc(center, radius, fromAngle, toAngle, color);
}

void SimpleDraw::AddScreenLine(const Math::Vector2& v0, const Math::Vector2& v1, const Color& color)
{
	sInstance->AddScreenLine(v0, v1, color);
}

void SimpleDraw::AddScreenLine(float x0, float y0, float x1, float y1, const Color& color)
{
	sInstance->AddScreenLine({ x0, y0 }, { x1, y1 }, color);
}

void SimpleDraw::AddScreenCircle(const Math::Circle& circle, const Color& color)
{
	sInstance->AddScreenCircle(circle.center, circle.radius, color);
}

void SimpleDraw::AddScreenCircle(const Math::Vector2& center, float radius, const Color& color)
{
	sInstance->AddScreenCircle(center, radius, color);
}

void SimpleDraw::AddScreenCircle(float centerX, float centerY, float radius, const Color& color)
{
	sInstance->AddScreenCircle({ centerX,centerY }, radius, color);
}

void SimpleDraw::Render(const Camera& camera)
{
	sInstance->Render(camera);
}