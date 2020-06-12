#include "GameState.h"

#include <ImGui/Inc/imgui.h>

using namespace Omega::Graphics;
using namespace Omega::Input;
using namespace Omega::Math;
using namespace Omega::Physics;

void GameState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Black);

	mCamera.SetNearPlane(0.1f);
	mCamera.SetFarPlane(300.0f);
	mCamera.SetPosition({ 0.0f, 10.0f, -30.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	PhysicsWorld::Settings settings;
	settings.gravity = { 0.0f, -9.8f, 0.0f };
	settings.timeStep = 1.0f / 60.0f;
	settings.drag = 0.3f;
	settings.iterations = 1;
	mPhysicsWorld.Initilize(settings);
	mPhysicsWorld.AddStaticPlane({ Vector3::YAxis, 0.0f });
	mPhysicsWorld.AddStaticOBB({ {0.0f, 2.0f, 0.0f}, { 4.0f, 0.5f,5.0f }, Quaternion::RotationAxis(Vector3::ZAxis, 10.0f * Constants::DegToRad) });
}

void GameState::Terminate()
{
	mPhysicsWorld.Clear();
}

void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();

	const float kMoveSpeed = inputSystem->IsKeyDown(KeyCode::LSHIFT) ? 100.0f : 10.0f;
	const float kTurnSpeed = 1.0f;

	if (inputSystem->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(kMoveSpeed * deltaTime);
	}

	if (inputSystem->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-kMoveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(kMoveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-kMoveSpeed * deltaTime);
	}
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(inputSystem->GetMouseMoveX() * kTurnSpeed * deltaTime);
		mCamera.Pitch(inputSystem->GetMouseMoveY() * kTurnSpeed * deltaTime);
	}

	mPhysicsWorld.Update(deltaTime);
}

