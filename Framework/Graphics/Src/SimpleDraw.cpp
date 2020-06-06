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
using namespace Omega::Graphics;
using namespace std;
namespace
{
	class SimpleDrawImpl
	{
	public:

		void Initialize(uint32_t maxVertexCount)
		{
			mVertexShader.Initialize("../../Assets/Shaders/SimpleDraw.fx", VertexPC::Format);
			mPixelShader.Initialize("../../Assets/Shaders/SimpleDraw.fx");
			mConstantBuffer.Initialize(sizeof(Math::Matrix4));
			mMeshBuffer.Initialize<VertexPC>(nullptr, maxVertexCount, true);
			mLineVertices = make_unique<VertexPC[]>(maxVertexCount);
			mFillVertices = make_unique<VertexPC[]>(static_cast<size_t>(maxVertexCount * 3.0f));
			mVertexCount = 0;
			mFillVertexCount = 0;
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
			if (mVertexCount + 2 < mMaxVertexCount)
			{
				mLineVertices[mVertexCount++] = VertexPC{ v0,color };
				mLineVertices[mVertexCount++] = VertexPC{ v1,color };
			}
		}

		void AddFace(const Math::Vector3& v0, const  Math::Vector3& v1, const  Math::Vector3& v2, const Color& color)
		{
			if (mFillVertexCount + 3 < mFillVertexCount)
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
			AddLine(Math::Vector3{ -length, -length , -length }, Math::Vector3{ length, -length , -length }, color);
			AddLine(Math::Vector3{ -length, -length , -length }, Math::Vector3{ -length, length , -length }, color);
			AddLine(Math::Vector3{ -length, -length , -length }, Math::Vector3{ -length, -length , length }, color);
			AddLine(Math::Vector3{ -length, length , -length }, Math::Vector3{ length, length , -length }, color);
			AddLine(Math::Vector3{ -length, length , -length }, Math::Vector3{ -length, length , length }, color);
			AddLine(Math::Vector3{ length, length , -length }, Math::Vector3{ length, length , length }, color);
			AddLine(Math::Vector3{ length, length , length }, Math::Vector3{ -length, length , length }, color);
			AddLine(Math::Vector3{ length, length , -length }, Math::Vector3{ length, -length , -length }, color);
			AddLine(Math::Vector3{ length, -length , -length }, Math::Vector3{ length, -length , length }, color);
			AddLine(Math::Vector3{ length, length , length }, Math::Vector3{ -length, length , length }, color);
			AddLine(Math::Vector3{ length, length , length }, Math::Vector3{ length, -length , length }, color);
			AddLine(Math::Vector3{ length, -length , length }, Math::Vector3{ -length, -length , length }, color);
			AddLine(Math::Vector3{ -length, -length , length }, Math::Vector3{ -length, length , length }, color);
		}

		void AddSphere(const Math::Vector3& position, float radius, int rings, int slices, const Color& color)
		{
			const float x = position.x;
			const float y = position.y;
			const float z = position.z;

			const uint32_t kSlices = Math::Max<uint32_t>(3u, slices);
			const uint32_t kRings = Math::Max<uint32_t>(2u, rings);
			const uint32_t kLines = (4 * kSlices * kRings) - (2 * kSlices);

			// Check if we have enough space
			if (mVertexCount + kLines <= mMaxVertexCount)
			{
				// Add lines
				const float kTheta = Math::Constants::Pi / (float)kRings;
				const float kPhi = Math::Constants::TwoPi / (float)kSlices;
				for (uint32_t j = 0; j < kSlices; ++j)
				{
					for (uint32_t i = 0; i < kRings; ++i)
					{
						const float a = i * kTheta;
						const float b = a + kTheta;
						const float ay = radius * cosf(a);
						const float by = radius * cosf(b);

						const float theta = j * kPhi;
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

		void AddTransform(const Math::Matrix4& transform)
		{
			Math::Vector3 position = Math::GetTranslation(transform);
			Math::Vector3 right = Math::GetRight(transform);
			Math::Vector3 up = Math::GetUp(transform);
			Math::Vector3 forward = Math::GetForward(transform);
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

		void Render(const Camera& camera)
		{
			auto matView = camera.GetViewMatrix();
			auto matProj = camera.GetPerspectiveMatrix();
			auto transform = Math::Transpose(matView * matProj);
			mConstantBuffer.Update(&transform);
			mConstantBuffer.BindVS(0);

			mVertexShader.Bind();
			mPixelShader.Bind();

			mMeshBuffer.Update(mLineVertices.get(), mVertexCount);
			mMeshBuffer.SetTopology(MeshBuffer::Topology::Lines);
			mMeshBuffer.Draw();

			auto system = GraphicsSystem::Get();

			const uint32_t w = system->GetBackBufferWidth();
			const uint32_t h = system->GetBackBufferHeight();
			Math::Matrix4 screenToNDC
			{
				2.0f / w, 0.0f,0.0f,0.0f,
				0.0f, -2.0f / h, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f,0.0f,
				-1.0f, 1.0f, 0.0f,1.0f
			};
			mConstantBuffer.Update(&Math::Transpose(screenToNDC));

			mMeshBuffer.Update(mFillVertices.get(), mVertexCount);
			mMeshBuffer.SetTopology(MeshBuffer::Topology::Triangles);
			mMeshBuffer.Draw();

			mFillVertexCount = 0;
			mVertexCount = 0;
		}

	private:
		VertexShader mVertexShader;
		PixelShader mPixelShader;
		ConstantBuffer mConstantBuffer;
		MeshBuffer mMeshBuffer;
		unique_ptr<VertexPC[]> mLineVertices;
		unique_ptr<VertexPC[]> mFillVertices;
		unique_ptr<VertexPC[]> m2DLineVertices;
		uint32_t mVertexCount = 0;
		uint32_t mMaxVertexCount = 0;
		uint32_t mFillVertexCount = 0;

		Math::Matrix4 mTransform;
	};

	unique_ptr<SimpleDrawImpl> sInstance;
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
	const float halfSize = size * 0.5f;
	for (float i = -halfSize; i <= halfSize; i += 1.0f)
	{
		sInstance->AddLine({ i, 0.0f, -halfSize }, { i, 0.0f, halfSize }, color);
		sInstance->AddLine({ halfSize, 0.0f,  -i }, { -halfSize, 0.0f, -i }, color);
	}
}

void SimpleDraw::AddBone(const Math::Vector3& position, const Math::Matrix4& transform)
{
	auto r = Math::GetRight(transform);
	auto u = Math::GetUp(transform);
	auto l = Math::GetLook(transform);
	auto p = Math::GetTranslation(transform);
	AddSphere(position, 0.5, 5, 6, Colors::BlueViolet);
	sInstance->AddLine(p, p + r * 0.1f, Colors::Red);
	sInstance->AddLine(p, p + u * 0.1f, Colors::Green);
	sInstance->AddLine(p, p + l * 0.1f, Colors::Blue);
}

void SimpleDraw::AddTransform(const Math::Matrix4& transform)
{
	sInstance->AddTransform(transform);
}

void SimpleDraw::AddOBB(const Math::OBB& obb, const Color& color)
{
	sInstance->AddOBB(obb, color);
}

void SimpleDraw::Render(const Camera& camera)
{
	sInstance->Render(camera);
}