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
			mFillVertices = make_unique<VertexPC[]>(maxVertexCount*3.0f);
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
				mFillVertices[mFillVertexCount++] = VertexPC{v0, color};
				mFillVertices[mFillVertexCount++] = VertexPC{v1, color};
				mFillVertices[mFillVertexCount++] = VertexPC{v2, color};
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
			AddLine(Math::Vector3{ -length, length , -length }, Math::Vector3{ length, length , length }, color);
			AddLine(Math::Vector3{ -length, length , -length }, Math::Vector3{ -length, length , length }, color);
			AddLine(Math::Vector3{ length, length , -length }, Math::Vector3{ length, length , length }, color);
			AddLine(Math::Vector3{ length, length , -length }, Math::Vector3{ -length, length , length }, color);
			AddLine(Math::Vector3{ length, length , -length }, Math::Vector3{ length, -length , -length }, color);
			AddLine(Math::Vector3{ length, -length , -length }, Math::Vector3{ length, -length , length }, color);
			AddLine(Math::Vector3{ length, length , -length }, Math::Vector3{ -length, length , length }, color);
			AddLine(Math::Vector3{ length, length , -length }, Math::Vector3{ length, -length , length }, color);
			AddLine(Math::Vector3{ length, -length , length }, Math::Vector3{ -length, -length , length }, color);
			AddLine(Math::Vector3{ -length, -length , length }, Math::Vector3{ -length, length , length }, color);
		}

		void AddSphere(float radius, int rings, int slices, const Color& color)
		{
			for (float phi = 0; phi < Math::Constants::Pi; phi+= (Math::Constants::Pi/ rings))
			{
				for (float theta = 0; theta < Math::Constants::TwoPi; theta+= (Math::Constants::TwoPi/ slices))
				{
					auto vec = Math::Vector3
					{
						sinf(phi)*cosf(theta)*radius,
						cosf(phi)*radius,
						sinf(theta) * sinf(phi) * radius
					};
					mLineVertices[mVertexCount++] = VertexPC{vec, color};
				}
			}
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
				2.0 / w, 0.0f,0.0f,0.0f,
				0.0f, -2.0f/h, 0.0f, 0.0f,
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

void SimpleDraw::AddFace(const Math::Vector3 & v0, const Math::Vector3 & v1, const Math::Vector3 & v2, const Color & color)
{
	sInstance->AddFace(v0,v1,v2, color);
}

void SimpleDraw::AddDisplacement(float length)
{
	sInstance->AddDisplacement(length);
}

void SimpleDraw::AddBox(float length, const Color & color)
{
	sInstance->AddBox(length, color);
}

void SimpleDraw::AddSphere(float radius, int rings, int slices, const Color & color)
{
	sInstance->AddSphere(radius, rings, slices, color);
}

void SimpleDraw::AddGroundPlane(float size, const Color & color)
{
	const float halfSize = size *0.5f;
	for (float i = 0; i < halfSize; i+=1.0f)
	{
		sInstance->AddLine({ i, 0.0f, -halfSize }, {i, 0.0f, halfSize}, color);
		sInstance->AddLine({ halfSize, 0.0f,  i}, { halfSize, 0.0f, i}, color);
	}
}

void SimpleDraw::AddBone(const Math::Matrix4 & transform)
{
	//TODO:
}

void SimpleDraw::AddTransform(const Math::Matrix4 & transform)
{
	//TODO:
}

void SimpleDraw::Render(const Camera& camera)
{
	sInstance->Render(camera);
}