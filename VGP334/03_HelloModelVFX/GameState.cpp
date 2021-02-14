#include "GameState.h"
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
	mDefaultCamera.SetFarPlane(1000.0f);
	mDefaultCamera.SetPosition({ 600.0f, 150.0f, 50.0f });
	//mDefaultCamera.SetLookAt({ 0.0f, 100.0f, 1000.0f });
	mDefaultCamera.SetLookAt({ 600.0f, 100.0f, 1000.0f });

	mDebugCamera.SetNearPlane(0.001f);
	mDebugCamera.SetFarPlane(1000.0f);
	mDebugCamera.SetPosition({ 0.0f, 10.0f, -30.0f });
	mDebugCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mLightCamera.SetDirection(Normalize({ 1.0f, -1.0f, 1.0f }));
	mLightCamera.SetNearPlane(1.0f);
	mLightCamera.SetFarPlane(200.0f);
	mLightCamera.SetFov(1.0f);
	mLightCamera.SetAspectRatio(1.0f);

	mActiveCamera = &mDefaultCamera;

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

	mVertexShader.Initialize("../../Assets/Shaders/Standard.fx", BoneVertex::Format);
	mPixelShader.Initialize("../../Assets/Shaders/Standard.fx");

	mSampler.Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Wrap);

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

	mModelStartPosition = { 600.0f, 6.0f, 600.0f };
	mModel2_StartPosition = { 800.0f, 6.0f, 600.0f };
	mModel3_StartPosition = { 400.0f, 6.0f, 600.0f };
	// Initialize and load model from assimp
	// Breakdance is OK
	//mModel.Initialize("../../Assets/Models/Breaking_Dance/Breakdance.model");
	// Taunt is OK
	//mModel.Initialize("../../Assets/Models/Taunt/Taunt.model");
	// Capoeira is OK
	//mModel.Initialize("../../Assets/Models/Capoeira/Capoeira.model");
	//mModel.Initialize("../../Assets/Models/RoundHouse/RoundhouseKick.model");
	// SambaDancing is OK
	mModel.Initialize("../../Assets/Models/Samba/SambaDancing.model");
	mAnimator.Initialize(mModel);
	mAnimator.PlayAnimation(0);

	// Taunt is OK
	mModel2.Initialize("../../Assets/Models/Taunt/Taunt.model");
	mAnimatorModel2.Initialize(mModel2);
	mAnimatorModel2.PlayAnimation(0);

	// Breakdance is OK
	mModel3.Initialize("../../Assets/Models/Breaking_Dance/Breakdance.model");
	mAnimatorModel3.Initialize(mModel3);
	mAnimatorModel3.PlayAnimation(0);

	// calcualte the bone matrices
	mBoneTransformBuffer.Initialize();

	// Load terrain 
	mTerrain.Initialize(1200, 1200, 1.0f);
	mTerrain.SetHeightScale(30.0f);
}

void GameState::Terminate()
{
	mTerrain.Terminate();

	// Bone ConstatBuffer
	mBoneTransformBuffer.Terminate();

	// Model
	mAnimatorModel3.Terminate();
	mModel3.Terminate();
	mAnimatorModel2.Terminate();
	mModel2.Terminate();
	mAnimator.Terminate();
	mModel.Terminate();

	mRenderTarget.Terminate();
	mShadowConstantBuffer.Terminate();
	mDepthMapConstantBuffer.Terminate();
	mDepthMapPixelShader.Terminate();
	mDepthMapVertexShader.Terminate();
	mDepthMapRenderTarget.Terminate();

	mAOMap.Terminate();
	mNormalMap.Terminate();
	mDisplacementMap.Terminate();
	mSpecularMap.Terminate();
	mDiffuseMap.Terminate();
	mSampler.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mSettingsBuffer.Terminate();
	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();
	mTransformBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();

	const float kMoveSpeed = inputSystem->IsKeyDown(KeyCode::LSHIFT) ? 100.0f : 10.0f;
	const float kTurnSpeed = 1.0f;

	if (inputSystem->IsKeyDown(KeyCode::W))
	{
		mDefaultCamera.Walk(kMoveSpeed * deltaTime);
		mLightCamera.Walk(kMoveSpeed * deltaTime);
	}

	if (inputSystem->IsKeyDown(KeyCode::S))
	{
		mActiveCamera->Walk(-kMoveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::D))
	{
		mActiveCamera->Strafe(kMoveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::A))
	{
		mActiveCamera->Strafe(-kMoveSpeed * deltaTime);
	}
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mActiveCamera->Yaw(inputSystem->GetMouseMoveX() * kTurnSpeed * deltaTime);
		mActiveCamera->Pitch(inputSystem->GetMouseMoveY() * kTurnSpeed * deltaTime);
	}
	mAnimator.ShowSkeleton(mIsSkeleton);
	mAnimator.Update(deltaTime);

	mAnimatorModel2.ShowSkeleton(mIsSkeleton);
	mAnimatorModel2.Update(deltaTime);

	mAnimatorModel3.ShowSkeleton(mIsSkeleton);
	mAnimatorModel3.Update(deltaTime);

	mLightCamera.SetDirection(mDirectionalLight.direction);

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

	const auto& lightLook = mLightCamera.GetDirection();
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
	mLightCamera.SetNearPlane(minZ - 300.0f);
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

	mRenderTarget.BindPS(0);
	DrawScene();
	mRenderTarget.UnBindPS(0);
}

