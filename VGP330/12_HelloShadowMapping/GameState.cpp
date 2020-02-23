#include "GameState.h"
#include <ImGui/Inc/imgui.h>

using namespace Omega::Graphics;
using namespace Omega::Input;
using namespace Omega::Math;

void GameState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Black);

	mTankPosition = { 0.0f, 3.5f,0.0f };

	mDefaultCamera.SetNearPlane(0.001f);
	mDefaultCamera.SetPosition({ 0.0f, 5.0f, -20.0f });
	mDefaultCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mLightCamera.SetDirection(Normalize({ 1.0f, -1.0f, 0.0f }));

	mLightCamera.SetNearPlane(1.0f);
	mLightCamera.SetFarPlane(200.0f);
	mLightCamera.SetFov(1.0f);
	mLightCamera.SetAspectRatio(1.0f);

	mActiveCamera = &mDefaultCamera;

	std::filesystem::path modelsAssets = "../../Assets/Models/Tank/";
	ObjLoader::Load(modelsAssets / "tank.obj", 0.01f, mTankMesh);
	mTankMeshBuffer.Initialize(mTankMesh);

	mTransformBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();

	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f ,1.0f });
	mDirectionalLight.ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	mDirectionalLight.diffuse = { 0.75f, 0.75f,0.75f,1.0f };
	mDirectionalLight.specular = { 0.5f, 0.5f, 0.5f, 1.0f };

	mMaterial.ambient = { 1.0f };
	mMaterial.diffuse = { 1.0f };
	mMaterial.specular = { 1.0f };
	mMaterial.power = 10.0f;

	mSettingsData.bumpMapWeight = 0.2f;

	mSamplers.Initialize(Sampler::Filter::Point, Sampler::AddressMode::Wrap);

	mDifuseTexture.Initialize(modelsAssets / "tank_diffuse.jpg");
	mSpecularTexture.Initialize(modelsAssets / "tank_specular.jpg");
	mNormalMap.Initialize(modelsAssets / "tank_normal.jpg");

	mSettingsDataBuffer.Initialize();

	auto graphicsSystem = GraphicsSystem::Get();
	mRenderTarget.Initialize(graphicsSystem->GetBackBufferWidth(),
		graphicsSystem->GetBackBufferHeight(),
		RenderTarget::Format::RGBA_U8);

	// Createa a Quad
	mScreenQuad = MeshBuilder::CreateNDCQuad();
	mScreenQuadBuffer.Initialize(mScreenQuad);

	// VS and PS
	std::filesystem::path shadersFolder = "../../Assets/Shaders/";
	mVertexShader.Initialize(shadersFolder / "Standard.fx", Vertex::Format);
	mPixelShader.Initialize(shadersFolder / "Standard.fx");

	mPostProcessingVertexShader.Initialize(shadersFolder / "PostProcessing.fx", VertexPX::Format);
	mPostProcessingPixelShader.Initialize(shadersFolder / "PostProcessing.fx", "PSNoProcessing");
}

