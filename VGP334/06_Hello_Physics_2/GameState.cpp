#include "GameState.h"

#include <ImGui/Inc/imgui.h>


using namespace Omega::Graphics;
using namespace Omega::Math;
using namespace Omega::Core;

void GameState::Initialize()
{
	mCameraService.Initialize();
	Camera& camera = mCameraService.GetActiveCamera();

	camera.SetNearPlane(0.1f);
	camera.SetFarPlane(300.0f);
	camera.SetPosition({ 0.0f, 1.0f, -5.0f });
	camera.SetLookAt({ 0.0f, 1.0f, 0.0f });

	mRenderManager = RendererManager::Get();
	// load sprite 
	if (mRenderManager)
	{
		std::string name = "Sprites/carrier_0" + std::to_string(1u) + ".png";
		mTexturesIds.at(0) = mRenderManager->get().LoadTexture(name);
	}
}

void GameState::Terminate()
{
	mCameraService.Terminate();
}

void GameState::Update(float deltaTime)
{
	mRenderManager->get().DrawScreenText(L"Hello Update", Vector2{100.f, 150.f}, 25.f, Colors::Azure);
	mRenderManager->get().DrawScreenText(L"Hello Update 2 ", Vector2{100.f, 170.f}, 25.f, Colors::Chocolate);
	mRenderManager->get().DrawScreenText({ L"Hello Update 3 - with args", 25.f, 100.f, 190.f, Colors::Gold });
}

void GameState::Render()
{	
	mRenderManager->get().DrawScreenText(L"Hello RENDER", Vector2{ 100.f, 120.f }, 25.f, Colors::Red);
	mRenderManager->get().DrawSprite({ mTexturesIds.at(0), Vector2{ 600.f, 120.f }, 0.0f });


	SimpleDraw::AddGroundPlane(20.f);
	const Camera& camera = mCameraService.GetActiveCamera();
	SimpleDraw::Render(camera);
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Delta Time (%f)", TimeUtil::GetDeltaTime());
	ImGui::Text("Time (%f)", TimeUtil::GetTime());

	ImGui::End();
}