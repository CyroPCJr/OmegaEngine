#include "GameState.h"

#include <ImGui/Inc/imgui.h>

using namespace Omega::Graphics;
using namespace Omega::Input;
using namespace Omega::Math;

namespace
{
	void SimpleDrawCamera(const Camera& camera)
	{
		auto defaultMatView = camera.GetViewMatrix();
		Vector3 cameraPosition = camera.GetPosition();
		Vector3 cameraRight = { defaultMatView._11, defaultMatView._21, defaultMatView._31 };
		Vector3 cameraUp = { defaultMatView._12, defaultMatView._22, defaultMatView._32 };
		Vector3 cameraLook = { defaultMatView._13, defaultMatView._23, defaultMatView._33 };
		//SimpleDraw::AddSphere(cameraPosition, 0.1f, Colors::White, 6, 8);
		SimpleDraw::AddLine(cameraPosition, cameraPosition + cameraRight, Colors::Red);
		SimpleDraw::AddLine(cameraPosition, cameraPosition + cameraUp, Colors::Green);
		SimpleDraw::AddLine(cameraPosition, cameraPosition + cameraLook, Colors::Blue);
	}
}

void GameState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Black);

	mDefaultCamera.SetNearPlane(0.1f);
	mDefaultCamera.SetFarPlane(200.0f);
	mDefaultCamera.SetPosition({ 0.0f, 10.0f, -30.0f });
	mDefaultCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mDebugCamera.SetNearPlane(0.001f);
	mDebugCamera.SetFarPlane(10000.0f);
	mDebugCamera.SetPosition({ 0.0f, 10.0f, -30.0f });
	mDebugCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mLightCamera.SetDirection(Normalize({ 1.0f, -1.0f, 1.0f }));
	mLightCamera.SetNearPlane(1.0f);
	mLightCamera.SetFarPlane(200.0f);
	mLightCamera.SetFov(1.0f);
	mLightCamera.SetAspectRatio(1.0f);

	mActiveCamera = &mDefaultCamera;

	ObjLoader::Load("../../Assets/Models/Tank/tank.obj", 0.001f, mTankMesh);
	mTankMeshBuffer.Initialize(mTankMesh);

	mGroundMesh = MeshBuilder::CreatePlane(300.0f);
	mGroundMeshBuffer.Initialize(mGroundMesh);

	mTransformBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSettingsBuffer.Initialize();
	mPostProcessingSettingsBuffer.Initialize();

	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
	mDirectionalLight.diffuse = { 0.75f, 0.75f, 0.75f, 1.0f };
	mDirectionalLight.specular = { 0.5f, 0.5f, 0.5f, 1.0f };

	mMaterial.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
	mMaterial.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mMaterial.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mMaterial.power = 40.0f;

	mSettings.specularMapWeight = 1.0f;
	mSettings.bumpMapWeight = 0.0f;
	mSettings.normalMapWeight = 0.0f;
	mSettings.aoMapWeight = 1.0f;
	mSettings.brightness = 3.5f;
	mSettings.useShadow = 1;
	mSettings.depthBias = 0.0003f;

	mVertexShader.Initialize("../../Assets/Shaders/Standard.fx", Vertex::Format);
	mPixelShader.Initialize("../../Assets/Shaders/Standard.fx");

	mSampler.Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Wrap);
	mDiffuseMap.Initialize("../../Assets/Models/Tank/tank_diffuse.jpg");
	mSpecularMap.Initialize("../../Assets/Models/Tank/tank_specular.jpg");
	mNormalMap.Initialize("../../Assets/Models/Tank/tank_normal.jpg");
	mAOMap.Initialize("../../Assets/Models/Tank/tank_ao.jpg");

	mGroundDiffuseMap.Initialize("../../Assets/Textures/grass.jpg");

	auto graphicsSystem = GraphicsSystem::Get();

	constexpr uint32_t depthMapSize = 4096;
	mDepthMapRenderTarget.Initialize(depthMapSize, depthMapSize, RenderTarget::Format::RGBA_U32);
	mDepthMapVertexShader.Initialize("../../Assets/Shaders/DepthMap.fx", Vertex::Format);
	mDepthMapPixelShader.Initialize("../../Assets/Shaders/DepthMap.fx");
	mDepthMapConstantBuffer.Initialize();
	mShadowConstantBuffer.Initialize();

	mRenderTarget.Initialize(
		graphicsSystem->GetBackBufferWidth(),
		graphicsSystem->GetBackBufferHeight(),
		RenderTarget::Format::RGBA_U8);

	mScreenQuad = MeshBuilder::CreateNDCQuad();
	mScreenQuadBuffer.Initialize(mScreenQuad);

	mPostProcessingVertexShader.Initialize("../../Assets/Shaders/PostProcessing.fx", VertexPX::Format);
	mPostProcessingPixelShader.Initialize("../../Assets/Shaders/PostProcessing.fx", "PSNoProcessing");
}

