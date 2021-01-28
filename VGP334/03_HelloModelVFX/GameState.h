#pragma once

#include <OmegaEngine/Inc/Omega.h>

class GameState : public Omega::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

private:
	void DrawDepthMap();
	void DrawScene();

private:
	Omega::Graphics::Camera mDefaultCamera;
	Omega::Graphics::Camera mDebugCamera;
	Omega::Graphics::Camera mLightCamera;
	Omega::Graphics::Camera* mActiveCamera = nullptr;

	Omega::Math::Matrix4 mLightProjectMatrix;

	std::vector<Omega::Math::Vector3> mViewFrustumVertices;

	struct TransformData
	{
		Omega::Math::Matrix4 world = Omega::Math::Matrix4::Identity;
		Omega::Math::Matrix4 wvp = Omega::Math::Matrix4::Identity;
		Omega::Math::Vector3 viewPosition = Omega::Math::Vector3::Zero;
		int blendIndices[4] = { 0 };
		float blendWeights[4] = { 0.0f };
		float padding = 0.0f;
	};

	struct SettingsData
	{
		float specularMapWeight = 1.0f;
		float bumpMapWeight = 1.0f;
		float normalMapWeight = 1.0f;
		float aoMapWeight = 1.0f;
		float brightness = 1.0f;
		int useShadow = 1;
		float depthBias = 0.0f;
		float padding = 0.0f;
	};

	struct PostProcessSettingsData
	{
		float screenWidth = 0.0f;
		float screenHeight = 0.0f;
		float time = 0.0f;
		float padding;
	};

	using TransformBuffer = Omega::Graphics::TypedConstantBuffer<TransformData>;
	using LightBuffer = Omega::Graphics::TypedConstantBuffer<Omega::Graphics::DirectionalLight>;
	using MaterialBuffer = Omega::Graphics::TypedConstantBuffer<Omega::Graphics::Material>;
	using SettingsBuffer = Omega::Graphics::TypedConstantBuffer<SettingsData>;
	using PostProcessingSettingsBuffer = Omega::Graphics::TypedConstantBuffer<PostProcessSettingsData>;
	using DepthMapConstantBuffer = Omega::Graphics::TypedConstantBuffer<Omega::Math::Matrix4>;
	using ShadowConstantBuffer = Omega::Graphics::TypedConstantBuffer<Omega::Math::Matrix4>;

	TransformBuffer mTransformBuffer;
	LightBuffer mLightBuffer;
	MaterialBuffer mMaterialBuffer;
	SettingsBuffer mSettingsBuffer;
	PostProcessingSettingsBuffer mPostProcessingSettingsBuffer;

	Omega::Graphics::DirectionalLight mDirectionalLight;
	Omega::Graphics::Material mMaterial;

	Omega::Graphics::VertexShader mVertexShader;
	Omega::Graphics::PixelShader mPixelShader;

	Omega::Graphics::Sampler mSampler;
	Omega::Graphics::Texture mDiffuseMap;
	Omega::Graphics::Texture mSpecularMap;
	Omega::Graphics::Texture mDisplacementMap;
	Omega::Graphics::Texture mNormalMap;
	Omega::Graphics::Texture mAOMap;

	SettingsData mSettings;

	// Shadow
	Omega::Graphics::RenderTarget mDepthMapRenderTarget;
	Omega::Graphics::VertexShader mDepthMapVertexShader;
	Omega::Graphics::PixelShader mDepthMapPixelShader;
	DepthMapConstantBuffer mDepthMapConstantBuffer;
	ShadowConstantBuffer mShadowConstantBuffer;

	// Render Target
	Omega::Graphics::RenderTarget mRenderTarget;
	
	//Model
	Omega::Graphics::Model mModel;
	Omega::Graphics::Model mModel2;
	Omega::Graphics::Model mModel3;
	std::vector<Omega::Math::Matrix4> mBoneMatrices;
	bool mIsSkeleton = false;
	bool mStopAnimation = false;
	Omega::Math::Vector3 mModelStartPosition;
	Omega::Math::Vector3 mModel2_StartPosition;
	Omega::Math::Vector3 mModel3_StartPosition;


	// Skeleton Buffer
	struct BoneTransformData
	{
		Omega::Math::Matrix4 boneTransforms[256];
	};

	using BoneTransformBuffer = Omega::Graphics::TypedConstantBuffer<BoneTransformData>;
	BoneTransformBuffer mBoneTransformBuffer;

	Omega::Graphics::Animator mAnimator;
	Omega::Graphics::Animator mAnimatorModel2;
	Omega::Graphics::Animator mAnimatorModel3;

	// Terrain
	Omega::Terrain mTerrain;
	float mSetTime = 0.0f;
	bool mSetTimeCheck = false;
};