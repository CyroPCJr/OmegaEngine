#include "GameState.h"

#include <ImGui/Inc/imgui.h>

using namespace Omega::Graphics;
using namespace Omega::Input;
using namespace Omega::Math;
using namespace Omega::Physics;

void GameState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::LightSlateGray);

	// Camera Settings
	mCamera.SetNearPlane(0.1f);
	mCamera.SetFarPlane(300.0f);
	mCamera.SetPosition({ 0.0f, 10.0f, -30.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	// Physics World settings
	PhysicsWorld::Settings settings;
	settings.gravity = { 0.0f, -9.8f, 0.0f };
	settings.timeStep = 1.0f / 60.0f;
	settings.drag = 0.3f;
	settings.iterations = 1;
	mPhysicsWorld.Initilize(settings);
	mPhysicsWorld.AddStaticPlane({ Vector3::YAxis, 0.0f });
	mPhysicsWorld.AddStaticOBB({ {5.0f, 4.0f, 0.0f}, { 4.0f, 0.5f,5.0f }, Quaternion::RotationAxis(Vector3::ZAxis, 10.0f * Constants::DegToRad) });
	mPhysicsWorld.AddStaticOBB({ { -5.0f, 8.f, 0.0f}, { 4.0f, 0.2f,5.0f }, Quaternion::RotationAxis(Vector3::ZAxis, -10.0f * Constants::DegToRad) });

	// Cloth settings
	Omega::Cloth::Settings clothSettings;
	clothSettings.path = "../../Assets/Textures/Brazil_flag.png";
	clothSettings.width = 20;
	clothSettings.height = 15;
	clothSettings.startPosition = { 10.0f, 20.0f,0.0f };
	mClothBrazilFlag.Initialize(clothSettings);
	clothSettings.path = "../../Assets/Textures/Canada_flag.jpg";
	clothSettings.startPosition = { -10.0f, 20.0f,0.0f };
	mClothCanadaFlag.Initialize(clothSettings);

	mVecFrames.reserve(mMaxFrameSize);
	InitializeParticles(1000); //Just for experiment
}

void GameState::Terminate()
{
	mClothCanadaFlag.Terminate();
	mClothBrazilFlag.Terminate();
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
	mClothBrazilFlag.Update(deltaTime);
	mClothCanadaFlag.Update(deltaTime);
}

void GameState::Render()
{
	mClothBrazilFlag.Render(mCamera);
	mClothCanadaFlag.Render(mCamera);
	mPhysicsWorld.DebugDraw();

	SimpleDraw::AddGroundPlane(50.0f);

	SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
	ImGui::Begin("Physics", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	float fps = ImGui::GetIO().Framerate; //Get frames
	const size_t frameSize = mVecFrames.size();
	if (frameSize > mMaxFrameSize) //Max seconds to show
	{
		for (size_t i = 1; i < frameSize; ++i)
		{
			mVecFrames[i - 1] = mVecFrames[i];
		}
		mVecFrames[frameSize - 1] = fps;
	}
	else
	{
		mVecFrames.push_back(fps);
	}
	ImGui::PlotLines("", &mVecFrames[0], static_cast<int>(frameSize), 0, NULL, 0.0f, 300.0f, ImVec2(250, 30));

	if (ImGui::Button("Particles!"))
	{
		UseRawParticles(1500);
	}

	if (ImGui::Button("Stick!"))
	{
		UseStickParticles(50);
	}

	if (ImGui::Button("Tetrahedron!"))
	{
		UseTetrahedronParticles(20);
	}

	if (ImGui::Button("Cube!"))
	{
		UseCubeParticles(20);
	}

	if (ImGui::Button("Ball and chains!"))
	{
		UseBallAndChains(1);
	}

	static int e = 0;
	ImGui::Separator();
	ImGui::Text("Cloth!");
	ImGui::RadioButton("Particles", &e, 0); ImGui::SameLine();
	ImGui::RadioButton("Texture", &e, 1);
	if (ImGui::Button("Show!"))
	{
		mPhysicsWorld.Clear(true);
		mClothBrazilFlag.SetShowCloth(true);
		mClothCanadaFlag.SetShowCloth(true);
		mClothBrazilFlag.SetShowTextureCloth(e);
		mClothCanadaFlag.SetShowTextureCloth(e);
	}
	ImGui::Separator();

	ImGui::End();
}

void GameState::InitializeParticles(int maxParticles)
{
	mPhysicsWorld.Clear(true);
	for (int i = 0; i != maxParticles; ++i)
	{
		auto p = std::make_unique<Particle>();
		mPhysicsWorld.AddParticle(p);
	}
}

void GameState::UseRawParticles(int count)
{
	mClothBrazilFlag.SetShowCloth(false);
	mClothCanadaFlag.SetShowCloth(false);
	//mPhysicsWorld.Clear(true);
	const auto& particlesList = mPhysicsWorld.GetParticles();
	const size_t particleCount = particlesList.size();
	for (int i = 0; i != count; ++i)
	{
		//Just for backup
		/*auto p = new Particle();
		p->SetPosition({ 0.0f, 5.0f, 0.0f });

		p->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f) , Random::RandomFloat(-0.05f, 0.05f) });
		p->radius = 0.1f;
		p->bounce = 0.3f;*/

		/*auto p = std::make_unique<Particle>();
		p->SetPosition({ 0.0f, 5.0f, 0.0f });

		p->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f) , Random::RandomFloat(-0.05f, 0.05f) });
		p->radius = 0.1f;
		p->bounce = 0.3f;
		mPhysicsWorld.AddParticle(p);*/
		auto& particle = particlesList[i % particleCount];
		particle->SetPosition({ 0.0f, 5.0f, 0.0f });

		particle->SetVelocity(Random::RandomVector3({ -0.05f, 0.1f, -0.05f }, { 0.05f, 0.4f, 0.05f }));
		particle->radius = 0.1f;
		particle->bounce = 0.3f;

	}
}

void GameState::UseStickParticles(int count)
{
	mClothBrazilFlag.SetShowCloth(false);
	mClothCanadaFlag.SetShowCloth(false);
	mPhysicsWorld.Clear(true);
	for (int i = 0; i < count; ++i)
	{
		auto p1 = std::make_unique<Particle>();
		auto p2 = std::make_unique<Particle>();

		/*auto p1 = new Particle();
		auto p2 = new Particle();*/

		p1->SetPosition({ 0.5f, 5.0f, 0.0f });
		p1->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p1->radius = 0.1f;
		p1->bounce = 0.3f;
		p2->SetPosition({ -0.5f, 5.0f, 0.0f });
		p2->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p2->radius = 0.1f;
		p2->bounce = 0.3f;
		std::unique_ptr<Constraint> spring = std::make_unique<Spring>(p1.get(), p2.get());
		mPhysicsWorld.AddConstraint(spring);
		mPhysicsWorld.AddParticle(p1);
		mPhysicsWorld.AddParticle(p2);
	}
}

void GameState::UseTetrahedronParticles(int count)
{
	mClothBrazilFlag.SetShowCloth(false);
	mClothCanadaFlag.SetShowCloth(false);
	mPhysicsWorld.Clear(true);
	for (int i = 0; i < count; ++i)
	{
		/*auto p1 = new Particle();
		auto p2 = new Particle();
		auto p3 = new Particle();
		auto p4 = new Particle();*/
		auto p1 = std::make_unique<Particle>();
		auto p2 = std::make_unique<Particle>();
		auto p3 = std::make_unique<Particle>();
		auto p4 = std::make_unique<Particle>();

		p1->SetPosition({ -0.5f, 5.0f, 0.0f });
		p1->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p1->radius = 0.1f;
		p1->bounce = 0.3f;

		p2->SetPosition({ 0.0f, 5.0f, 1.0f });
		p2->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p2->radius = 0.1f;
		p2->bounce = 0.3f;

		p3->SetPosition({ 0.5f, 5.0f, 0.0f });
		p3->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f),Random::RandomFloat(-0.05f, 0.05f) });
		p3->radius = 0.1f;
		p3->bounce = 0.3f;

		p4->SetPosition({ 0.0f, 6.0f, 0.0f });
		p4->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p4->radius = 0.1f;
		p4->bounce = 0.3f;

		std::unique_ptr<Constraint> spring1 = std::make_unique<Spring>(p1.get(), p2.get(), 1.0f);
		std::unique_ptr<Constraint> spring2 = std::make_unique<Spring>(p2.get(), p3.get(), 1.0f);
		std::unique_ptr<Constraint> spring3 = std::make_unique<Spring>(p3.get(), p1.get(), 1.0f);

		std::unique_ptr<Constraint> spring4 = std::make_unique<Spring>(p1.get(), p4.get(), 1.0f);
		std::unique_ptr<Constraint> spring5 = std::make_unique<Spring>(p2.get(), p4.get(), 1.0f);
		std::unique_ptr<Constraint> spring6 = std::make_unique<Spring>(p3.get(), p4.get(), 1.0f);

		mPhysicsWorld.AddConstraint(spring1);
		mPhysicsWorld.AddConstraint(spring2);
		mPhysicsWorld.AddConstraint(spring3);

		mPhysicsWorld.AddConstraint(spring4);
		mPhysicsWorld.AddConstraint(spring5);
		mPhysicsWorld.AddConstraint(spring6);

		mPhysicsWorld.AddParticle(p1);
		mPhysicsWorld.AddParticle(p2);
		mPhysicsWorld.AddParticle(p3);
		mPhysicsWorld.AddParticle(p4);
	}

}