void GameState::Terminate()
{
	mPostProcessingPixelShader.Terminate();
	mPostProcessingVertexShader.Terminate();
	mScreenQuadBuffer.Terminate();
	mRenderTarget.Terminate();
	mShadowConstantBuffer.Terminate();
	mDepthMapConstantBuffer.Terminate();
	mDepthMapPixelShader.Terminate();
	mDepthMapVertexShader.Terminate();
	mDepthMapRenderTarget.Terminate();
	mGroundDiffuseMap.Terminate();
	mAOMap.Terminate();
	mNormalMap.Terminate();
	mDisplacementMap.Terminate();
	mSpecularMap.Terminate();
	mDiffuseMap.Terminate();
	mSampler.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mPostProcessingSettingsBuffer.Terminate();
	mSettingsBuffer.Terminate();
	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();
	mTransformBuffer.Terminate();
	mGroundMeshBuffer.Terminate();
	mTankMeshBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{
	const float kMoveSpeed = 10.0f;
	const float kTurnSpeed = 1.0f;

	auto inputSystem = InputSystem::Get();
	if (inputSystem->IsKeyDown(KeyCode::W))
	{
		mDefaultCamera.Walk(kMoveSpeed * deltaTime);
		mLightCamera.Walk(kMoveSpeed * deltaTime);
		//mTankPosition.z += kMoveSpeed * deltaTime;
	}

	if (inputSystem->IsKeyDown(KeyCode::S))
	{
		mActiveCamera->Walk(-kMoveSpeed * deltaTime);
		//mTankPosition.z -= kMoveSpeed * deltaTime;
	}
	if (inputSystem->IsKeyDown(KeyCode::D))
	{
		mActiveCamera->Strafe(kMoveSpeed * deltaTime);
		mTankRotation.y += kMoveSpeed * deltaTime;
	}
	if (inputSystem->IsKeyDown(KeyCode::A))
	{
		mActiveCamera->Strafe(-kMoveSpeed * deltaTime);
		mTankRotation.y -= kMoveSpeed * deltaTime;
	}
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mActiveCamera->Yaw(inputSystem->GetMouseMoveX() * kTurnSpeed * deltaTime);
		mActiveCamera->Pitch(inputSystem->GetMouseMoveY() * kTurnSpeed * deltaTime);
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

	mPostProcessSettings.time += deltaTime;

	mLightCamera.SetDirection(mDirectionalLight.direction);
	//mLightCamera.SetPosition(mLightCamera.GetDirection() * -50.0f);

	mTankPositions.clear();

	const int count = 5;
	const float offsetX = (count - 1) * mTankSpacing * -0.5f;
	const float offsetZ = (count - 1) * mTankSpacing * -0.5f;
	for (int z = 0; z < count; ++z)
	{
		for (int x = 0; x < count; ++x)
		{
			float posX = (x * mTankSpacing) + offsetX;
			float posZ = (z * mTankSpacing) + offsetZ;
			mTankPositions.push_back({ posX, 3.5f, posZ });
		}
	}

	mViewFrustumVertices =
	{
		// Near plane
		{ -1.0f, -1.0f, 0.0f },
		{ -1.0f,  1.0f, 0.0f },
		{  1.0f,  1.0f, 0.0f },
		{  1.0f, -1.0f, 0.0f },

		// Far plane
		{ -1.0f, -1.0f, 1.0f },
		{ -1.0f,  1.0f, 1.0f },
		{  1.0f,  1.0f, 1.0f },
		{  1.0f, -1.0f, 1.0f },
	};
	auto defaultMatView = mDefaultCamera.GetViewMatrix();
	auto defaultMatProj = mDefaultCamera.GetPerspectiveMatrix();
	auto invViewProj = Inverse(defaultMatView * defaultMatProj);
	for (auto& vertex : mViewFrustumVertices)
	{
		vertex = TransformCoord(vertex, invViewProj);
	}

	auto lightLook = mLightCamera.GetDirection();
	auto lightSide = Normalize(Cross(Vector3::YAxis, lightLook));
	auto lightUp = Normalize(Cross(lightLook, lightSide));
	float minX = FLT_MAX, maxX = -FLT_MAX;
	float minY = FLT_MAX, maxY = -FLT_MAX;
	float minZ = FLT_MAX, maxZ = -FLT_MAX;
	for (auto& vertex : mViewFrustumVertices)
	{
		float projectX = Dot(lightSide, vertex);
		minX = Min(minX, projectX);
		maxX = Max(maxX, projectX);
		float projectY = Dot(lightUp, vertex);
		minY = Min(minY, projectY);
		maxY = Max(maxY, projectY);
		float projectZ = Dot(lightLook, vertex);
		minZ = Min(minZ, projectZ);
		maxZ = Max(maxZ, projectZ);
	}
	mLightCamera.SetPosition(
		lightSide + (minX + maxX) * 0.5f +
		lightUp + (minY + maxY) * 0.5f +
		lightLook + (minZ + maxZ) * 0.5f
	);
	mLightCamera.SetNearPlane(minZ);
	mLightCamera.SetFarPlane(maxZ);
	mLightProjectMatrix = mLightCamera.GetOrthoGraphiMatrix(maxX - minX, maxY - minY);

	auto v0 = lightSide * minX + lightUp * minY + lightLook * minZ;
	auto v1 = lightSide * minX + lightUp * maxY + lightLook * minZ;
	auto v2 = lightSide * maxX + lightUp * maxY + lightLook * minZ;
	auto v3 = lightSide * maxX + lightUp * minY + lightLook * minZ;
	auto v4 = lightSide * minX + lightUp * minY + lightLook * maxZ;
	auto v5 = lightSide * minX + lightUp * maxY + lightLook * maxZ;
	auto v6 = lightSide * maxX + lightUp * maxY + lightLook * maxZ;
	auto v7 = lightSide * maxX + lightUp * minY + lightLook * maxZ;

	SimpleDraw::AddLine(v0, v1, Colors::Yellow);
	SimpleDraw::AddLine(v1, v2, Colors::Yellow);
	SimpleDraw::AddLine(v2, v3, Colors::Yellow);
	SimpleDraw::AddLine(v3, v0, Colors::Yellow);

	SimpleDraw::AddLine(v0, v4, Colors::Red);
	SimpleDraw::AddLine(v1, v5, Colors::Red);
	SimpleDraw::AddLine(v2, v6, Colors::Red);
	SimpleDraw::AddLine(v3, v7, Colors::Red);

	SimpleDraw::AddLine(v4, v5, Colors::Red);
	SimpleDraw::AddLine(v5, v6, Colors::Red);
	SimpleDraw::AddLine(v6, v7, Colors::Red);
	SimpleDraw::AddLine(v7, v4, Colors::Red);
	
	SimpleDrawCamera(mLightCamera);

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
		bool debugCamera = mActiveCamera == &mDebugCamera;
		if (ImGui::Checkbox("Use Debug Camera", &debugCamera))
		{
			mActiveCamera = debugCamera ? &mDebugCamera : &mDefaultCamera;
		}

		ImGui::Image(
			mDepthMapRenderTarget.GetShaderResourceView(),
			{ 150.0f, 150.0f },
			{ 0.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			{ 1.0f, 1.0f, 1.0f, 1.0f }
		);
	}
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
	if (ImGui::CollapsingHeader("Settings", ImGuiTreeNodeFlags_DefaultOpen))
	{
		static bool specularMap = mSettings.specularMapWeight > 0.0f;
		static bool normalMap = mSettings.normalMapWeight > 0.0f;
		static bool aoMap = mSettings.aoMapWeight > 0.0f;
		static bool useShadow = mSettings.useShadow == 1;
		ImGui::SliderFloat("Displacement", &mSettings.bumpMapWeight, 0.0f, 1.0f);
		if (ImGui::Checkbox("Specular Map", &specularMap))
		{
			mSettings.specularMapWeight = specularMap ? 1.0f : 0.0f;
		}
		if (ImGui::Checkbox("Normal Map", &normalMap))
		{
			mSettings.normalMapWeight = normalMap ? 1.0f : 0.0f;
		}
		if (ImGui::Checkbox("Ambient Occlusion Map", &aoMap))
		{
			mSettings.aoMapWeight = aoMap ? 1.0f : 0.0f;
		}
		if (ImGui::Checkbox("Use Shadow", &useShadow))
		{
			mSettings.useShadow = useShadow ? 1 : 0;
		}
		ImGui::SliderFloat("Depth Bias", &mSettings.depthBias, 0.0f, 0.01f, "%.4f");
		ImGui::SliderFloat("Brightness", &mSettings.brightness, 1.0f, 10.0f);
	}
	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat3("Translation##Transform", &mTankPositions[0].x, 0.01f);
		ImGui::DragFloat3("Rotation##Transform", &mTankRotation.x, 0.01f);
		ImGui::DragFloat("Spacing", &mTankSpacing, 0.1f, 0.5f, 100.0f);
	}
	ImGui::End();
}