void GameState::DebugUI()
{
	ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	//if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
	//{
	//	/*bool lightCamera = mActiveCamera == &mLightCamera;
	//	if (ImGui::Checkbox("Use Light Camera", &lightCamera))
	//	{
	//		mActiveCamera = lightCamera ? &mLightCamera : &mDefaultCamera;
	//	}
	//	bool debugCamera = mActiveCamera == &mDebugCamera;
	//	if (ImGui::Checkbox("Use Debug Camera", &debugCamera))
	//	{
	//		mActiveCamera = debugCamera ? &mDebugCamera : &mDefaultCamera;
	//	}*/

	//	// comment because is not using
	//	/*ImGui::Image(
	//		mDepthMapRenderTarget.GetShaderResourceView(),
	//		{ 150.0f, 150.0f },
	//		{ 0.0f, 0.0f },
	//		{ 1.0f, 1.0f },
	//		{ 1.0f, 1.0f, 1.0f, 1.0f },
	//		{ 1.0f, 1.0f, 1.0f, 1.0f }
	//	);*/
	//}

	ImGui::Checkbox("Set time", &mSetTimeCheck);
	if (mSetTimeCheck)
	{
		ImGui::SliderFloat("Set Time", &mSetTime, 0.0f, mAnimator.GetMaxDuration());
		mAnimator.SetTime(mSetTime);
		mAnimatorModel2.SetTime(mSetTime);
		mAnimatorModel3.SetTime(mSetTime);
	}

	ImGui::Checkbox("Show Skeleton", &mIsSkeleton);
	ImGui::End();
}

void GameState::DrawDepthMap()
{
	mDepthMapVertexShader.Bind();
	mDepthMapPixelShader.Bind();

	auto matViewLight = mLightCamera.GetViewMatrix();
	auto matProjLight = mLightProjectMatrix;// mLightCamera.GetPerspectiveMatrix();

	mDepthMapConstantBuffer.BindVS(0);

	auto matWorld = Matrix4::Translation(mModelStartPosition);
	auto wvp = Transpose(matWorld * matViewLight * matProjLight);

	mDepthMapConstantBuffer.Update(wvp);

	mModel.Draw();
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

	mBoneTransformBuffer.BindVS(5);

	// Model 1
	auto matWorld1 = Matrix4::Translation(mModelStartPosition);

	TransformData transformData1;
	transformData1.world = Transpose(matWorld1);
	transformData1.wvp = Transpose(matWorld1 * matView * matProj);
	transformData1.viewPosition = mActiveCamera->GetPosition();
	mTransformBuffer.Update(transformData1);

	auto wvpLight1 = Transpose(matWorld1 * matViewLight * matProjLight);
	mShadowConstantBuffer.Update(wvpLight1);

	BoneTransformData boneTransformData{};
	for (size_t i = 0; i < mAnimator.GetBoneMatrices().size(); ++i)
	{
		boneTransformData.boneTransforms[i] = mAnimator.GetBoneMatrices()[i];
	}
	// Send final transform to Shader
	mBoneTransformBuffer.Update(boneTransformData);

	if (!mIsSkeleton)
	{
		mModel.Draw();
	}
	else
	{
		DrawSkeleton(mModel.skeleton, mAnimator.GetBoneMatrices(), mModelStartPosition);
	}

	// Model 2
	auto matWorld2 = Matrix4::Translation(mModel2_StartPosition);
	TransformData transformData2;
	transformData2.world = Transpose(matWorld2);
	transformData2.wvp = Transpose(matWorld2 * matView * matProj);
	transformData2.viewPosition = mActiveCamera->GetPosition();
	mTransformBuffer.Update(transformData2);

	auto wvpLight2 = Transpose(matWorld2 * matViewLight * matProjLight);
	mShadowConstantBuffer.Update(wvpLight2);

	boneTransformData.boneTransforms;
	for (size_t i = 0; i < mAnimatorModel2.GetBoneMatrices().size(); ++i)
	{
		boneTransformData.boneTransforms[i] = mAnimatorModel2.GetBoneMatrices()[i];
	}
	// Send final transform to Shader
	mBoneTransformBuffer.Update(boneTransformData);

	if (!mIsSkeleton)
	{
		mModel2.Draw();
	}
	else
	{
		DrawSkeleton(mModel2.skeleton, mAnimatorModel2.GetBoneMatrices(), mModel2_StartPosition);
	}

	// Model 3
	auto matWorld3 = Matrix4::Translation(mModel3_StartPosition);
	TransformData transformData3;
	transformData3.world = Transpose(matWorld3);
	transformData3.wvp = Transpose(matWorld3 * matView * matProj);
	transformData3.viewPosition = mActiveCamera->GetPosition();
	mTransformBuffer.Update(transformData3);

	auto wvpLight3 = Transpose(matWorld3 * matViewLight * matProjLight);
	mShadowConstantBuffer.Update(wvpLight3);

	boneTransformData.boneTransforms;
	for (size_t i = 0; i < mAnimatorModel3.GetBoneMatrices().size(); ++i)
	{
		boneTransformData.boneTransforms[i] = mAnimatorModel3.GetBoneMatrices()[i];
	}
	// Send final transform to Shader
	mBoneTransformBuffer.Update(boneTransformData);

	if (!mIsSkeleton)
	{
		mModel3.Draw();
	}
	else
	{
		DrawSkeleton(mModel3.skeleton, mAnimatorModel3.GetBoneMatrices(), mModel3_StartPosition);
	}

	mTerrain.SetDirectionalLight(mDirectionalLight);
	mTerrain.Render(mDefaultCamera);

	SettingsData settings;
	settings.specularMapWeight = 0.0f;
	settings.bumpMapWeight = 0.0f;
	settings.normalMapWeight = 0.0f;
	settings.aoMapWeight = 0.0f;
	settings.useShadow = 1;
	mSettingsBuffer.Update(settings);

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

	SimpleDrawCamera(mDefaultCamera);

	SimpleDraw::Render(*mActiveCamera);
}

