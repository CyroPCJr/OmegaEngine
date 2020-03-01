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

	// set the tank
	std::filesystem::path modelsAssets = "../../Assets/Models/Tank/";
	ObjLoader::Load(modelsAssets / "tank.obj", 0.001f, mTankMesh);
	mTankMeshBuffer.Initialize(mTankMesh);

	// Set a ground plane
	mGroundPlane = MeshBuilder::CreatePlane(100.0f);
	mGroundPlaneBuffer.Initialize(mGroundPlane);

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

	std::filesystem::path texturesAssets = "../../Assets/Textures/";
	mGroundPlaneMap.Initialize(texturesAssets / "grass.jpg");

	mSettingsDataBuffer.Initialize();

	auto graphicsSystem = GraphicsSystem::Get();
	mRenderTarget.Initialize(graphicsSystem->GetBackBufferWidth(),
		graphicsSystem->GetBackBufferHeight(),
		RenderTarget::Format::RGBA_U8);

	// Create a Quad
	mScreenQuad = MeshBuilder::CreateNDCQuad();
	mScreenQuadBuffer.Initialize(mScreenQuad);

	// VS and PS
	std::filesystem::path shadersFolder = "../../Assets/Shaders/";
	mVertexShader.Initialize(shadersFolder / "Standard.fx", Vertex::Format);
	mPixelShader.Initialize(shadersFolder / "Standard.fx");

	mPostProcessingVertexShader.Initialize(shadersFolder / "PostProcessing.fx", VertexPX::Format);
	mPostProcessingPixelShader.Initialize(shadersFolder / "PostProcessing.fx", "PSNoProcessing");

	// DepthMap for cast shadow
	const uint32_t depthMapSize = 1024;
	mDepthMapRenderTarget.Initialize(depthMapSize, depthMapSize, RenderTarget::Format::RGBA_U32);
	mDepthMapVertexShader.Initialize(shadersFolder / "DepthMap.fx", Vertex::Format);
	mDepthMaPixelShader.Initialize(shadersFolder / "DepthMap.fx");
	mDepthMapConstantBuffer.Initialize();
	mShadowConstantBuffer.Initialize();
}

void GameState::Terminate()
{
	mShadowConstantBuffer.Terminate();
	mDepthMapRenderTarget.Terminate();
	mDepthMapVertexShader.Terminate();
	mDepthMaPixelShader.Terminate();
	mDepthMapConstantBuffer.Terminate();
	mVertexShader.Terminate();
	mPixelShader.Terminate();
	mPostProcessingPixelShader.Terminate();
	mPostProcessingVertexShader.Terminate();
	mGroundPlaneMap.Terminate();
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
		mDefaultCamera.Walk(kMoveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::S))
	{
		mDefaultCamera.Walk(-kMoveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::D))
	{
		mDefaultCamera.Strafe(kMoveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::A))
	{
		mDefaultCamera.Strafe(-kMoveSpeed * deltaTime);
	}
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mDefaultCamera.Yaw(inputSystem->GetMouseMoveX() * kTurnSpeed * deltaTime);
		mDefaultCamera.Pitch(inputSystem->GetMouseMoveY() * kTurnSpeed * deltaTime);
	}

	if (inputSystem->IsKeyDown(KeyCode::UP))
	{
		mTankRotation.x += deltaTime;
	}
	if (inputSystem->IsKeyDown(KeyCode::DOWN))
	{
		mTankRotation.x -= deltaTime;
	}
	if (inputSystem->IsKeyDown(KeyCode::LEFT))
	{
		mTankRotation.y += deltaTime;

	}
	if (inputSystem->IsKeyDown(KeyCode::RIGHT))
	{
		mTankRotation.y -= deltaTime;
	}

	mLightCamera.SetDirection(mDirectionalLight.direction);
	mLightCamera.SetPosition(mTankPosition - mLightCamera.GetDirection()* 50.0f);
}

