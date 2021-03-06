#include "GameState.h"
#include <ImGui/Inc/imgui.h>

using namespace Omega::Graphics;
using namespace Omega::Input;
using namespace Omega::Math;

void GameState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Black);

	mCamera.SetPosition({ 0.0f, 0.0f, -50.0f });
	mCamera.SetDirection({ 0.0f, 0.0f, 1.0f });

	mMesh = MeshBuilder::CreateSpherePN(10);
	mMeshBuffer.Initialize(mMesh);

	mTransformBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();

	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f ,1.0f });
	mDirectionalLight.ambient = { 0.3f };
	mDirectionalLight.diffuse = { 0.7f };
	mDirectionalLight.specular = { 0.5f };

	mMaterial.ambient = { 1.0f };
	mMaterial.diffuse = { 1.0f };
	mMaterial.specular = { 1.0f };
	mMaterial.power = { 1.0f };

	mGouraudShadingVertexShader.Initialize("../../Assets/Shaders/DoGouraudShading.fx", VertexPN::Format);
	mGouraudShadingPixelShader.Initialize("../../Assets/Shaders/DoGouraudShading.fx");

	mPhongShadingVertexShader.Initialize("../../Assets/Shaders/DoPhongShading.fx", VertexPN::Format);
	mPhongShadingPixelShader.Initialize("../../Assets/Shaders/DoPhongShading.fx");
}

void GameState::Terminate()
{
	mPhongShadingPixelShader.Terminate();
	mPhongShadingVertexShader.Terminate();
	mGouraudShadingPixelShader.Terminate();
	mGouraudShadingVertexShader.Terminate();
	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();
	mTransformBuffer.Terminate();
	mMeshBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{
	const float kMoveSpeed = 100.5f;
	const float kTurnSpeed = 0.5f;

	auto inputSystem = InputSystem::Get();
	if (inputSystem->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(kMoveSpeed*deltaTime);
	}

	if (inputSystem->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-kMoveSpeed * deltaTime);
	}

	if (inputSystem->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(-kMoveSpeed * deltaTime);
	}

	if (inputSystem->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(kMoveSpeed * deltaTime);
	}
}

void GameState::Render()
{
	auto maTranslation = Matrix4::Translation({ -11.0f , 0.0f, 0.0f });

	auto matRotation = Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y);
	auto matWorld = matRotation * maTranslation;
	auto matView = mCamera.GetViewMatrix();
	auto matProj = mCamera.GetPerspectiveMatrix();

	TransformData transformData;
	transformData.viewPosition = mCamera.GetPosition();

	mTransformBuffer.BindVS(0);

	mLightBuffer.Update(mDirectionalLight);
	mLightBuffer.BindVS(1);
	mLightBuffer.BindPS(1);

	mMaterialBuffer.Update(mMaterial);
	mMaterialBuffer.BindVS(2);
	mMaterialBuffer.BindPS(2);

	//---------------- first transformation -------------------
	//Left Sphere -> Gouraud Shading
	{
		transformData.world = Transpose(matWorld);
		transformData.wvp = Transpose(matWorld * matView * matProj);
		
		mTransformBuffer.Update(transformData);

		mGouraudShadingVertexShader.Bind();
		mGouraudShadingPixelShader.Bind();

		mMeshBuffer.Draw();
	}

	//---------------- second transformation -------------------
	//Right Sphere -> Phong Shading
	{
		maTranslation = Matrix4::Translation({ 11.0f , 0.0f, 0.0f });
		matRotation = Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y);
		matWorld = matRotation * maTranslation;
		transformData.world = Transpose(matWorld);
		transformData.wvp = Transpose(matWorld * matView * matProj);

		mTransformBuffer.Update(transformData);

		mPhongShadingVertexShader.Bind();
		mPhongShadingPixelShader.Bind();

		mMeshBuffer.Draw();
	}	

	SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
	ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool directionChanged = false;
		directionChanged |= ImGui::DragFloat("Direction X##Light", &mDirectionalLight.direction.x, 0.01f, -1.0f, 1.0f);
		directionChanged |= ImGui::DragFloat("Direction Y##Light", &mDirectionalLight.direction.y, 0.01f, -1.0f, 1.0f);
		directionChanged |= ImGui::DragFloat("Direction Z##Light", &mDirectionalLight.direction.z, 0.01f, -1.0f, 1.0f);

		if (directionChanged)
		{
			mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
		}

		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.x);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.x);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.x);
	}

	if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit4("Ambient##Material", &mMaterial.ambient.x);
		ImGui::ColorEdit4("Diffuse##Material", &mMaterial.diffuse.x);
		ImGui::ColorEdit4("Specular##Material", &mMaterial.specular.x);
		ImGui::DragFloat("Power##Material", &mMaterial.power, 1.0f, 1.0f, 100.0f);
	}

	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Rotation##Transform", &mRotation.x, 0.01f);
	}

	ImGui::End();
}