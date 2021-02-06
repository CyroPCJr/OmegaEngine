#include "Precompiled.h"
#include "Cloth.h"

using namespace Omega;
using namespace Omega::Graphics;
using namespace Omega::Math;
using namespace Omega::Physics;

void Cloth::Initialize(const std::filesystem::path& texturePath, uint32_t width, uint32_t height)
{
	PhysicsWorld::Settings settings;
	settings.gravity = { 0.0f, -9.8f, 0.0f };
	settings.timeStep = 1.0f / 60.0f;
	settings.drag = 0.3f;
	settings.iterations = 1;
	mPhysicsWorld.Initilize(settings);

	mWidth = width;
	mHeight = height;
	mMeshPlane = MeshBuilder::CreatePlanePX(width, height);
	mMeshBuffer.Initialize(mMeshPlane, true);
	std::filesystem::path doTexturingShaderPath = L"../../Assets/Shaders/DoTexturing.fx";
	mVertexShader.Initialize(doTexturingShaderPath, VertexPX::Format);
	mPixelShader.Initialize(doTexturingShaderPath);

	mSampler.Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Border);
	mTexture.Initialize(texturePath);

	mConstantBuffer.Initialize(sizeof(Matrix4));
}

void Cloth::Render(const Camera& camera)
{
	if (!mIsUseCloth) return;

	//auto world = Math::Matrix4::Identity;
	auto view = camera.GetViewMatrix();
	auto projection = camera.GetPerspectiveMatrix();

	mConstantBuffer.BindVS();
	mVertexShader.Bind();
	mPixelShader.Bind();
	mSampler.BindPS();
	mTexture.BindPS();

	auto matrixViewProjection = Transpose(view * projection);
	mConstantBuffer.Update(&matrixViewProjection);
	mMeshBuffer.Update(mMeshPlane.vertices.data(), static_cast<uint32_t>(mMeshPlane.vertices.size()));
	mMeshBuffer.Draw();
}

void Cloth::ShowCloth(const Omega::Math::Vector3& position)
{
	mIsUseCloth = true;
	Math::Vector3 offset = { -0.5f * mWidth + position.x, 0.5f * mHeight + position.y, 0.0f };
	mParticles.clear();
	mPhysicsWorld.Clear(true);
	for (uint32_t y = 0; y < mHeight; y++)
	{
		for (uint32_t x = 0; x < mWidth; x++)
		{
			mParticles.push_back(new Particle());
			mParticles.back()->SetPosition({ offset.x + static_cast<float>(x), offset.y - static_cast<float>(y) , offset.z });
			mParticles.back()->SetVelocity({ Random::RandomFloat(-0.05f,0.01f) ,Random::RandomFloat(-0.1f,0.5f),Random::RandomFloat(-0.05f,0.05f) });
			mParticles.back()->radius = 0.1f;
			mParticles.back()->bounce = 0.3f;
			mPhysicsWorld.AddParticle(mParticles.back());
		}
	}

	for (uint32_t y = 0; y < mHeight; y++)
	{
		for (uint32_t x = 0; x < mWidth; x++)
		{
			//if (y == 0 && (x == 0 || x == static_cast<int>(mWidth * 0.5f) || x == mWidth - 1))
			if (y == 0 || x == mWidth) // now fixed the particles all in the top position
			{
				auto c1 = new Fixed(mParticles[GetIndex(x, y, mWidth)]); // fixed
				mPhysicsWorld.AddConstraint(c1);
			}

			if (x + 1 < mWidth)
			{
				auto c1 = new Spring(mParticles[GetIndex(x, y, mWidth)], mParticles[GetIndex(x + 1, y, mWidth)]);
				mPhysicsWorld.AddConstraint(c1);
			}

			if (y + 1 < mHeight)
			{
				auto c2 = new Spring(mParticles[GetIndex(x, y, mWidth)], mParticles[GetIndex(x, y + 1, mWidth)]);
				mPhysicsWorld.AddConstraint(c2);
			}
		}
	}
}

void Cloth::Update(float deltaTime)
{
	mPhysicsWorld.Update(deltaTime);

	if (mIsUseCloth)
	{
		for (size_t i = 0; i < mParticles.size(); ++i)
		{
			mMeshPlane.vertices[i].position = mParticles[i]->position;
		}
	}
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
