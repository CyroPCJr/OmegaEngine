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

	void DrawScene();
	void PostProcess();

private:
	Omega::Graphics::Camera mDefaultCamera;
	Omega::Graphics::Camera mLightCamera;
	Omega::Graphics::Camera* mActiveCamera = nullptr;;

	// Tank
	Omega::Graphics::Mesh mTankMesh;
	Omega::Graphics::MeshBuffer mTankMeshBuffer;
	
	Omega::Graphics::Sampler mSamplers;
	Omega::Graphics::Texture mDifuseTexture;
	Omega::Graphics::Texture mSpecularTexture;
	Omega::Graphics::Texture mNormalMap;

	Omega::Graphics::VertexShader mVertexShader;
	Omega::Graphics::PixelShader mPixelShader;

	struct TransformData
	{
		Omega::Math::Matrix4 world;
		Omega::Math::Matrix4 wvp;
		Omega::Math::Vector3 viewPosition;
		float padding;
	};

	struct SettingsData
	{
		float specularWeight = 1.0f;
		float bumpMapWeight = 1.0f;
		float normalMapWeight = 1.0f;
		float padding;
	};

	// Lighting
	using TransformBuffer = Omega::Graphics::TypedConstantBuffer<TransformData>;
	using LightBuffer = Omega::Graphics::TypedConstantBuffer<Omega::Graphics::DirectionalLight>;
	using MaterialBuffer = Omega::Graphics::TypedConstantBuffer<Omega::Graphics::Material>;
	
	using SettingsDataBuffer = Omega::Graphics::TypedConstantBuffer<SettingsData>;

	SettingsDataBuffer mSettingsDataBuffer;

	TransformBuffer mTransformBuffer;
	LightBuffer mLightBuffer;
	MaterialBuffer mMaterialBuffer;

	SettingsData mSettingsData;
	Omega::Graphics::DirectionalLight mDirectionalLight;
	Omega::Graphics::Material mMaterial;

	// Post processing
	Omega::Graphics::RenderTarget mRenderTarget;
	Omega::Graphics::MeshPX mScreenQuad;
	Omega::Graphics::MeshBuffer mScreenQuadBuffer;
	Omega::Graphics::VertexShader mPostProcessingVertexShader;
	Omega::Graphics::PixelShader mPostProcessingPixelShader;


	Omega::Math::Vector3 mTankPosition = 0.0f;
	Omega::Math::Vector3 mTankRotation = 0.0f;
	
};