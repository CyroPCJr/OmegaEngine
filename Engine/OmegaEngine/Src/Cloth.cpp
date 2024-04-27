#include "Precompiled.h"
#include "Cloth.h"

using namespace Omega;
using namespace Omega::Graphics;
using namespace Omega::Math;
using namespace Omega::Physics;
using namespace Omega::Core;

void Cloth::Initialize(const Settings& settings)
{
	mSettings = settings;
	PhysicsWorld::Settings physicsSettings;
	physicsSettings.gravity = { 0.0f, -9.8f, 0.0f };
	physicsSettings.drag = 0.3f;
	physicsSettings.iterations = 1;
	mPhysicsWorld.Initilize(physicsSettings);

	mMeshPlane = MeshBuilder::CreatePlanePX(mSettings.width, mSettings.height);
	mMeshBuffer.Initialize(mMeshPlane, true);

	const std::filesystem::path doTexturingShaderPath = L"../../Assets/Shaders/DoTexturing.fx";
	mVertexShader.Initialize(doTexturingShaderPath, VertexPX::Format);
	mPixelShader.Initialize(doTexturingShaderPath);
	mSampler.Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Border);
	//TODO: corrigir isso e executar o ctor ao inves do metodo Initialize
	//mTexture.Initialize(mSettings.path); 

	mConstantBuffer.Initialize(sizeof(Matrix4));
	mRasterizer.Initialize(RasterizerState::CullMode::None, RasterizerState::FillMode::Solid);

	InitializeParticles();
}

void Cloth::Render(const Camera& camera)
{
	if (!mShowCloth) return;
	if (mShowTexture)
	{
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

		mRasterizer.Set();
		mMeshBuffer.Draw();
		mRasterizer.Clear();
	}
	else
	{
		mPhysicsWorld.DebugDraw();
	}
}

void Cloth::Update(float deltaTime)
{
	mPhysicsWorld.Update(deltaTime);

	if (mShowCloth)
	{
		/*for (size_t i = 0; i < mPhysicsWorld.GetParticles().size(); ++i)
		{
			mMeshPlane.vertices[i].position = mPhysicsWorld.GetParticles()[i]->position;
		}*/
	}
}

void Cloth::Terminate()
{
	mConstantBuffer.Terminate();
	mSampler.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
	mRasterizer.Terminate();
}

void Cloth::InitializeParticles()
{
	Math::Vector3 offset = { -0.5f * mSettings.width + mSettings.startPosition.x, 0.5f * mSettings.height + mSettings.startPosition.y, 0.0f };
	//mParticles.clear();
	mPhysicsWorld.Clear(true);
	for (uint32_t y = 0; y < mSettings.height; y++)
	{
		for (uint32_t x = 0; x < mSettings.width; x++)
		{
			//auto particle = std::make_unique<Particle>();
			
			/*particle->SetPosition({ offset.x + static_cast<float>(x), offset.y - static_cast<float>(y) , offset.z });
			particle->SetVelocity(Random::RandomVector3({ -0.05f, -0.01f, -0.05f }, { 0.01f, 0.5f, 0.05f }));
			particle->radius = 0.1f;
			particle->bounce = 0.3f;*/
			//mPhysicsWorld.AddParticle(particle);


			//BCK
			/*mParticles.push_back(new Particle());
			mParticles.back()->SetPosition({ offset.x + static_cast<float>(x), offset.y - static_cast<float>(y) , offset.z });
			mParticles.back()->SetVelocity({ Random::RandomFloat(-0.05f,0.01f) ,Random::RandomFloat(-0.1f,0.5f),Random::RandomFloat(-0.05f,0.05f) });
			mParticles.back()->radius = 0.1f;
			mParticles.back()->bounce = 0.3f;
			mPhysicsWorld.AddParticle(mParticles.back());*/
		}
	}


	//for (uint32_t y = 0; y < mSettings.height; y++)
	//{
	//	for (uint32_t x = 0; x < mSettings.width; x++)
	//	{
	//		const auto particle = mPhysicsWorld.GetParticles()[GetIndex(x, y, mSettings.width)].get();

	//		////if (y == 0 && (x == 0 || x == static_cast<int>(mWidth * 0.5f) || x == mWidth - 1))
	//		if (y == 0 || x == mSettings.width) // now fixed the particles all in the top position
	//		{
	//			//auto c1 = new Fixed(mPhysicsWorld.GetParticles()[GetIndex(x, y, mSettings.width)].get()); // fixed
	//			std::unique_ptr<Constraint> c1 = std::make_unique<Fixed>(mPhysicsWorld.GetParticles()[GetIndex(x, y, mSettings.width)].get());
	//			
	//			mPhysicsWorld.AddConstraint(c1);
	//		}

	//		if (x + 1 < mSettings.width)
	//		{
	//			//auto c1 = new Spring(mPhysicsWorld.GetParticles()[GetIndex(x, y, mSettings.width)].get(), mPhysicsWorld.GetParticles()[GetIndex(x + 1, y, mSettings.width)].get());
	//			std::unique_ptr<Constraint> c1 = std::make_unique<Spring>(mPhysicsWorld.GetParticles()[GetIndex(x, y, mSettings.width)].get(), mPhysicsWorld.GetParticles()[GetIndex(x + 1, y, mSettings.width)].get());
	//			//auto nextParticle = mPhysicsWorld.GetParticles()[GetIndex(x + 1, y, mSettings.width)].get();
	//			//std::unique_ptr<Constraint> c1 = std::make_unique<Spring>(particle, nextParticle);
	//			mPhysicsWorld.AddConstraint(c1);
	//		}

	//		if (y + 1 < mSettings.height)
	//		{
	//			//auto c2 = new Spring(mPhysicsWorld.GetParticles()[GetIndex(x, y, mSettings.width)].get(), mPhysicsWorld.GetParticles()[GetIndex(x, y + 1, mSettings.width)].get());
	//			std::unique_ptr<Constraint> c2 = std::make_unique<Spring>(mPhysicsWorld.GetParticles()[GetIndex(x, y, mSettings.width)].get(), mPhysicsWorld.GetParticles()[GetIndex(x, y + 1, mSettings.width)].get());
	//			//auto nextParticle = mPhysicsWorld.GetParticles()[GetIndex(x + 1, y, mSettings.width)].get();
	//			//std::unique_ptr<Constraint> c2 = std::make_unique<Spring>(particle, nextParticle);
	//			mPhysicsWorld.AddConstraint(c2);
	//		}
	//	}
	//}
}