void GameState::UseCubeParticles(int count)
{
	mClothBrazilFlag.SetShowCloth(false);
	mClothCanadaFlag.SetShowCloth(false);
	mPhysicsWorld.Clear(true);
	const float pos = 0.5f;
	for (int i = 0; i < count; ++i)
	{
		auto p1 = std::make_unique<Particle>();
		auto p2 = std::make_unique<Particle>();
		auto p3 = std::make_unique<Particle>();
		auto p4 = std::make_unique<Particle>();
		auto p5 = std::make_unique<Particle>();
		auto p6 = std::make_unique<Particle>();
		auto p7 = std::make_unique<Particle>();
		auto p8 = std::make_unique<Particle>();

		p1->SetPosition({ -pos + i, pos + 10.0f, pos + i });
		p1->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p1->radius = 0.1f;
		p1->bounce = 0.3f;

		p2->SetPosition({ pos + i, pos + 10.0f, pos + i });
		p2->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p2->radius = 0.1f;
		p2->bounce = 0.3f;

		p3->SetPosition({ -pos + i,pos + 10.0f , -pos + i });
		p3->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p3->radius = 0.1f;
		p3->bounce = 0.3f;

		p4->SetPosition({ pos + i, pos + 10.0f, -pos + i });
		p4->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p4->radius = 0.1f;
		p4->bounce = 0.3f;

		p5->SetPosition({ pos + i, -pos + 10.0f,-pos + i });
		p5->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p5->radius = 0.1f;
		p5->bounce = 0.3f;

		p6->SetPosition({ -pos + i, -pos + 10.0f, -pos + i });
		p6->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p6->radius = 0.1f;
		p6->bounce = 0.3f;

		p7->SetPosition({ pos + i, -pos + 10.0f, pos + i });
		p7->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p7->radius = 0.1f;
		p7->bounce = 0.3f;

		p8->SetPosition({ -pos + i,-pos + 10.0f, pos + i });
		p8->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p8->radius = 0.1f;
		p8->bounce = 0.3f;


		std::unique_ptr<Constraint> spring1 = std::make_unique<Spring>(p1.get(), p2.get());
		std::unique_ptr<Constraint> spring2 = std::make_unique<Spring>(p2.get(), p4.get());
		std::unique_ptr<Constraint> spring3 = std::make_unique<Spring>(p3.get(), p4.get());
		std::unique_ptr<Constraint> spring4 = std::make_unique<Spring>(p3.get(), p1.get());

		mPhysicsWorld.AddConstraint(spring1);
		mPhysicsWorld.AddConstraint(spring2);
		mPhysicsWorld.AddConstraint(spring3);
		mPhysicsWorld.AddConstraint(spring4);

		spring1 = std::make_unique<Spring>(p5.get(), p6.get());
		spring2 = std::make_unique<Spring>(p6.get(), p8.get());
		spring3 = std::make_unique<Spring>(p7.get(), p8.get());
		spring4 = std::make_unique<Spring>(p7.get(), p5.get());

		mPhysicsWorld.AddConstraint(spring1);
		mPhysicsWorld.AddConstraint(spring2);
		mPhysicsWorld.AddConstraint(spring3);
		mPhysicsWorld.AddConstraint(spring4);

		spring1 = std::make_unique<Spring>(p1.get(), p8.get());
		spring2 = std::make_unique<Spring>(p2.get(), p7.get());
		spring3 = std::make_unique<Spring>(p3.get(), p6.get());
		spring4 = std::make_unique<Spring>(p4.get(), p5.get());

		mPhysicsWorld.AddConstraint(spring1);
		mPhysicsWorld.AddConstraint(spring2);
		mPhysicsWorld.AddConstraint(spring3);
		mPhysicsWorld.AddConstraint(spring4);

		spring1 = std::make_unique<Spring>(p1.get(), p5.get());
		spring2 = std::make_unique<Spring>(p3.get(), p7.get());
		spring3 = std::make_unique<Spring>(p2.get(), p6.get());
		spring4 = std::make_unique<Spring>(p4.get(), p8.get());

		mPhysicsWorld.AddConstraint(spring1);
		mPhysicsWorld.AddConstraint(spring2);
		mPhysicsWorld.AddConstraint(spring3);
		mPhysicsWorld.AddConstraint(spring4);

		mPhysicsWorld.AddParticle(p1);
		mPhysicsWorld.AddParticle(p2);
		mPhysicsWorld.AddParticle(p3);
		mPhysicsWorld.AddParticle(p4);

		mPhysicsWorld.AddParticle(p5);
		mPhysicsWorld.AddParticle(p6);
		mPhysicsWorld.AddParticle(p7);
		mPhysicsWorld.AddParticle(p8);
	}
}

