#include "Precompiled.h"
#include "Cloth.h"

using namespace Omega;
using namespace Omega::Graphics;
using namespace Omega::Math;
using namespace Omega::Physics;


//CONTINUAR VER ISSO AQUI
void Cloth::Initialize(const std::filesystem::path& texturePath, uint32_t size)
{
	mSize = size;
	// Add Mesh for cloth texture
	mMeshPlane = MeshBuilder::CreatePlanePX(size, size);
	mMeshBuffer.Initialize(mMeshPlane, true);
	std::filesystem::path doTexturingShaderPath = L"../../Assets/Shaders/DoTexturing.fx";
	mVertexShader.Initialize(doTexturingShaderPath, VertexPX::Format);
	mPixelShader.Initialize(doTexturingShaderPath);

	mSampler.Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Wrap);
	mTexture.Initialize(texturePath);

	mConstantBuffer.Initialize(sizeof(Matrix4));
}

void Cloth::Render(const Camera& camera)
{
	auto world = Math::Matrix4::Identity;
	auto view = camera.GetViewMatrix();
	auto projection = camera.GetPerspectiveMatrix();

	mConstantBuffer.BindVS();
	mVertexShader.Bind();
	mPixelShader.Bind();
	mSampler.BindPS();
	mTexture.BindVS();
	
	auto matrixViewProjection = Transpose(world * view * projection);
	mConstantBuffer.Update(&matrixViewProjection);

	mMeshBuffer.Draw();
}

void Cloth::ShowParticles()
{
	mParticles.clear();
	mPhysicsWorld.Clear(true);
	const float offsetX = mSize * 0.5f;
	const float offsetY = mSize * 0.5f + 10.f;
	for (float y = 0.f; y < mSize; y += 1.0f)
	{
		for (float x = 0.f; x < mSize; x += 1.0f)
		{
			auto p1 = new Particle();
			p1->SetPosition({ -offsetX + x, offsetY - y , 0.0f });
			p1->radius = 0.1f;
			p1->SetVelocity(Random::RandomFloat(0.01f, 0.1f));
			mPhysicsWorld.AddParticle(p1);
			mParticles.push_back(p1);
		}
	}

	for (float y = 0.f; y < mSize; y += 1.0f)
	{
		for (float x = 0.f; x < mSize; x += 1.0f)
		{
			if ((y == 0.f) && (x == mSize - 1.f || x == 0.f))
			{
				mPhysicsWorld.AddConstraint(new Fixed(mParticles[static_cast<size_t>(y * mSize + x)]));
			}
			if (x + 1.f < mSize)
			{
				mPhysicsWorld.AddConstraint(new Spring(mParticles[static_cast<size_t>(y * mSize + x)], mParticles[static_cast<size_t>(y * mSize + x + 1.f)]));
			}

			if (y + 1.f < mSize)
			{
				mPhysicsWorld.AddConstraint(new Spring(mParticles[static_cast<size_t>(y * mSize + x)], mParticles[static_cast<size_t>((y + 1.f) * mSize + x)]));
			}
		}
	}
}

void Cloth::Update()
{
	if (mMeshPlane.vertices.size() == mSize)
	{
		for (size_t i = 0; i < mParticles.size(); i++)
		{
			mMeshPlane.vertices[i].position = mParticles[i]->position;
		}
	}

	mMeshBuffer.Update(mMeshPlane.vertices.data(), static_cast<uint32_t>(mMeshPlane.vertices.size()));
}

void Cloth::Terminate()
{
	mConstantBuffer.Terminate();
	mSampler.Terminate();
	mTexture.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}