void GameState::Terminate()
{
	mVertexShader.Terminate();
	mPixelShader.Terminate();
	mPostProcessingPixelShader.Terminate();
	mPostProcessingVertexShader.Terminate();
	mScreenQuadBuffer.Terminate();
	mRenderTarget.Terminate();
	mSettingsDataBuffer.Terminate();
	mNormalMap.Terminate();

	mSpecularTexture.Terminate();
	mDifuseTexture.Terminate();
	mSamplers.Terminate();

	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();
	mTransformBuffer.Terminate();
	mTankMeshBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{
	const float kMoveSpeed = 100.5f;
	const float kTurnSpeed = 0.5f;

	auto inputSystem = InputSystem::Get();
	if (inputSystem->IsKeyDown(KeyCode::W))
	{
		mDefaultCamera.Walk(kMoveSpeed*deltaTime);
	}

	if (inputSystem->IsKeyDown(KeyCode::S))
	{
		mDefaultCamera.Walk(-kMoveSpeed * deltaTime);
	}

	if (inputSystem->IsKeyDown(KeyCode::D))
	{
		mDefaultCamera.Strafe(-kMoveSpeed * deltaTime);
	}

	if (inputSystem->IsKeyDown(KeyCode::A))
	{
		mDefaultCamera.Strafe(kMoveSpeed * deltaTime);
	}

	mLightCamera.SetPosition(mTankPosition - mLightCamera.GetDirection()* 100.0f);
}

void GameState::Render()
{
	mRenderTarget.BeginRender();
	DrawScene();
	mRenderTarget.EndRender();

	mRenderTarget.BindPS(0);
	PostProcess();
	mRenderTarget.UnBindPS(0);
}

void GameState::DebugUI()
{
	ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool lightCamera = mActiveCamera == &mLightCamera;
		if (ImGui::Checkbox("Use Light Camera", &lightCamera))
		{
			mActiveCamera = lightCamera ? &mLightCamera : &mDefaultCamera;
		}
	}

	ImGui::Separator();
	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool directionChanged = false;
		directionChanged |= ImGui::DragFloat("Direction X##Light", &mDirectionalLight.direction.x, 0.01f);
		directionChanged |= ImGui::DragFloat("Direction Y##Light", &mDirectionalLight.direction.y, 0.01f);
		directionChanged |= ImGui::DragFloat("Direction Z##Light", &mDirectionalLight.direction.z, 0.01f);

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

	if (ImGui::CollapsingHeader("Settings", ImGuiTreeNodeFlags_DefaultOpen))
	{
		static bool specularMap = true;
		static bool normalMap = true;
		ImGui::SliderFloat("Displacement", &mSettingsData.bumpMapWeight, 0.0f, 100.0f);
		if (ImGui::Checkbox("Specular", &specularMap))
		{
			mSettingsData.specularWeight = specularMap ? 1.0f : 0.0f;
		}

		if (ImGui::Checkbox("Normal", &normalMap))
		{
			mSettingsData.normalMapWeight = normalMap ? 1.0f : 0.0f;
		}
	}
	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Tank Position X##Transform", &mTankPosition.y, 0.01f);
		ImGui::DragFloat("Tank Position Y##Transform", &mTankPosition.x, 0.01f);
	}

	ImGui::End();
}

void GameState::DrawScene()
{
	auto maTranslation = Matrix4::Translation({ 0.0f , 3.5f, 0.0f });

	auto matRotation = Matrix4::RotationX(mTankRotation.x);
	auto matWorld = matRotation * maTranslation;
	auto matView = mDefaultCamera.GetViewMatrix();
	auto matProj = mDefaultCamera.GetPerspectiveMatrix();

	TransformData transformData;
	transformData.viewPosition = mDefaultCamera.GetPosition();
	transformData.world = Transpose(matWorld);
	transformData.wvp = Transpose(matWorld * matView * matProj);

	mTransformBuffer.Update(transformData);
	mTransformBuffer.BindVS();

	mLightBuffer.Update(mDirectionalLight);
	mLightBuffer.BindVS(1);
	mLightBuffer.BindPS(1);

	mMaterialBuffer.Update(mMaterial);
	mMaterialBuffer.BindVS(2);
	mMaterialBuffer.BindPS(2);

	mDifuseTexture.BindPS();
	mDifuseTexture.BindVS();

	mSpecularTexture.BindPS(1);
	mSpecularTexture.BindVS(1);

	mNormalMap.BindPS(3);

	mSamplers.BindPS();
	mSamplers.BindVS();

	mSettingsDataBuffer.Update(mSettingsData);
	mSettingsDataBuffer.BindPS(3);
	mSettingsDataBuffer.BindVS(3);

	mVertexShader.Bind();
	mPixelShader.Bind();

	mTankMeshBuffer.Draw();

	SimpleDraw::Render(*mActiveCamera);
}

void GameState::PostProcess()
{
	mPostProcessingVertexShader.Bind();
	mPostProcessingPixelShader.Bind();
	mSamplers.BindPS();
	mScreenQuadBuffer.Draw();
}
