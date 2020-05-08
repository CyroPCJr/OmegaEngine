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
	void PostProcess();

private:
	Omega::Graphics::Camera mDefaultCamera;
	Omega::Graphics::Camera mDebugCamera;
	Omega::Graphics::Camera mLightCamera;
	Omega::Graphics::Camera* mActiveCamera = nullptr;

	Omega::Math::Matrix4 mLightProjectMatrix;

	std::vector<Omega::Math::Vector3> mViewFrustumVertices;

	Omega::Graphics::Mesh mTankMesh;
	Omega::Graphics::MeshBuffer mTankMeshBuffer;

	Omega::Graphics::Mesh mGroundMesh;
	Omega::Graphics::MeshBuffer mGroundMeshBuffer;

	struct TransformData
	{
		Omega::Math::Matrix4 world;
		Omega::Math::Matrix4 wvp;
		Omega::Math::Vector3 viewPosition;
		float padding;
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
		float padding;
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

	Omega::Graphics::Texture mGroundDiffuseMap;

	SettingsData mSettings;

	// Shadow
	Omega::Graphics::RenderTarget mDepthMapRenderTarget;
	Omega::Graphics::VertexShader mDepthMapVertexShader;
	Omega::Graphics::PixelShader mDepthMapPixelShader;
	DepthMapConstantBuffer mDepthMapConstantBuffer;
	ShadowConstantBuffer mShadowConstantBuffer;

	// Post processing
	Omega::Graphics::RenderTarget mRenderTarget;
	Omega::Graphics::MeshPX mScreenQuad;
	Omega::Graphics::MeshBuffer mScreenQuadBuffer;
	Omega::Graphics::VertexShader mPostProcessingVertexShader;
	Omega::Graphics::PixelShader mPostProcessingPixelShader;
	PostProcessSettingsData mPostProcessSettings;
	
	//Model
	Omega::Graphics::Model mModel;
	Omega::Graphics::Animation mAnimation;
	float mAnimationTime = 0.0f;
};