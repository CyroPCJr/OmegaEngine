#include "GameState.h"
#include <ImGui/Inc/imgui.h>

using namespace Omega::Graphics;
using namespace Omega::Input;
using namespace Omega::Math;

void GameState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Black);

	mCamera.SetNearPlane(0000.1f);
	mCamera.SetPosition({ 0.0f, 0.0f, -50.0f });
	mCamera.SetDirection({ 0.0f, 0.0f, 1.0f });

	mMesh = MeshBuilder::CreateSphere(10.0f, 64, 64);
	mMeshBuffer.Initialize(mMesh);

	mMeshMoon = MeshBuilder::CreateSphere(1.0f, 15, 15);
	mMeshBufferMoon.Initialize(mMeshMoon);

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

	std::filesystem::path EarthShader = "../../Assets/Shaders/Earth.fx";
	mEarthVertexShader.Initialize(EarthShader, "VSEarth", Vertex::Format);
	mEarthPixelShader.Initialize(EarthShader, "PSEarth");

	mCloudVertexShader.Initialize(EarthShader, "VSCloud", Vertex::Format);
	mCloudPixelShader.Initialize(EarthShader, "PSCloud");

	std::filesystem::path rootTextures = "../../Assets/Textures";
	mDifuseTexture.Initialize(rootTextures / "earth.jpg");
	mSpecularTexture.Initialize(rootTextures / "earth_spec.tif");
	mDisplacementTexture.Initialize(rootTextures / "earth_bump.jpg");
	mNormalMap.Initialize(rootTextures / "earth_normal.tif"); 
	mClouds.Initialize(rootTextures / "earth_clouds.jpg");
	mNightLights.Initialize(rootTextures / "earth_lights.jpg");

	mBlendState.Initialize(BlendState::Mode::AlphaBlending);

	mSettingsDataBuffer.Initialize();

	// SkyDome
	mSkydome.Initialize("8k_stars.jpg");

	// Moon
	mVSMoon.Initialize(EarthShader, "VSEarth", Vertex::Format);
	mPSMoon.Initialize(EarthShader, "PSEarth");
	mMoonTexture.Initialize(rootTextures / "8k_moon.jpg");
	mSettingsMoonDataBuffer.Initialize();

	auto graphicsSystem = GraphicsSystem::Get();
	mRenderTarget.Initialize(graphicsSystem->GetBackBufferWidth(),
		graphicsSystem->GetBackBufferHeight(),
		RenderTarget::Format::RGBA_U8);

	// Createa a Quad
	mScreenQuad = MeshBuilder::CreateNDCQuad();
	mScreenQuadBuffer.Initialize(mScreenQuad);

	std::filesystem::path postProcessingShader = "../../Assets/Shaders/PostProcessing.fx";
	mPostProcessingVertexShader.Initialize(postProcessingShader, VertexPX::Format);
	mPostProcessingPixelShader.Initialize(postProcessingShader, "PSNoProcessing");
}

