#include "GameState.h"

#include <ImGui/Inc/imgui.h>
#include <Math/Inc/RandomHelper.h>

using namespace Omega::Graphics;
using namespace Omega::Physics;
using namespace Omega::Math;
using namespace Omega::Core;
using namespace Omega::Input;

void GameState::Initialize()
{
	mCameraService.Initialize();
	Camera& camera = mCameraService.GetActiveCamera();

	camera.SetNearPlane(0.1f);
	camera.SetFarPlane(300.0f);
	camera.SetPosition({ 0.0f, 1.0f, -5.0f });
	camera.SetLookAt({ 0.0f, 1.0f, 0.0f });

	mRenderManager = RendererManager::Get();

	if (mRenderManager)
	{
		// load sprite 
		std::string name = "Sprites/carrier_0" + std::to_string(1u) + ".png";
		mTexturesIds.at(0) = mRenderManager->get().LoadTexture(name);
	}

	PhysicsWorld::Settings settings;
	settings.drag = 0.3f;
	mPhysicsWorld.Initilize(settings);
	mPhysicsWorld.AddStaticPlane(Plane{ Vector3::YAxis, 0.0f });
}

void GameState::Terminate()
{
	mCameraService.Terminate();
}

void GameState::Update(float deltaTime)
{
	const auto inputSystem = InputSystem::Get();
	const float kMoveSpeed = inputSystem->get().IsKeyDown(KeyCode::LSHIFT) ? 100.0f : 10.0f;
	const float moveSpeedDelta = kMoveSpeed * deltaTime;

	Camera& camera = mCameraService.GetActiveCamera();

	if (inputSystem->get().IsKeyDown(KeyCode::W))
	{
		camera.Walk(moveSpeedDelta);
	}

	if (inputSystem->get().IsKeyDown(KeyCode::S))
	{
		camera.Walk(-moveSpeedDelta);
	}
	if (inputSystem->get().IsKeyDown(KeyCode::D))
	{
		camera.Strafe(moveSpeedDelta);
	}
	if (inputSystem->get().IsKeyDown(KeyCode::A))
	{
		camera.Strafe(-moveSpeedDelta);
	}
	if (inputSystem->get().IsMouseDown(MouseButton::RBUTTON))
	{
		constexpr float kTurnSpeed = 1.0f;
		camera.Yaw(static_cast<float>(inputSystem->get().GetMouseMoveX()) * kTurnSpeed * deltaTime);
		camera.Pitch(static_cast<float>(inputSystem->get().GetMouseMoveY()) * kTurnSpeed * deltaTime);
	}
	mPhysicsWorld.Update(deltaTime);


	mRenderManager->get().DrawScreenText(L"Hello Update", Vector2{ 100.f, 150.f }, 25.f, Colors::Azure);
	mRenderManager->get().DrawScreenText(L"Hello Update 2 ", Vector2{ 100.f, 170.f }, 25.f, Colors::Chocolate);
	mRenderManager->get().DrawScreenText({ L"Hello Update 3 - with args", 25.f, 100.f, 190.f, Colors::Gold });
}

void GameState::Render()
{
	mRenderManager->get().DrawScreenText(L"Hello RENDER", Vector2{ 100.f, 120.f }, 25.f, Colors::Red);
	mRenderManager->get().DrawSprite({ mTexturesIds.at(0), Vector2{ 600.f, 120.f }, 0.0f });

	SimpleDraw::AddGroundPlane(20.f);
	const Camera& camera = mCameraService.GetActiveCamera();
	SimpleDraw::Render(camera);

	mPhysicsWorld.DebugDraw();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Delta Time (%f)", TimeUtil::GetDeltaTime());
	ImGui::Text("Time (%f)", TimeUtil::GetTime());
	ImGui::Text("FPS (%d)", FpsHelper::GetCurrentFps());

	ImGui::End();

	ImGui::Begin("Physics 2", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::Button("Use Particles"))
	{
		mPhysicsWorld.GetParticleManager().ShotSingleParticles();
	}

	if (ImGui::Button("Use Stick Particles"))
	{
		mPhysicsWorld.GetParticleManager().ShotStickParticles();
	}

	if (ImGui::Button("Use Tetrahedron Particles"))
	{
		mPhysicsWorld.GetParticleManager().ShotTetrahedronParticles();
	}

	if (ImGui::Button("Use Burst Particles"))
	{
		mPhysicsWorld.GetParticleManager().BurstParticles();
	}

	if (ImGui::Button("Clear"))
	{
		mPhysicsWorld.Clear();
	}

	ImGui::End();
}