void GameState::Render()
{
	mPhysicsWorld.DebugDraw();

	SimpleDraw::AddGroundPlane(30.0f);
	


	SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{

	ImGui::Begin("Physics", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	float lines[120];
	for (int n = 0; n < 120; ++n)
	{
		lines[n] = 1000.0f / ImGui::GetIO().Framerate;
	}
	ImGui::PlotLines("FPS", lines, IM_ARRAYSIZE(lines));

	ImGui::SliderFloat("Cloth size", &mClothSize, 1.0f, 30.0f);
	if (ImGui::Button("Particles!"))
	{
		mPhysicsWorld.Clear(true);
		for (int i = 0; i < 100; ++i)
		{
			auto p = new Particle();
			p->SetPosition({ 0.0f, 5.0f, 0.0f });

			p->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f) , RandomFloat(-0.05f, 0.05f) });
			p->radius = 0.1f;
			p->bounce = 0.3f;
			mPhysicsWorld.AddParticle(p);
		}
	}
	if (ImGui::Button("Stick!"))
	{
		mPhysicsWorld.Clear(true);
		for (int i = 0; i < 50; ++i)
		{
			auto p1 = new Particle();
			auto p2 = new Particle();
			p1->SetPosition({ 0.5f, 5.0f, 0.0f });
			p1->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p1->radius = 0.1f;
			p1->bounce = 0.3f;
			p2->SetPosition({ -0.5f, 5.0f, 0.0f });
			p2->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p2->radius = 0.1f;
			p2->bounce = 0.3f;
			mPhysicsWorld.AddParticle(p1);
			mPhysicsWorld.AddParticle(p2);
			mPhysicsWorld.AddConstraint(new Spring(p1, p2));
		}
	}
	if (ImGui::Button("Tetrahedron!"))
	{
		mPhysicsWorld.Clear(true);
		for (int i = 0; i < 20; ++i)
		{
			auto p1 = new Particle();
			auto p2 = new Particle();
			auto p3 = new Particle();
			auto p4 = new Particle();
			p1->SetPosition({ -0.5f, 5.0f, 0.0f });
			p1->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p1->radius = 0.1f;
			p1->bounce = 0.3f;

			p2->SetPosition({ 0.0f, 5.0f, 1.0f });
			p2->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p2->radius = 0.1f;
			p2->bounce = 0.3f;

			p3->SetPosition({ 0.5f, 5.0f, 0.0f });
			p3->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p3->radius = 0.1f;
			p3->bounce = 0.3f;

			p4->SetPosition({ 0.0f, 6.0f, 0.0f });
			p4->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p4->radius = 0.1f;
			p4->bounce = 0.3f;

			mPhysicsWorld.AddParticle(p1);
			mPhysicsWorld.AddParticle(p2);
			mPhysicsWorld.AddParticle(p3);
			mPhysicsWorld.AddParticle(p4);

			mPhysicsWorld.AddConstraint(new Spring(p1, p2, 1.0f));
			mPhysicsWorld.AddConstraint(new Spring(p2, p3, 1.0f));
			mPhysicsWorld.AddConstraint(new Spring(p3, p1, 1.0f));

			mPhysicsWorld.AddConstraint(new Spring(p1, p4, 1.0f));
			mPhysicsWorld.AddConstraint(new Spring(p2, p4, 1.0f));
			mPhysicsWorld.AddConstraint(new Spring(p3, p4, 1.0f));
		}
	}

	if (ImGui::Button("Cube!"))
	{
		const float restLength = 5.0f;
		mPhysicsWorld.Clear(true);
		for (int i = 0; i < 1; ++i)
		{
			auto p1 = new Particle();
			auto p2 = new Particle();
			auto p3 = new Particle();
			auto p4 = new Particle();
			auto p5 = new Particle();
			auto p6 = new Particle();
			auto p7 = new Particle();
			auto p8 = new Particle();

			p1->SetPosition({ -0.5f, 5.0f, 0.0f });
			p1->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p1->radius = 0.1f;
			p1->bounce = 0.3f;

			p2->SetPosition({ 0.5f, 5.0f, 0.0f });
			p2->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p2->radius = 0.1f;
			p2->bounce = 0.3f;

			p3->SetPosition({ 1.0f, 5.0f, 0.0f });
			p3->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p3->radius = 0.1f;
			p3->bounce = 0.3f;

			p4->SetPosition({ 0.5f, 6.0f, 1.0f });
			p4->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p4->radius = 0.1f;
			p4->bounce = 0.3f;

			p5->SetPosition({ -0.5f, 5.0f, 0.5f });
			p5->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p5->radius = 0.1f;
			p5->bounce = 0.3f;

			p6->SetPosition({ 0.5f, 5.0f, -0.5f });
			p6->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p6->radius = 0.1f;
			p6->bounce = 0.3f;

			p7->SetPosition({ 0.5f, 6.0f, 1.0f });
			p7->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p7->radius = 0.1f;
			p7->bounce = 0.3f;

			p8->SetPosition({ 0.5f, 6.0f, 1.0f });
			p8->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p8->radius = 0.1f;
			p8->bounce = 0.3f;

			mPhysicsWorld.AddParticle(p1);
			mPhysicsWorld.AddParticle(p2);
			mPhysicsWorld.AddParticle(p3);
			mPhysicsWorld.AddParticle(p4);

			mPhysicsWorld.AddParticle(p5);
			mPhysicsWorld.AddParticle(p6);
			mPhysicsWorld.AddParticle(p7);
			mPhysicsWorld.AddParticle(p8);

			//TODO: continuar a debugando essa joca aqui
			mPhysicsWorld.AddConstraint(new Spring(p1, p2, restLength));
			mPhysicsWorld.AddConstraint(new Spring(p2, p3, restLength));
			mPhysicsWorld.AddConstraint(new Spring(p3, p4, restLength));
			mPhysicsWorld.AddConstraint(new Spring(p4, p1, restLength));

			mPhysicsWorld.AddConstraint(new Spring(p5, p6, restLength));
			mPhysicsWorld.AddConstraint(new Spring(p6, p7, restLength));
			mPhysicsWorld.AddConstraint(new Spring(p7, p8, restLength));
			mPhysicsWorld.AddConstraint(new Spring(p8, p5, restLength));

			mPhysicsWorld.AddConstraint(new Spring(p1, p5, restLength));
			mPhysicsWorld.AddConstraint(new Spring(p2, p6, restLength));
			mPhysicsWorld.AddConstraint(new Spring(p3, p7, restLength));
			mPhysicsWorld.AddConstraint(new Spring(p4, p8, restLength));

			mPhysicsWorld.AddConstraint(new Spring(p1, p7, restLength));
			mPhysicsWorld.AddConstraint(new Spring(p3, p5, restLength));
			mPhysicsWorld.AddConstraint(new Spring(p2, p8, restLength));
			mPhysicsWorld.AddConstraint(new Spring(p4, p6, restLength));
		}
	}

	if (ImGui::Button("Ball and chains!"))
	{
		const float restLength = 2.0f;
		mPhysicsWorld.Clear(true);
		for (int i = 0; i < 1; ++i)
		{
			auto p1 = new Particle();
			auto p2 = new Particle();
			auto p3 = new Particle();
			auto p4 = new Particle();
			auto p5 = new Particle();

			p1->SetPosition({ -0.5f, 5.0f, 0.0f });
			p1->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p1->radius = 0.1f;
			p1->bounce = 0.3f;

			p2->SetPosition({ 0.5f, 5.0f, 0.0f });
			p2->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p2->radius = 0.1f;
			p2->bounce = 0.3f;

			p3->SetPosition({ 1.0f, 5.0f, 0.0f });
			p3->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p3->radius = 0.1f;
			p3->bounce = 0.3f;

			p4->SetPosition({ 0.5f, 5.0f, 1.0f });
			p4->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p4->radius = 0.1f;
			p4->bounce = 0.3f;

			p5->SetPosition({ 0.0f, 6.0f, 0.0f });
			p5->SetVelocity({ RandomFloat(-0.05f, 0.05f), RandomFloat(0.1f, 0.4f), RandomFloat(-0.05f, 0.05f) });
			p5->radius = 1.0f;
			p5->bounce = 0.3f;

			mPhysicsWorld.AddParticle(p1);
			mPhysicsWorld.AddParticle(p2);
			mPhysicsWorld.AddParticle(p3);
			mPhysicsWorld.AddParticle(p4);
			mPhysicsWorld.AddParticle(p5);

			mPhysicsWorld.AddConstraint(new Fixed(p1, p2->position));
			mPhysicsWorld.AddConstraint(new Spring(p1, p2, restLength));
			mPhysicsWorld.AddConstraint(new Spring(p2, p3, restLength));
			mPhysicsWorld.AddConstraint(new Spring(p3, p4, restLength));
			mPhysicsWorld.AddConstraint(new Spring(p4, p5, restLength));
		}
	}
	if (ImGui::Button("Cloth!"))
	{
		std::vector<Omega::Physics::Particle*> aux;
		aux.clear();
		mPhysicsWorld.Clear(true);
		float size = mClothSize;
		const float offsetX = size * 0.5f;
		const float offsetY = size * 0.5f + 10.f;
		for (float y = 0.f; y < size; y += 1.0f)
		{
			for (float x = 0.f; x < size; x += 1.0f)
			{
				auto p1 = new Particle();
				p1->SetPosition({ -offsetX + x, offsetY - y , 0.0f });
				p1->radius = 0.1f;
				p1->SetVelocity(RandomFloat(0.01f, 0.1f));
				mPhysicsWorld.AddParticle(p1);
				aux.push_back(p1);
			}
		}

		for (float y = 0.f; y < size; y += 1.0f)
		{
			for (float x = 0.f; x < size; x += 1.0f)
			{
				if ((y == 0.f) && (x == size - 1.f || x == 0.f))
				{
					mPhysicsWorld.AddConstraint(new Fixed(aux[y * size + x]));
				}
				if (x + 1.f < size)
				{
					mPhysicsWorld.AddConstraint(new Spring(aux[static_cast<size_t>(y * size + x)], aux[static_cast<size_t>(y * size + x + 1.f)]));
				}

				if (y + 1.f < size)
				{
					mPhysicsWorld.AddConstraint(new Spring(aux[static_cast<size_t>(y * size + x)], aux[static_cast<size_t>((y + 1.f) * size + x)]));
				}
			}
		}

	}

	ImGui::End();
}