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

	mMesh = MeshBuilder::CreateSphere(10, 64, 64);
	mMeshBuffer.Initialize(mMesh);

	mMeshSkyBox = MeshBuilder::CreateSpherePX(1000, 12, 360, true);
	mMeshBufferSkyBox.Initialize(mMeshSkyBox);

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
	mMaterial.power =  10.0f ;

	mSettingsData.bumpMapWeight = 0.2f;

	std::filesystem::path assetsEarth = "../../Assets/Shaders/Earth.fx";
	mEarthVertexShader.Initialize(assetsEarth, "VSEarth", Vertex::Format);
	mEarthPixelShader.Initialize(assetsEarth, "PSEarth");

	mCloudVertexShader.Initialize(assetsEarth, "VSCloud", Vertex::Format);
	mCloudPixelShader.Initialize(assetsEarth, "PSCloud");
	mSamplers.Initialize(Sampler::Filter::Point, Sampler::AddressMode::Wrap);
	mSkyBoxVS.Initialize("../../Assets/Shaders/DoTexturing.fx", Vertex::Format);
	mSkyBoxPS.Initialize("../../Assets/Shaders/DoTexturing.fx");

	mSamplers.Initialize(Sampler::Filter::Point, Sampler::AddressMode::Wrap);
	std::filesystem::path root = "../../Assets/Textures";
	mDifuseTexture.Initialize(root / "earth.jpg");
	mSpecularTexture.Initialize(root / "earth_spec.tif");
	mDisplacementTexture.Initialize(root / "earth_bump.jpg");
	mNormalMap.Initialize(root/ "earth_normal.tif");
	mClouds.Initialize(root / "earth_clouds.jpg");
	mNightLights.Initialize(root / "earth_lights.jpg");

	//mSkybox.Initialize(root / "Space_Skybox.jpg");
	mSkybox.Initialize(root / "Space.jpg");

	//SkyBox ConstantBuffer
	mSkyBoxConstantBuffer.Initialize(sizeof(Omega::Math::Matrix4));

	mBlendState.Initialize(BlendState::Mode::AlphaBlending);

	mSettingsDataBuffer.Initialize();
}

void GameState::Terminate()
{
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

	mSkyBoxConstantBuffer.Terminate();
	mMeshBufferSkyBox.Terminate();

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

	mCloudRotation += 0.0005f;
}

void GameState::Render()
{
	auto maTranslation = Matrix4::Translation({ 0.0f , 0.0f, 0.0f });

	auto matRotation = Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y);
	auto matWorld = matRotation * maTranslation;
	auto matView = mCamera.GetViewMatrix();
	auto matProj = mCamera.GetPerspectiveMatrix();

	auto matWVP = Transpose(matWorld * matView * matProj);

	//// Skybox try to fixed the skybox
	//mSkybox.BindVS();
	//mSkybox.BindPS();
	//mSkyBoxConstantBuffer.Update(&matWVP);
	//mSkyBoxConstantBuffer.BindVS(0);
	//mSkyBoxConstantBuffer.BindPS(0);
	//mMeshBufferSkyBox.Draw();

	// Earth
	TransformData transformData;
	matWorld = Matrix4::Translation({ 0.0f,0.0f,0.0f });
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

	SimpleDraw::Render(mCamera);
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
		if(ImGui::Checkbox("Specular", &specularMap))
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

	ImGui::End();
}