void GameState::Render()
{
	mDepthMapRenderTarget.BeginRender();
	DrawDepthMap();
	mDepthMapRenderTarget.EndRender();

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

		ImGui::Image(mDepthMapRenderTarget.GetShaderResourceView(),
			{ 150.0f, 150.0f },
			{ 0.0f,0.0f },
			{ 1.0f, 1.0f },
			{ 1.0f , 1.0f ,1.0f ,1.0f },
			{ 1.0f , 1.0f ,1.0f ,1.0f });

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
		static bool useShadow = mSettingsData.useShadow == 1;
		ImGui::SliderFloat("Displacement", &mSettingsData.bumpMapWeight, 0.0f, 100.0f);
		if (ImGui::Checkbox("Specular", &specularMap))
		{
			mSettingsData.specularWeight = specularMap ? 1.0f : 0.0f;
		}

		if (ImGui::Checkbox("Normal", &normalMap))
		{
			mSettingsData.normalMapWeight = normalMap ? 1.0f : 0.0f;
		}

		if (ImGui::Checkbox("Use Shadow", &useShadow))
		{
			mSettingsData.useShadow = useShadow ? 1.0f : 0.0f;
		}
	}
	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("X##Transform", &mTankPosition.x, 0.01f);
		ImGui::DragFloat("Y##Transform", &mTankPosition.y, 0.01f);
	}

	ImGui::End();
}

void GameState::DrawDepthMap()
{
	mDepthMapVertexShader.Bind();
	mDepthMaPixelShader.Bind();
	auto matViewLight = mActiveCamera->GetViewMatrix();
	auto matProjLight = mActiveCamera->GetPerspectiveMatrix();

	auto maTranslation = Matrix4::Translation(mTankPosition);
	auto matRotation = Matrix4::RotationX(mTankRotation.x) * Matrix4::RotationY(mTankRotation.y);;
	auto matWorld = matRotation * maTranslation;

	auto wvp = Transpose(matWorld * matViewLight * matProjLight);
	mDepthMapConstantBuffer.Update(wvp);
	mDepthMapConstantBuffer.BindVS(0);

	mTankMeshBuffer.Draw();

}

void GameState::DrawScene()
{
	auto matView = mActiveCamera->GetViewMatrix();
	auto matProj = mActiveCamera->GetPerspectiveMatrix();

	auto matViewLight = mLightCamera.GetViewMatrix();
	auto matProjLight = mLightCamera.GetPerspectiveMatrix();

	mLightBuffer.Update(mDirectionalLight);
	mLightBuffer.BindVS(1);
	mLightBuffer.BindPS(1);

	mMaterialBuffer.Update(mMaterial);
	mMaterialBuffer.BindVS(2);
	mMaterialBuffer.BindPS(2);

	mSettingsDataBuffer.Update(mSettingsData);
	mSettingsDataBuffer.BindPS(3);
	mSettingsDataBuffer.BindVS(3);

	mSamplers.BindPS();
	mSamplers.BindVS();
	mDifuseTexture.BindPS();
	mSpecularTexture.BindPS(1);
	mSpecularTexture.BindVS(1);
	mNormalMap.BindPS(3);
	mDepthMapRenderTarget.BindPS(5);

	auto maTranslation = Matrix4::Translation(mTankPosition);
	auto matRotation = Matrix4::RotationX(mTankRotation.x) * Matrix4::RotationY(mTankRotation.y);;
	auto matWorld = matRotation * maTranslation;

	TransformData transformData;
	transformData.viewPosition = mDefaultCamera.GetPosition();
	transformData.world = Transpose(matWorld);
	transformData.wvp = Transpose(matWorld * matView * matProj);

	mTransformBuffer.Update(transformData);
	mTransformBuffer.BindVS();

	mVertexShader.Bind();
	mPixelShader.Bind();

	auto wvpLight = Transpose(matWorld * matViewLight * matProjLight);
	mShadowConstantBuffer.Update(wvpLight);
	mShadowConstantBuffer.BindPS(4);

	mTankMeshBuffer.Draw();

	matWorld = Matrix4::Identity;
	transformData.world = Transpose(matWorld);
	transformData.wvp = Transpose(matWorld * matView * matProj);
	mTransformBuffer.Update(transformData);

	wvpLight = Transpose(matWorld * matViewLight * matProjLight);
	mShadowConstantBuffer.Update(wvpLight);
	mShadowConstantBuffer.BindVS(4);

	mGroundPlaneMap.BindPS(0);
	mSettingsData.bumpMapWeight = 0.0f;
	mSettingsData.normalMapWeight = 0.0f;
	mSettingsData.specularWeight = 0.0f;
	mSettingsData.aoMapWeight = 0.0f;
	mSettingsData.useShadow = 1;
	mSettingsDataBuffer.Update(mSettingsData);

	mGroundPlaneBuffer.Draw();

	SimpleDraw::Render(*mActiveCamera);
}

void GameState::PostProcess()
{
	mPostProcessingVertexShader.Bind();
	mPostProcessingPixelShader.Bind();
	mSamplers.BindPS();
	mScreenQuadBuffer.Draw();
}
