#include "GameState.h"
#include <ImGui/Inc/imgui.h>

using namespace Omega::Graphics;
using namespace Omega::Input;
using namespace Omega::Math;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 0.0f, -5.0f });
	mCamera.SetDirection({ 0.0f, 0.0f, 1.0f });
	
	//mMesh = MeshBuilder::CreateSpherePX();
	//mMeshBuffer.Initialize(mMesh);

	mTransformBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();

	mVertexShader.Initialize("../../Assets/Shaders/DoPhongLighting.fx", VertexPN::Format);
	mPixelShader.Initialize("../../Assets/Shaders/DoPhongLighting.fx");
}

void GameState::Terminate()
{
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();
	mTransformBuffer.Terminate();
	mMeshBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{
}

void GameState::Render()
{
	auto context = GraphicsSystem::Get()->GetContext();
	
	auto matRotation = Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y);
	auto matView = mCamera.GetViewMatrix();
	auto matProj = mCamera.GetPerspectiveMatrix();
}

void GameState::DebugUI()
{
	ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::End();
}