void GameState::Terminate()
{
	// Post Processing 
	mPostProcessingPixelShader.Terminate();
	mPostProcessingVertexShader.Terminate();
	mScreenQuadBuffer.Terminate();
	mRenderTarget.Terminate();

	// Moon
	mSettingsMoonDataBuffer.Terminate();
	mMoonTexture.Terminate();
	mPSMoon.Terminate();
	mVSMoon.Terminate();

	// Sky Dome
	mSkydome.Terminate();

	// Earth
	mSettingsDataBuffer.Terminate();
	mNightLights.Terminate();
	mBlendState.Terminate();
	mClouds.Terminate();
	mNormalMap.Terminate();
	mDisplacementTexture.Terminate();
	mSpecularTexture.Terminate();
	mDifuseTexture.Terminate();
	mSamplers.Terminate();
	mCloudVertexShader.Terminate();
	mCloudPixelShader.Terminate();
	mEarthPixelShader.Terminate();
	mEarthVertexShader.Terminate();
	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();
	mTransformBuffer.Terminate();

	mMeshBufferMoon.Terminate();
	mMeshBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{
	const float kMoveSpeed = 100.5f;
	const float kTurnSpeed = 0.5f;
	mSkydome.Update(mCamera);
	auto inputSystem = InputSystem::Get();
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
	
	mCloudRotation += 0.0001f;
	mMoonRotation += 0.005f;
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
		ImGui::DragFloat("Rotation X##Transform", &mRotation.x, 0.01f);
		ImGui::DragFloat("Rotation Y##Transform", &mRotation.y, 0.01f);
	}

	if (ImGui::CollapsingHeader("Post Processing", ImGuiTreeNodeFlags_DefaultOpen))
	{
		static bool PosProcessingSepiaTone = false;
		static bool GreyScale = false;
		static bool InverseColor = false;
		static bool DistortionColor = false;
		static bool Default = true;

		if (ImGui::Checkbox("No Post Processing", &Default))
		{
			DistortionColor = false;
			InverseColor = false;
			GreyScale = false;
			PosProcessingSepiaTone = false;
			mPostProcessingPixelShader.Initialize("../../Assets/Shaders/PostProcessing.fx", "PSNoProcessing");
		}

		if (ImGui::Checkbox("Sepia Tone", &PosProcessingSepiaTone))
		{
			DistortionColor = false;
			InverseColor = false;
			GreyScale = false;
			Default = false;
			mPostProcessingPixelShader.Initialize("../../Assets/Shaders/PostProcessing.fx", "PSSepiaTone");
		}

		if (ImGui::Checkbox("GreyScale", &GreyScale))
		{
			DistortionColor = false;
			InverseColor = false;
			Default = false;
			PosProcessingSepiaTone = false;
			mPostProcessingPixelShader.Initialize("../../Assets/Shaders/PostProcessing.fx", "PSGreyScale");
		}

		if (ImGui::Checkbox("Inverse Color", &InverseColor))
		{
			DistortionColor = false;
			Default = false;
			GreyScale = false;
			PosProcessingSepiaTone = false;
			mPostProcessingPixelShader.Initialize("../../Assets/Shaders/PostProcessing.fx", "PSInverseColor");
		}

	}

	ImGui::End();
}

void GameState::DrawScene()
{
	auto matView = mCamera.GetViewMatrix();
	auto matProj = mCamera.GetPerspectiveMatrix();

	// SkyDome
	mSkydome.Render(mCamera);

	// Earth
	auto maTranslation = Matrix4::Translation({ 0.0f , 0.0f, 0.0f });
	auto matRotation = Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y);
	auto matWorld = matRotation * maTranslation;

	TransformData transformData;
	transformData.viewPosition = mCamera.GetPosition();
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

	mDisplacementTexture.BindPS(2);
	mDisplacementTexture.BindVS(2);

	mNormalMap.BindPS(3);

	mSamplers.BindPS();
	mSamplers.BindVS();

	mSettingsDataBuffer.Update(mSettingsData);
	mSettingsDataBuffer.BindPS(3);
	mSettingsDataBuffer.BindVS(3);

	mEarthVertexShader.Bind();
	mEarthPixelShader.Bind();

	mMeshBuffer.Draw();

	mNightLights.BindPS(5);
	mNightLights.BindVS(5);

	// --- cloud render ------ //
	matRotation = Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y + mCloudRotation);
	matWorld = matRotation * maTranslation;
	transformData.world = Transpose(matWorld);
	transformData.wvp = Transpose(matWorld * matView * matProj);

	mTransformBuffer.Update(transformData);

	mClouds.BindVS(4);
	mClouds.BindPS(4);

	mCloudVertexShader.Bind();
	mCloudPixelShader.Bind();

	mBlendState.Bind();

	mMeshBuffer.Draw();
	BlendState::ClearState();

	// Moon
	auto MoonPos = Matrix4::Translation({ 30.0f, 0.0f, 0.0f });
	auto MoonRotation = Matrix4::RotationY(mMoonRotation.y * 0.5f);

	transformData.world = Transpose(MoonPos * MoonRotation * matWorld);
	transformData.wvp = Transpose(MoonPos * MoonRotation * matWorld * matView * matProj);
	mTransformBuffer.Update(transformData);

	mSettingsMoonDataBuffer.Update(mSettingsMoonData);
	mSettingsMoonDataBuffer.BindPS(3);
	mSettingsMoonDataBuffer.BindVS(3);

	mVSMoon.Bind();
	mPSMoon.Bind();
	mMoonTexture.BindPS();
	mSamplers.BindPS();

	mMeshBufferMoon.Draw();

	SimpleDraw::Render(mCamera);
}

void GameState::PostProcess()
{
	mPostProcessingVertexShader.Bind();
	mPostProcessingPixelShader.Bind();
	mSamplers.BindPS();
	mScreenQuadBuffer.Draw();
}