void GameState::DrawDepthMap()
{
	mDepthMapVertexShader.Bind();
	mDepthMapPixelShader.Bind();

	auto matViewLight = mLightCamera.GetViewMatrix();
	auto matProjLight = mLightProjectMatrix;// mLightCamera.GetPerspectiveMatrix();

	mDepthMapConstantBuffer.BindVS(0);

	for (auto& position : mTankPositions)
	{
		auto matTrans = Matrix4::Translation(position);
		auto matRot = Matrix4::RotationX(mTankRotation.x) * Matrix4::RotationY(mTankRotation.y);
		auto matWorld = matRot * matTrans;
		auto wvp = Transpose(matWorld * matViewLight * matProjLight);
		mDepthMapConstantBuffer.Update(wvp);
		mTankMeshBuffer.Draw();
	}
}

void GameState::DrawScene()
{
	auto matView = mActiveCamera->GetViewMatrix();
	auto matProj = mActiveCamera->GetPerspectiveMatrix();
	auto matViewLight = mLightCamera.GetViewMatrix();
	auto matProjLight = mLightProjectMatrix; //mLightCamera.GetPerspectiveMatrix();

	mLightBuffer.Update(mDirectionalLight);
	mLightBuffer.BindVS(1);
	mLightBuffer.BindPS(1);

	mMaterialBuffer.Update(mMaterial);
	mMaterialBuffer.BindVS(2);
	mMaterialBuffer.BindPS(2);

	mSettingsBuffer.Update(mSettings);
	mSettingsBuffer.BindVS(3);
	mSettingsBuffer.BindPS(3);

	mSampler.BindVS();
	mSampler.BindPS();

	mDiffuseMap.BindPS(0);
	mSpecularMap.BindPS(1);
	mDisplacementMap.BindVS(2);
	mNormalMap.BindPS(3);
	mAOMap.BindPS(4);
	mDepthMapRenderTarget.BindPS(5);

	mVertexShader.Bind();
	mPixelShader.Bind();

	mTransformBuffer.BindVS(0);
	mShadowConstantBuffer.BindVS(4);

	for (auto& position : mTankPositions)
	{
		auto matTrans = Matrix4::Translation(position);
		auto matRot = Matrix4::RotationX(mTankRotation.x) * Matrix4::RotationY(mTankRotation.y);
		auto matWorld = matRot * matTrans;

		TransformData transformData;
		transformData.world = Transpose(matWorld);
		transformData.wvp = Transpose(matWorld * matView * matProj);
		transformData.viewPosition = mActiveCamera->GetPosition();
		mTransformBuffer.Update(transformData);

		auto wvpLight = Transpose(matWorld * matViewLight * matProjLight);
		mShadowConstantBuffer.Update(wvpLight);

		mTankMeshBuffer.Draw();
	}

	auto matWorld = Matrix4::Identity;
	TransformData transformData;
	transformData.world = Transpose(matWorld);
	transformData.wvp = Transpose(matWorld * matView * matProj);
	mTransformBuffer.Update(transformData);

	auto wvpLight = Transpose(matWorld * matViewLight * matProjLight);
	mShadowConstantBuffer.Update(wvpLight);

	mGroundDiffuseMap.BindPS(0);

	SettingsData settings;
	settings.specularMapWeight = 0.0f;
	settings.bumpMapWeight = 0.0f;
	settings.normalMapWeight = 0.0f;
	settings.aoMapWeight = 0.0f;
	settings.useShadow = 1;
	mSettingsBuffer.Update(settings);

	mGroundMeshBuffer.Draw();

	SimpleDraw::AddLine(mViewFrustumVertices[0], mViewFrustumVertices[1], Colors::White);
	SimpleDraw::AddLine(mViewFrustumVertices[1], mViewFrustumVertices[2], Colors::White);
	SimpleDraw::AddLine(mViewFrustumVertices[2], mViewFrustumVertices[3], Colors::White);
	SimpleDraw::AddLine(mViewFrustumVertices[3], mViewFrustumVertices[0], Colors::White);

	SimpleDraw::AddLine(mViewFrustumVertices[0], mViewFrustumVertices[4], Colors::White);
	SimpleDraw::AddLine(mViewFrustumVertices[1], mViewFrustumVertices[5], Colors::White);
	SimpleDraw::AddLine(mViewFrustumVertices[2], mViewFrustumVertices[6], Colors::White);
	SimpleDraw::AddLine(mViewFrustumVertices[3], mViewFrustumVertices[7], Colors::White);

	SimpleDraw::AddLine(mViewFrustumVertices[4], mViewFrustumVertices[5], Colors::White);
	SimpleDraw::AddLine(mViewFrustumVertices[5], mViewFrustumVertices[6], Colors::White);
	SimpleDraw::AddLine(mViewFrustumVertices[6], mViewFrustumVertices[7], Colors::White);
	SimpleDraw::AddLine(mViewFrustumVertices[7], mViewFrustumVertices[4], Colors::White);

	auto defaultMatView = mDefaultCamera.GetViewMatrix();
	Vector3 cameraPosition = mDefaultCamera.GetPosition();
	Vector3 cameraRight = { defaultMatView._11, defaultMatView._21, defaultMatView._31 };
	Vector3 cameraUp = { defaultMatView._12, defaultMatView._22, defaultMatView._32 };
	Vector3 cameraLook = { defaultMatView._13, defaultMatView._23, defaultMatView._33 };
	//TODO: Add position to this function AddSphere
	//SimpleDraw::AddSphere(cameraPosition, 0.1f, 6, 8, Colors::White);
	SimpleDraw::AddLine(cameraPosition, cameraPosition + cameraRight, Colors::Red);
	SimpleDraw::AddLine(cameraPosition, cameraPosition + cameraUp, Colors::Green);
	SimpleDraw::AddLine(cameraPosition, cameraPosition + cameraLook, Colors::Blue);

	SimpleDraw::Render(*mActiveCamera);
}

void GameState::PostProcess()
{
	mPostProcessingVertexShader.Bind();
	mPostProcessingPixelShader.Bind();

	mSampler.BindPS();

	auto graphicsSystem = GraphicsSystem::Get();
	mPostProcessSettings.screenWidth = (float)graphicsSystem->GetBackBufferWidth();
	mPostProcessSettings.screenHeight = (float)graphicsSystem->GetBackBufferHeight();
	mPostProcessingSettingsBuffer.Update(mPostProcessSettings);
	mPostProcessingSettingsBuffer.BindVS(0);
	mPostProcessingSettingsBuffer.BindPS(0);

	mScreenQuadBuffer.Draw();
}