void GameState::RawParticles()
{
	/*if (auto& tempPool = mPhysicsWorld.GetPoolParticle();
		tempPool.ObjectInUse() < tempPool.Size())
	{
		auto InitializeParticle = [&](Particle& particle, const Omega::Math::Vector3& position)
			{
				Omega::Math::RandomHelper randomHelper;
				particle.SetPosition(position);
				particle.SetVelocity({ randomHelper.RandomVector3({-0.05f, 0.1f, -0.05f},{0.05f, 0.5f, 0.05f}) });
				particle.radius = 0.1f;
				particle.bounce = 0.3f;
			};

		const auto& particle = tempPool.AcquireObject().lock();
		InitializeParticle(*particle, { 0.0f, 5.0f, 0.0f });
	}*/
}

void GameState::UseStickParticles()
{
	/*if (auto& pool = mPhysicsWorld.GetPoolParticle();
		pool.ObjectInUse() <= pool.Size() - 2u)
	{
		auto InitializeParticle = [&](Particle& particle, const Omega::Math::Vector3& position)
			{
				Omega::Math::RandomHelper randomHelper;
				particle.SetPosition(position);
				particle.SetVelocity({ randomHelper.RandomVector3({-0.05f, 0.1f, -0.05f},{0.05f, 0.5f, 0.05f}) });
				particle.radius = 0.1f;
				particle.bounce = 0.3f;
			};

		auto particle1 = pool.AcquireObject().lock();
		auto particle2 = pool.AcquireObject().lock();

		InitializeParticle(*particle1, { 0.5f, 5.0f, 0.0f });
		InitializeParticle(*particle2, { -0.5f, 5.0f, 0.0f });

		mPhysicsWorld.CreateSpring({ particle1.get(), particle2.get() });
	}*/
}

void GameState::UseTetrahedronParticles()
{
	/*if (auto& pool = mPhysicsWorld.GetPoolParticle();
		pool.ObjectInUse() <= pool.Size() - 4u)
	{
		auto InitializeParticle = [&](Particle& particle, const Omega::Math::Vector3& position)
			{
				Omega::Math::RandomHelper randomHelper;
				particle.SetPosition(position);
				particle.SetVelocity({ randomHelper.RandomVector3({-0.05f, 0.1f, -0.05f},{0.05f, 0.5f, 0.05f}) });
				particle.radius = 0.1f;
				particle.bounce = 0.3f;
			};

		auto particle1 = pool.AcquireObject().lock();
		auto particle2 = pool.AcquireObject().lock();
		auto particle3 = pool.AcquireObject().lock();
		auto particle4 = pool.AcquireObject().lock();

		InitializeParticle(*particle1, { -0.5f, 5.0f, 0.0f });
		InitializeParticle(*particle2, { 0.0f, 5.0f, 1.0f });
		InitializeParticle(*particle3, { 0.5f, 5.0f, 0.0f });
		InitializeParticle(*particle4, { 0.0f, 6.0f, 0.0f });

		mPhysicsWorld.CreateSpring({ particle1.get(), particle2.get() });
		mPhysicsWorld.CreateSpring({ particle2.get(), particle3.get() });
		mPhysicsWorld.CreateSpring({ particle3.get(), particle1.get() });

		mPhysicsWorld.CreateSpring({ particle1.get(), particle4.get() });
		mPhysicsWorld.CreateSpring({ particle2.get(), particle4.get() });
		mPhysicsWorld.CreateSpring({ particle3.get(), particle4.get() });
	}*/

}