void GameState::UseBallAndChains(int count)
{
	mClothBrazilFlag.SetShowCloth(false);
	mClothCanadaFlag.SetShowCloth(false);
	const float restLength = 2.0f;
	mPhysicsWorld.Clear(true);
	for (int i = 0; i < count; ++i)
	{
		auto p1 = std::make_unique<Particle>();
		auto p2 = std::make_unique<Particle>();
		auto p3 = std::make_unique<Particle>();
		auto p4 = std::make_unique<Particle>();
		auto p5 = std::make_unique<Particle>();
		auto p6 = std::make_unique<Particle>();

		p1->SetPosition({ -0.5f, 15.0f, 0.0f });
		p1->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p1->radius = 0.1f;
		p1->bounce = 0.3f;

		p2->SetPosition({ 0.5f, 15.0f, 0.0f });
		p2->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p2->radius = 0.1f;
		p2->bounce = 0.3f;

		p3->SetPosition({ 1.0f, 15.0f, 0.0f });
		p3->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p3->radius = 0.1f;
		p3->bounce = 0.3f;

		p4->SetPosition({ 0.5f, 15.0f, 1.0f });
		p4->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p4->radius = 0.1f;
		p4->bounce = 0.3f;

		p5->SetPosition({ 0.0f, 15.0f, 0.0f });
		p5->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p5->radius = 0.1f;
		p5->bounce = 0.3f;

		p6->SetPosition({ 0.0f, 16.0f, 0.0f });
		p6->SetVelocity({ Random::RandomFloat(-0.05f, 0.05f), Random::RandomFloat(0.1f, 0.4f), Random::RandomFloat(-0.05f, 0.05f) });
		p6->radius = 1.0f;
		p6->bounce = 0.3f;

		std::unique_ptr<Constraint> fixed = std::make_unique<Fixed>(p1.get(), p2.get()->position);
		mPhysicsWorld.AddConstraint(fixed);

		std::unique_ptr<Constraint> spring1 = std::make_unique<Spring>(p1.get(), p2.get(), restLength);
		std::unique_ptr<Constraint> spring2 = std::make_unique<Spring>(p2.get(), p3.get(), restLength);
		std::unique_ptr<Constraint> spring3 = std::make_unique<Spring>(p3.get(), p4.get(), restLength);
		std::unique_ptr<Constraint> spring4 = std::make_unique<Spring>(p4.get(), p5.get(), restLength);
		std::unique_ptr<Constraint> spring5 = std::make_unique<Spring>(p5.get(), p6.get(), restLength);

		mPhysicsWorld.AddConstraint(spring1);
		mPhysicsWorld.AddConstraint(spring2);
		mPhysicsWorld.AddConstraint(spring3);
		mPhysicsWorld.AddConstraint(spring4);
		mPhysicsWorld.AddConstraint(spring5);

		mPhysicsWorld.AddParticle(p1);
		mPhysicsWorld.AddParticle(p2);
		mPhysicsWorld.AddParticle(p3);
		mPhysicsWorld.AddParticle(p4);
		mPhysicsWorld.AddParticle(p5);
		mPhysicsWorld.AddParticle(p6);

	}
}
